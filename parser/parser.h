#ifndef PARSER_H
#define PARSER_H
#include <stdio.h>
#include <stdbool.h>

typedef enum {
  WHITESPACE = 0,
  INT = 1,
  FLOAT = 2,
  CHAR = 3,
  STRING = 4,
  PLUS = 5,
  MINUS = 6,
  STAR = 7,
  SLASH = 8,
  PAR_OPEN = 9,
  PAR_CLOSE = 10,
  END = 11,
} Symbol;

static const char *symbol_name[12] = {"whitespace", "int", "float", "char", "string", "plus", "minus", "star", "slash", "par_open", "par_close", "end"};

typedef struct {
  unsigned int start;
  unsigned int end;
  char *value;
  unsigned int value_length;
} ValueToken;

typedef struct {
  unsigned int start;
  unsigned int end;
} Token;

typedef struct {
  unsigned int lookahead;
  unsigned int lookahead_size;
  bool eof;
  unsigned int result_symbol;
  unsigned int byte_offset;
  unsigned int char_offset;
  unsigned int column;
  unsigned int line;
  bool seen_cr;
} Lexer;

void adv(Lexer *lexer);

static inline Lexer init_lexer() {
    Lexer lex;
    lex.seen_cr = false;
    lex.lookahead = 0;
    adv(&lex);
    lex.byte_offset = 0;
    lex.char_offset = 0;
    lex.line = 1;
    lex.column = 0;
    return lex;
}

bool scan(Lexer *lexer, bool valid_symbols[]);
#endif
