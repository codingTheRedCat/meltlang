#include "parser.h"
#include <stdbool.h>

static inline bool is_hexdec(unsigned int c) {
  return (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F') ||
         (c >= '0' && c <= '9');
}

static inline bool is_dec(unsigned int c) { return c >= '0' && c <= '9'; }

static inline bool is_oct(unsigned int c) { return c >= '0' && c <= '7'; }

// Starts when lookahead is one char after backslash. Ends with lookahead one
// character after the last character of an escape sequence.
static inline void handle_char_escape(Lexer *lexer) {
  if (lexer->eof)
    return;
  if (lexer->lookahead == 'u') {
    adv(lexer);
    if (!is_hexdec(lexer->lookahead))
      return;
    adv(lexer);
    if (!is_hexdec(lexer->lookahead))
      return;
    adv(lexer);
    if (!is_hexdec(lexer->lookahead))
      return;
    adv(lexer);
    if (!is_hexdec(lexer->lookahead))
      return;
    adv(lexer);
    return;
  }
  if (lexer->lookahead == 'U') {
    adv(lexer);
    if (!is_hexdec(lexer->lookahead))
      return;
    adv(lexer);
    if (!is_hexdec(lexer->lookahead))
      return;
    adv(lexer);
    if (!is_hexdec(lexer->lookahead))
      return;
    adv(lexer);
    if (!is_hexdec(lexer->lookahead))
      return;
    adv(lexer);
    if (!is_hexdec(lexer->lookahead))
      return;
    adv(lexer);
    if (!is_hexdec(lexer->lookahead))
      return;
    adv(lexer);
    if (!is_hexdec(lexer->lookahead))
      return;
    adv(lexer);
    if (!is_hexdec(lexer->lookahead))
      return;
    adv(lexer);
    return;
  }
  adv(lexer);
}

bool scan(Lexer *lexer, bool valid_symbols[]) {
  if (valid_symbols[PLUS] && lexer->lookahead == '+') {
    lexer->result_symbol = PLUS;
    adv(lexer);
    return true;
  }
  if (valid_symbols[MINUS] && lexer->lookahead == '-') {
    lexer->result_symbol = MINUS;
    adv(lexer);
    return true;
  }
  if (valid_symbols[STAR] && lexer->lookahead == '*') {
    lexer->result_symbol = STAR;
    adv(lexer);
    return true;
  }
  if (valid_symbols[SLASH] && lexer->lookahead == '/') {
    lexer->result_symbol = SLASH;
    adv(lexer);
    return true;
  }
  if (valid_symbols[PAR_OPEN] && lexer->lookahead == '(') {
    lexer->result_symbol = PAR_OPEN;
    adv(lexer);
    return true;
  }
  if (valid_symbols[PAR_CLOSE] && lexer->lookahead == ')') {
    lexer->result_symbol = PAR_CLOSE;
    adv(lexer);
    return true;
  }

  if (valid_symbols[STRING] && lexer->lookahead == '"') {
    lexer->result_symbol = STRING;
    adv(lexer);
    for (;;) {
      if (lexer->eof)
        return true;
      if (lexer->lookahead == '"') {
        adv(lexer);
        return true;
      }
      if (lexer->lookahead == '\\') {
        adv(lexer);
        handle_char_escape(lexer);
        continue;
      }
      adv(lexer);
    }
  }
  if (valid_symbols[CHAR] && lexer->lookahead == '\'') {
    lexer->result_symbol = CHAR;
    adv(lexer);
    if (lexer->eof)
      return true;
    if (lexer->lookahead == '\'') {
      adv(lexer);
      return true;
    }
    if (lexer->lookahead == '\\') {
      adv(lexer);
      handle_char_escape(lexer);
      if (lexer->eof)
        return true;
    } else {
      adv(lexer);
    }
    if (lexer->lookahead == '\'')
      adv(lexer);
    return true;
  }
  if ((valid_symbols[INT] || valid_symbols[FLOAT]) &&
      (is_dec(lexer->lookahead) || lexer->lookahead == '+' ||
       lexer->lookahead == '-')) {
    if (valid_symbols[INT] && lexer->lookahead == '0') {
      adv(lexer);
      if (lexer->lookahead == 'x') {
        lexer->result_symbol = INT;
        adv(lexer);
        while (is_hexdec(lexer->lookahead))
          adv(lexer);
        return true;
      }
      if (lexer->lookahead == 'o') {
        lexer->result_symbol = INT;
        adv(lexer);
        while (is_oct(lexer->lookahead))
          adv(lexer);
        return true;
      }
      if (lexer->lookahead == 'b') {
        lexer->result_symbol = INT;
        adv(lexer);
        while (lexer->lookahead == '1' | lexer->lookahead == '0') {
          adv(lexer);
        }
        return true;
      }
    } else if (lexer->lookahead == '-' || lexer->lookahead == '+') {
      adv(lexer);
    }
    while (is_dec(lexer->lookahead))
      adv(lexer);
    if (valid_symbols[FLOAT] && lexer->lookahead == '.') {
      lexer->result_symbol = FLOAT;
      adv(lexer);
      while (is_dec(lexer->lookahead))
        adv(lexer);
      if (lexer->lookahead == 'e' || lexer->lookahead == 'E') {
        adv(lexer);
        if (lexer->lookahead == '-' || lexer->lookahead == '+') {
          adv(lexer);
        }
        while (is_dec(lexer->lookahead))
          adv(lexer);
      }
      return true;
    }
    if (valid_symbols[FLOAT] && lexer->lookahead == 'e' ||
        lexer->lookahead == 'E') {
      lexer->result_symbol = FLOAT;
      adv(lexer);
      if (lexer->lookahead == '-' || lexer->lookahead == '+') {
        adv(lexer);
      }
      while (is_dec(lexer->lookahead))
        adv(lexer);
      return true;
    }

    lexer->result_symbol = INT;
    return valid_symbols[INT];
  }
  if (valid_symbols[WHITESPACE] &&
      (lexer->lookahead == ' ' || lexer->lookahead == '\t' ||
       lexer->lookahead == '\r' || lexer->lookahead == '\n')) {
    while (lexer->lookahead == ' ' || lexer->lookahead == '\t' ||
           lexer->lookahead == '\r' || lexer->lookahead == '\n')
      adv(lexer);
    lexer->result_symbol = WHITESPACE;
    return true;
  }
  if (valid_symbols[END] && lexer->eof) {
    lexer->result_symbol = END;
    return true;
  }
  return false;
}
