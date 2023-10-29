#ifndef STACK_H
#define STACK_H

#include <stdlib.h>

typedef struct {
  void *min;
  void *max;
  void *top;
} Stack;

Stack stack_create(unsigned int initial_size);

unsigned int stack_max_length(Stack s);

unsigned int stack_size(Stack s);

void *stack_alloc(Stack *s, unsigned int bytes);

void *stack_push(Stack *s, unsigned int bytes);

void *stack_pop(Stack *s, unsigned int bytes);

#endif // STACK_H

