#include "dot_parser/dot_parser.h"
#include "graph/graph.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CONTENT_SIZE 1024
#define FILE_BUFFER_SIZE 1024

#define ADD_TOKEN(token_type) do {\
          scanner->tokens = realloc(scanner->tokens, sizeof(DOT_PARSER_TOKEN) * (++(scanner->num_tokens)));\
          scanner->tokens[scanner->num_tokens-1].type = token_type;\
          scanner->tokens[scanner->num_tokens-1].content = NULL;\
 } while(0)

#define ADD_ID() do{\
          scanner->content[scanner->content_size]='\0';\
          scanner->tokens = realloc(scanner->tokens, sizeof(DOT_PARSER_TOKEN) * (++(scanner->num_tokens)));\
          scanner->tokens[scanner->num_tokens-1].type = ID;\
          scanner->tokens[scanner->num_tokens-1].content = malloc(scanner->content_size+1);\
          memcpy(scanner->tokens[scanner->num_tokens-1].content, scanner->content, scanner->content_size+1);\
          scanner->content_size = 0;\
} while(0)

enum DOT_PARSER_SCANNER_STATE {
  BEFORE_FIRST_CURLY_BRACKET='^',
  OPEN_BRACKET='[',
  WAITING='.',
  ID_INSIDE='*',
  PORT_START=':',
  ARROW_START='-',
  ESCAPE_ID='\\',
  COMMENT='#',
  COMMENT_START='/'
};

typedef struct DOT_PARSER_SCANNER {
  enum DOT_PARSER_SCANNER_STATE state;
  unsigned long local_cursor;
  unsigned long global_cursor;
  char content[MAX_CONTENT_SIZE];
  unsigned long content_size;
  DOT_PARSER_TOKEN* tokens;
  unsigned long num_tokens;
  int error;
} DOT_PARSER_SCANNER;

void dot_parser_init_scanner(DOT_PARSER_SCANNER* scanner) {
  memset(scanner, 0x00, sizeof(DOT_PARSER_SCANNER));
  scanner->state = BEFORE_FIRST_CURLY_BRACKET;
}

void _dot_parser_get_tokenstream_internal(const char* source, DOT_PARSER_SCANNER* scanner) {

  scanner->local_cursor = 0;
  if(!source) {
    printf("error: no source given\n");
    scanner->error = 1;
    return;
  }

  do {
    char c = source[scanner->local_cursor];
    switch(scanner->state) {
      case BEFORE_FIRST_CURLY_BRACKET: {
        if(c == '{') {
          scanner->state = WAITING;
          ADD_TOKEN(OPEN_CURLY_BRACKET);
        }
        break;
      }
      case WAITING: {
        switch(c) {
          case '-':
            scanner->state = ARROW_START;
            continue;
          case '/':
            scanner->state = COMMENT_START;
            continue;
          case '#':
            scanner->state = COMMENT;
            continue;
          case '{':
            ADD_TOKEN(OPEN_CURLY_BRACKET);
            continue;
          case '}':
            ADD_TOKEN(CLOSE_CURLY_BRACKET);
            continue;
          case '[':
            scanner->state = OPEN_BRACKET;
            continue;
          case '\n':
          case '\t':
          case ' ':
            continue;
        }
        if(
            ('0' <= c && c <= '9') || // is number
            (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z')) || // [a-zA-Z]
            (c == '_' || c == '"') || // _ | "
            (c == '<')  // <
            ) {
          scanner->state = ID_INSIDE;
          scanner->content[scanner->content_size++] = c;
          break;
        } else {
          printf("error: invalid character in WAITING\n");
          scanner->error = 1;
          return;
        }
        break;
      }
      case ID_INSIDE: {
        switch(c) {
          case '\t':
          case '\n':
          case ' ': {
            scanner->state = WAITING;
            ADD_ID();
            continue;
          }
          case '/': {
            scanner->state = COMMENT_START;
            ADD_ID();
            continue;
          }
          case '#': {
            scanner->state = COMMENT;
            ADD_ID();
            continue;
          }
          case '\\': {
            scanner->state = ESCAPE_ID;
            continue;
          }
          case '-': {
            scanner->state = ARROW_START;
            ADD_ID();
            continue;
          }
          case ':': {
            scanner->state = PORT_START;
            ADD_ID();
            continue;
          }
          case ';': {
            scanner->state = WAITING;
            ADD_ID();
            continue;
          }
          case '{':
            scanner->state = WAITING;
            ADD_ID();
            ADD_TOKEN(OPEN_CURLY_BRACKET);
            continue;
          case '}':
            scanner->state = WAITING;
            ADD_ID();
            ADD_TOKEN(CLOSE_CURLY_BRACKET);
            continue;
        }
        if(
            ('0' <= c && c <= '9') || // is number
            (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z')) || // [a-zA-Z]
            (c == '_' || c == '"') || // _ | "
            (c == '<')  // <
            ) {
          scanner->content[scanner->content_size++] = c;
          continue;
        }
        break;
      }
      case ARROW_START: {
        switch(c) {
          case '-': {
            scanner->state = WAITING;
            ADD_TOKEN(LINK);
            break;
          }
          case '>': {
            scanner->state = WAITING;
            ADD_TOKEN(ARROW);
            break;
          }
          default: {
            printf("error: invalid character in ARROW\n");
            scanner->error = 1;
            return;
          }
        }
        break;
      }
      case OPEN_BRACKET: {
        if(c == ']') {
          scanner->state = WAITING;
        }
        break;
      }
      case ESCAPE_ID: {
        scanner->content[scanner->content_size++] = c;
        scanner->state = ID_INSIDE;
        break;
      }
      case PORT_START: {
        switch(c) {
          case ' ':
          case '\n':
          case '\t': {
            scanner->state = WAITING;
            break;
          }
        }
        if(
            !(('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z')) // [a-zA-Z]
            ) {
          scanner->state = WAITING;
          scanner->local_cursor--;
          scanner->global_cursor--;
        }
        break;
      }
      case COMMENT: {
        if(c == '\n') {
          scanner->state = WAITING;
        }
        break;
      }
      case COMMENT_START: {
        if(c == '/') {
          scanner->state = COMMENT;
          continue;
        } else {
          scanner->error = 1;
          return;
        }
      }
    }
    scanner->global_cursor++;
  } while(source[++scanner->local_cursor]);
}

DOT_PARSER_TOKEN* dot_parser_get_tokenstream(const char* source, unsigned long* num_tokens) {
  if(!source || !num_tokens) return NULL;
  DOT_PARSER_SCANNER scanner;
  dot_parser_init_scanner(&scanner);
  _dot_parser_get_tokenstream_internal(source, &scanner);
  if(scanner.error) {
    dot_parser_free_tokenstream(scanner.tokens, scanner.num_tokens);
    *num_tokens = scanner.global_cursor;
    return NULL;
  }
  *num_tokens = scanner.num_tokens;
  return scanner.tokens;
}

void dot_parser_free_tokenstream(DOT_PARSER_TOKEN* tokens, unsigned long num_tokens) {
  for(unsigned long i = 0; i < num_tokens; i++) {
    free(tokens[i].content);
  }
  free(tokens);
}

DOT_PARSER_TOKEN* dot_parser_get_tokenstream_from_file(FILE* file, unsigned long* num_tokens) {
  if(!file) return NULL;
  char buf[FILE_BUFFER_SIZE];
  DOT_PARSER_SCANNER scanner;
  dot_parser_init_scanner(&scanner);
  while(!scanner.error && fgets(buf, FILE_BUFFER_SIZE-1, file)) {
    _dot_parser_get_tokenstream_internal(buf, &scanner);
  }
  if(scanner.error) {
    dot_parser_free_tokenstream(scanner.tokens, scanner.num_tokens);
    *num_tokens = scanner.global_cursor;
    return NULL;
  }
  *num_tokens = scanner.num_tokens;
  return scanner.tokens;
}

DOT_PARSER_AST* dot_parser_ast_from_tokenstream(DOT_PARSER_TOKEN* tokenstream, unsigned long num_tokens);

struct GRAPH* dot_parser_graph_from_ast(DOT_PARSER_AST* ast);
