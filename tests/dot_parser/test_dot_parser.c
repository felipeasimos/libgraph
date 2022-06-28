#include "ctdd.h"
#include "dot_parser/dot_parser.h"

#include <string.h>

ctdd_test(test_dot_parser_get_tokenstream) {
  unsigned long num_tokens = 0;
  DOT_PARSER_TOKEN* tokens = dot_parser_get_tokenstream("sdfsd { a ->b;\n a-- {b2 ca23->3fa;df:asdf->{a b}}->}", &num_tokens);
  ctdd_check(tokens);
  DOT_PARSER_TOKEN correct_tokens[] = {
    { .content = NULL, .type = OPEN_CURLY_BRACKET},
    { .content = "a", .type = ID},
    { .content = NULL, .type = ARROW},
    { .content = "b", .type = ID},
    { .content = "a", .type = ID},
    { .content = NULL, .type = LINK},
    { .content = NULL, .type = OPEN_CURLY_BRACKET},
    { .content = "b2", .type = ID},
    { .content = "ca23", .type = ID},
    { .content = NULL, .type = ARROW},
    { .content = "3fa", .type = ID},
    { .content = "df", .type = ID},
    { .content = NULL, .type = ARROW},
    { .content = NULL, .type = OPEN_CURLY_BRACKET},
    { .content = "a", .type = ID},
    { .content = "b", .type = ID},
    { .content = NULL, .type = CLOSE_CURLY_BRACKET},
    { .content = NULL, .type = CLOSE_CURLY_BRACKET},
    { .content = NULL, .type = ARROW},
    { .content = NULL, .type = CLOSE_CURLY_BRACKET},
  };
  ctdd_check(num_tokens == sizeof(correct_tokens)/sizeof(correct_tokens[0]));
  for(unsigned long i = 0; i < sizeof(correct_tokens)/sizeof(correct_tokens[0]); i++) {
    ctdd_check(tokens[i].type == correct_tokens[i].type);

    if(tokens[i].type == ID) {
      ctdd_check(!strcmp(tokens[i].content, correct_tokens[i].content));
    }
  }
  dot_parser_free_tokenstream(tokens, num_tokens);
}

ctdd_test(test_dot_parser_get_tokenstream_from_file) {
  unsigned long num_tokens = 0;
  FILE* file = fopen("tests/test.dot", "rt");
  ctdd_check(file);
  DOT_PARSER_TOKEN* tokens = dot_parser_get_tokenstream_from_file(file, &num_tokens);
  ctdd_check(tokens);
  DOT_PARSER_TOKEN correct_tokens[] = {
    { .content = NULL, .type = OPEN_CURLY_BRACKET},
    { .content = "a", .type = ID},
    { .content = NULL, .type = ARROW},
    { .content = "b", .type = ID},
    { .content = "a", .type = ID},
    { .content = NULL, .type = LINK},
    { .content = NULL, .type = OPEN_CURLY_BRACKET},
    { .content = "b2", .type = ID},
    { .content = "ca23", .type = ID},
    { .content = NULL, .type = ARROW},
    { .content = "3fa", .type = ID},
    { .content = "df", .type = ID},
    { .content = NULL, .type = ARROW},
    { .content = NULL, .type = OPEN_CURLY_BRACKET},
    { .content = "a", .type = ID},
    { .content = "b", .type = ID},
    { .content = NULL, .type = CLOSE_CURLY_BRACKET},
    { .content = NULL, .type = CLOSE_CURLY_BRACKET},
    { .content = NULL, .type = ARROW},
    { .content = NULL, .type = CLOSE_CURLY_BRACKET},
  };
  ctdd_check(num_tokens == sizeof(correct_tokens)/sizeof(correct_tokens[0]));
  for(unsigned long i = 0; i < sizeof(correct_tokens)/sizeof(correct_tokens[0]); i++) {
    ctdd_check(tokens[i].type == correct_tokens[i].type);

    if(tokens[i].type == ID) {
      ctdd_check(!strcmp(tokens[i].content, correct_tokens[i].content));
    }
  }
  fclose(file);
  dot_parser_free_tokenstream(tokens, num_tokens);
}

ctdd_test_suite(test_dot_parser) {
  ctdd_run_test(test_dot_parser_get_tokenstream);
  ctdd_run_test(test_dot_parser_get_tokenstream_from_file);
}
