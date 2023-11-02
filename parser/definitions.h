#ifndef MELTLANG_DEFINITIONS_H
#define MELTLANG_DEFINITIONS_H
#include <stdbool.h>

typedef struct {
  unsigned int boffset;
  unsigned int coffset;
  unsigned int line;
  unsigned int column;
} TextPos;

typedef void (*Reader)(void *, unsigned int *, bool *, unsigned int *);

typedef void (*Listener)(void *, unsigned int, TextPos);

#endif
