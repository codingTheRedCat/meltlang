#ifndef MELT_PARSER_SYMBOLS_H
#define MELT_PARSER_SYMBOLS_H
#include <stdbool.h>

typedef enum {
  INT = 0,
  FLOAT = 1,
  CHAR = 2,
  STRING = 3,
  WHITESPACE = 4,
  PLUS = 5,
  MINUS = 6,
  STAR = 7,
  SLASH = 8,
  PAR_OPEN = 9,
  PAR_CLOSE = 10,
  END = 11,
  SOURCE_FILE = 12,
} Symbol;

#define TOKEN_COUNT 12
#define SYMBOL_COUNT 13

#define is_token(sym) (sym < TOKEN_COUNT)

static const bool ALL_VALID[13] = { true, true, true, true, true, true, true, true, true, true, true, true, true, };

static const bool ALL_NOT_VALID[13] = { false, false, false, false, false, false, false, false, false, false, false, false, false, };

static const char *symbol_name[13] = { "int", "float", "char", "string", "whitespace", "plus", "minus", "star", "slash", "par_open", "par_close", "end", "source_file", };

#endif
