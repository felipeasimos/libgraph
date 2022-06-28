#ifndef LIBGRAPH_DOT_PARSER
#define LIBGRAPH_DOT_PARSER

struct FILE;
struct GRAPH;

enum DOT_PARSER_TOKEN_TYPE {
  ID='*',
  ARROW='>',
  LINK='-',
  OPEN_CURLY_BRACKET='{',
  CLOSE_CURLY_BRACKET='}'
};

typedef struct DOT_PARSER_TOKEN {

  enum DOT_PARSER_TOKEN_TYPE type;
  char* content;
} DOT_PARSER_TOKEN;

typedef struct DOT_PARSER_AST {

  DOT_PARSER_TOKEN token;
  struct DOT_PARSET_AST* left;
  struct DOT_PARSET_AST* right;
} DOT_PARSER_AST;

//! @relates DOT_PARSER_TOKEN
//! @brief return array of tokens from source
//! @details num_tokens will be the character position in case of an error
//! @param[in] source : dot language string
//! @param[in] num_tokens : where the number of tokens will be stored
//! @return array of tokens if successful, otherwise NULL
DOT_PARSER_TOKEN* dot_parser_get_tokenstream(const char* source, unsigned long* num_tokens);

void dot_parser_free_tokenstream(DOT_PARSER_TOKEN* tokens, unsigned long num_tokens);

DOT_PARSER_TOKEN* dot_parser_get_tokenstream_from_file(struct FILE* file, unsigned long* num_tokens);

DOT_PARSER_AST* dot_parser_ast_from_tokenstream(DOT_PARSER_TOKEN* tokenstream, unsigned long num_tokens);

struct GRAPH* dot_parser_graph_from_ast(DOT_PARSER_AST* ast);

#endif
