#include "parser.h"
#include "symbols.h"
#include "utf8.h"
#include <stdbool.h>
#include <stdio.h>
#include <wchar.h>
#include <wctype.h>

int read_byte_stdin(void *ign) { return getchar(); }

void read(void *source, unsigned int *ch, bool *eof, unsigned int *size) {
  readch_utf8(source, ch, eof, size, read_byte_stdin);
}

void listen(void *payload, unsigned int tag, TextPos pos) {
  int *indent = (int *)payload;
  if (tag != BEGSYM) {
    *indent -= 1;
    for (int i = 0; i < *indent; i++) {
      printf("  ");
    }
    printf("[%d:%d] %s)\n", pos.line, pos.column, symbol_name[tag]);
    return;
  }
  for (int i = 0; i < *indent; i++) {
    printf("  ");
  }
  printf("([%d:%d]\n", pos.line, pos.column);
  *indent += 1;
}

int main() {
  Reader r = read;
  int indent = 0;
  parse(NULL, &indent, r, listen);
}
