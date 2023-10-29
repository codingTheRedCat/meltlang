#include "parser.h"
#include <endian.h>
#include <stdbool.h>
#include <stdio.h>
#include <wchar.h>
#include <wctype.h>

#define nextc(byte, lexer)                                                     \
  byte = getchar();                                                            \
  if (byte == EOF) {                                                           \
    lexer->eof = true;                                                         \
    lexer->lookahead = 0;                                                      \
    return;                                                                    \
  }

void adv(Lexer *lexer) {
  // UTF-8 decode one character from STDIN and put it in lookahead or set EOF = true
  // and lookahead=0 if no more bytes or an incomplete characer.
  unsigned int codePoint = 0;
  int byte;
  if (lexer->lookahead == '\r') {
      lexer->column = 0;
      lexer->line++;
      lexer->seen_cr = true;
  } else if (lexer->lookahead == '\n') {
      lexer->column = 0;
      if (lexer->seen_cr) {
          lexer->seen_cr = false;
      } else {
          lexer->line++;
      }
  } else {
      lexer->seen_cr = false;
      lexer->column++;
  }
          
  lexer->byte_offset += lexer->lookahead_size;
  lexer->char_offset++;
  nextc(byte, lexer);
  if ((byte & 0x80) == 0) {
    lexer->eof = false;
    lexer->lookahead = byte;
    lexer->lookahead_size = 1;
    return;
  }
  if ((byte & 0x20) == 0) {
    lexer->eof = false;
    lexer->lookahead = 0x3F & byte;
    nextc(byte, lexer);
    lexer->lookahead <<= 6;
    lexer->lookahead |= 0x3F & byte;
    lexer->lookahead_size = 2;
  } else if ((byte & 0x10) == 0) {
    lexer->eof = false;
    lexer->lookahead = 0x1F & byte;
    nextc(byte, lexer);
    lexer->lookahead <<= 6;
    lexer->lookahead |= 0x3F & byte;
    nextc(byte, lexer);
    lexer->lookahead <<= 6;
    lexer->lookahead |= 0x3F & byte;
    lexer->lookahead_size = 3;
  } else if ((byte & 0x08) == 0) {
    lexer->eof = false;
    lexer->lookahead = 0x0F & byte;
    nextc(byte, lexer);
    lexer->lookahead <<= 6;
    lexer->lookahead |= 0x3F & byte;
    nextc(byte, lexer);
    lexer->lookahead <<= 6;
    lexer->lookahead |= 0x3F & byte;
    nextc(byte, lexer);
    lexer->lookahead <<= 6;
    lexer->lookahead |= 0x3F & byte;
    lexer->lookahead_size = 4;
  } else if ((byte & 0x04) == 0) {
    lexer->eof = false;
    lexer->lookahead = 0x07 & byte;
    nextc(byte, lexer);
    lexer->lookahead <<= 6;
    lexer->lookahead |= 0x3F & byte;
    nextc(byte, lexer);
    lexer->lookahead <<= 6;
    lexer->lookahead |= 0x3F & byte;
    nextc(byte, lexer);
    lexer->lookahead <<= 6;
    lexer->lookahead |= 0x3F & byte;
    nextc(byte, lexer);
    lexer->lookahead <<= 6;
    lexer->lookahead |= 0x3F & byte;
    lexer->lookahead_size = 5;
  } else if ((byte & 0x02) == 0) {
    lexer->eof = false;
    lexer->lookahead = 0x03 & byte;
    nextc(byte, lexer);
    lexer->lookahead <<= 6;
    lexer->lookahead |= 0x3F & byte;
    nextc(byte, lexer);
    lexer->lookahead <<= 6;
    lexer->lookahead |= 0x3F & byte;
    nextc(byte, lexer);
    lexer->lookahead <<= 6;
    lexer->lookahead |= 0x3F & byte;
    nextc(byte, lexer);
    lexer->lookahead <<= 6;
    lexer->lookahead |= 0x3F & byte;
    nextc(byte, lexer);
    lexer->lookahead <<= 6;
    lexer->lookahead |= 0x3F & byte;
    lexer->lookahead_size = 6;
  }
}
