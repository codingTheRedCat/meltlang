#include "definitions.h"
#include "lexer.h"
#include "symbols.h"
// ---
#ifndef MELTLANG_PARSER_H
#define MELTLANG_PARSER_H
#include <stdint.h>
#include <stdio.h>

#define BEGSYM UINT32_MAX

static inline void parse(void *source, void *payload, Reader read,
                         Listener handle) {
  Lexer lexer = init_lexer(source, read);
  handle(payload, BEGSYM, lexer.pos);
  for (;;) {
    TextPos begining = lexer.pos;
    if (!lex(&lexer, ALL_VALID))
      break;
    handle(payload, BEGSYM, begining);
    handle(payload, lexer.result_symbol, lexer.pos);
    if (lexer.result_symbol == END)
      break;
  }
  handle(payload, SOURCE_FILE, lexer.pos);
}

#endif
