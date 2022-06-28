#include "dot_parser/dot_parser.h"
#include "graph/graph.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CONTENT_SIZE 1024

#define ADD_TOKEN(token_type) do {\
          tokens = realloc(tokens, sizeof(DOT_PARSER_TOKEN) * (++(*num_tokens)));\
          tokens[*num_tokens-1].type = token_type;\
          tokens[*num_tokens-1].content = NULL;\
 } while(0)

#define ADD_ID() do{\
          content[content_size]='\0';\
          tokens = realloc(tokens, sizeof(DOT_PARSER_TOKEN) * (++(*num_tokens)));\
          tokens[*num_tokens-1].type = ID;\
          tokens[*num_tokens-1].content = malloc(content_size+1);\
          memcpy(tokens[*num_tokens-1].content, content, content_size+1);\
          content_size = 0;\
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

DOT_PARSER_TOKEN* dot_parser_get_tokenstream(const char* source, unsigned long* num_tokens) {

  *num_tokens = 0;
  if(!source) {
    return NULL;
  }

  const char* begin = source;
  DOT_PARSER_TOKEN* tokens = NULL;

  char content[MAX_CONTENT_SIZE]={0};
  unsigned long content_size = 0;
  enum DOT_PARSER_SCANNER_STATE state = BEFORE_FIRST_CURLY_BRACKET;

  do {
    switch(state) {
      case BEFORE_FIRST_CURLY_BRACKET: {
        if(*source == '{') {
          state = WAITING;
          ADD_TOKEN(OPEN_CURLY_BRACKET);
        }
        break;
      }
      case WAITING: {
        switch(*source) {
          case '-':
            state = ARROW_START;
            continue;
          case '/':
            state = COMMENT_START;
            continue;
          case '#':
            state = COMMENT;
            continue;
          case '{':
            ADD_TOKEN(OPEN_CURLY_BRACKET);
            continue;
          case '}':
            ADD_TOKEN(CLOSE_CURLY_BRACKET);
            continue;
          case '[':
            state = OPEN_BRACKET;
            continue;
          case '\n':
          case '\t':
          case ' ':
            continue;
        }
        if(
            ('0' <= *source && *source <= '9') || // is number
            (('a' <= *source && *source <= 'z') || ('A' <= *source && *source <= 'Z')) || // [a-zA-Z]
            (*source == '_' || *source == '"') || // _ | "
            (*source == '<')  // <
            ) {
          state = ID_INSIDE;
          content[content_size++] = *source;
          break;
        } else {
          *num_tokens = source - begin;
          return NULL;
        }
        break;
      }
      case ID_INSIDE: {
        switch(*source) {
          case '\t':
          case '\n':
          case ' ': {
            state = WAITING;
            ADD_ID();
            continue;
          }
          case '/': {
            state = COMMENT_START;
            ADD_ID();
            continue;
          }
          case '#': {
            state = COMMENT;
            ADD_ID();
            continue;
          }
          case '\\': {
            state = ESCAPE_ID;
            continue;
          }
          case '-': {
            state = ARROW_START;
            ADD_ID();
            continue;
          }
          case ':': {
            state = PORT_START;
            ADD_ID();
            continue;
          }
          case ';': {
            state = WAITING;
            ADD_ID();
            continue;
          }
          case '{':
            state = WAITING;
            ADD_ID();
            ADD_TOKEN(OPEN_CURLY_BRACKET);
            continue;
          case '}':
            state = WAITING;
            ADD_ID();
            ADD_TOKEN(CLOSE_CURLY_BRACKET);
            continue;
        }
        if(
            ('0' <= *source && *source <= '9') || // is number
            (('a' <= *source && *source <= 'z') || ('A' <= *source && *source <= 'Z')) || // [a-zA-Z]
            (*source == '_' || *source == '"') || // _ | "
            (*source == '<')  // <
            ) {
          content[content_size++] = *source;
          continue;
        }
        break;
      }
      case ARROW_START: {
        switch(*source) {
          case '-': {
            state = WAITING;
            ADD_TOKEN(LINK);
            break;
          }
          case '>': {
            state = WAITING;
            ADD_TOKEN(ARROW);
            break;
          }
          default: {
            *num_tokens = source - begin;
            return NULL;
          }
        }
        break;
      }
      case OPEN_BRACKET: {
        if(*source == ']') {
          state = WAITING;
        }
        break;
      }
      case ESCAPE_ID: {
        content[content_size++] = *source;
        state = ID_INSIDE;
        break;
      }
      case PORT_START: {
        switch(*source) {
          case ' ':
          case '\n':
          case '\t': {
            state = WAITING;
            break;
          }
        }
        if(
            !(('a' <= *source && *source <= 'z') || ('A' <= *source && *source <= 'Z')) // [a-zA-Z]
            ) {
          state = WAITING;
          source--;
        }
        break;
      }
      case COMMENT: {
        if(*source == '\n') {
          state = WAITING;
        }
        break;
      }
      case COMMENT_START: {
        if(*source == '/') {
          state = COMMENT;
          continue;
        } else {
          *num_tokens = source - begin;
          return NULL;
        }
      }
    }
  } while(*(++source));

  return tokens;
}

void dot_parser_free_tokenstream(DOT_PARSER_TOKEN* tokens, unsigned long num_tokens) {
  for(unsigned long i = 0; i < num_tokens; i++) {
    free(tokens[i].content);
  }
  free(tokens);
}

DOT_PARSER_TOKEN* dot_parser_get_tokenstream_from_file(struct FILE* file, unsigned long* num_tokens);

DOT_PARSER_AST* dot_parser_ast_from_tokenstream(DOT_PARSER_TOKEN* tokenstream, unsigned long num_tokens);

struct GRAPH* dot_parser_graph_from_ast(DOT_PARSER_AST* ast);
