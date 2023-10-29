#include "parser.h"
#include <locale.h>
#include <stdbool.h>
#include <stdio.h>
#include <wchar.h>

int main() {
  setlocale(LC_ALL, "C.UTF-8");
  Lexer lex = init_lexer();
  bool valid_symbols[] = { true, true, true, true, true, true, true, true, true, true, true, true };
  unsigned int from_line = lex.line;
  unsigned int from_col = lex.column;
  while (scan(&lex, valid_symbols)) {
      printf("token: %s [%d:%d;%d:%d]\n", symbol_name[lex.result_symbol], from_line, from_col, lex.line, lex.column);
      from_line = lex.line;
      from_col = lex.column;
      if (lex.result_symbol == END) break;
  }
  return 0;
}
