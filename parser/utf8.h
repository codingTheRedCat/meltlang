#ifndef MELT_PARSER_UTF8
#define MELT_PARSER_UTF8
#include <stdio.h>
#include <stdbool.h>

typedef int (*BinaryReader) (void *);

static inline void readch_utf8(void *source, unsigned int *lookahead, bool *eof, unsigned int *lookahead_size, BinaryReader read) {
    int byte = read(source);
    if (byte == EOF) {
        *lookahead = 0;
        *lookahead_size = 0;
        *eof = true;
        return;
    }
  if ((byte & 0x80) == 0) {
    *eof = false;
    *lookahead = byte;
    *lookahead_size = 1;
    return;
  }
  if ((byte & 0x20) == 0) {
    *eof = false;
    *lookahead = 0x3F & byte;
    byte = read(source);
    if (byte == EOF) {
        *lookahead = 0;
        *lookahead_size = 0;
        *eof = true;
        return;
    }
    *lookahead <<= 6;
    *lookahead |= 0x3F & byte;
    *lookahead_size = 2;
  } else if ((byte & 0x10) == 0) {
    *eof = false;
    *lookahead = 0x1F & byte;
    byte = read(source);
    if (byte == EOF) {
        *lookahead = 0;
        *lookahead_size = 0;
        *eof = true;
        return;
    }
    *lookahead <<= 6;
    *lookahead |= 0x3F & byte;
    byte = read(source);
    if (byte == EOF) {
        *lookahead = 0;
        *lookahead_size = 0;
        *eof = true;
        return;
    }
    *lookahead <<= 6;
    *lookahead |= 0x3F & byte;
    *lookahead_size = 3;
  } else if ((byte & 0x08) == 0) {
    *eof = false;
    *lookahead = 0x0F & byte;
    byte = read(source);
    if (byte == EOF) {
        *lookahead = 0;
        *lookahead_size = 0;
        *eof = true;
        return;
    }
    *lookahead <<= 6;
    *lookahead |= 0x3F & byte;
    byte = read(source);
    if (byte == EOF) {
        *lookahead = 0;
        *lookahead_size = 0;
        *eof = true;
        return;
    }
    *lookahead <<= 6;
    *lookahead |= 0x3F & byte;
    byte = read(source);
    if (byte == EOF) {
        *lookahead = 0;
        *lookahead_size = 0;
        *eof = true;
        return;
    }
    *lookahead <<= 6;
    *lookahead |= 0x3F & byte;
    *lookahead_size = 4;
  } else if ((byte & 0x04) == 0) {
    *eof = false;
    *lookahead = 0x07 & byte;
    byte = read(source);
    if (byte == EOF) {
        *lookahead = 0;
        *lookahead_size = 0;
        *eof = true;
        return;
    }
    *lookahead <<= 6;
    *lookahead |= 0x3F & byte;
    byte = read(source);
    if (byte == EOF) {
        *lookahead = 0;
        *lookahead_size = 0;
        *eof = true;
        return;
    }
    *lookahead <<= 6;
    *lookahead |= 0x3F & byte;
    byte = read(source);
    if (byte == EOF) {
        *lookahead = 0;
        *lookahead_size = 0;
        *eof = true;
        return;
    }
    *lookahead <<= 6;
    *lookahead |= 0x3F & byte;
    byte = read(source);
    if (byte == EOF) {
        *lookahead = 0;
        *lookahead_size = 0;
        *eof = true;
        return;
    }
    *lookahead <<= 6;
    *lookahead |= 0x3F & byte;
    *lookahead_size = 5;
  } else if ((byte & 0x02) == 0) {
    *eof = false;
    *lookahead = 0x03 & byte;
    byte = read(source);
    if (byte == EOF) {
        *lookahead = 0;
        *lookahead_size = 0;
        *eof = true;
        return;
    }
    *lookahead <<= 6;
    *lookahead |= 0x3F & byte;
    byte = read(source);
    if (byte == EOF) {
        *lookahead = 0;
        *lookahead_size = 0;
        *eof = true;
        return;
    }
    *lookahead <<= 6;
    *lookahead |= 0x3F & byte;
    byte = read(source);
    if (byte == EOF) {
        *lookahead = 0;
        *lookahead_size = 0;
        *eof = true;
        return;
    }
    *lookahead <<= 6;
    *lookahead |= 0x3F & byte;
    byte = read(source);
    if (byte == EOF) {
        *lookahead = 0;
        *lookahead_size = 0;
        *eof = true;
        return;
    }
    *lookahead <<= 6;
    *lookahead |= 0x3F & byte;
    byte = read(source);
    if (byte == EOF) {
        *lookahead = 0;
        *lookahead_size = 0;
        *eof = true;
        return;
    }
    *lookahead <<= 6;
    *lookahead |= 0x3F & byte;
    *lookahead_size = 6;
  }
}

#endif
