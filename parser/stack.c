#include <stdio.h>
#include <stdlib.h>

unsigned int round_up_pow_2(unsigned int v) {
  v--;
  v |= v >> 1;
  v |= v >> 2;
  v |= v >> 4;
  v |= v >> 8;
  v |= v >> 16;
  v++;
  return v;
}

typedef struct {
  void *min;
  void *max;
  void *top;
} Stack;

Stack stack_create(unsigned int initial_size) {
  Stack result;
  result.min = malloc(initial_size);
  result.top = result.min;
  result.max = result.top + initial_size - 1;
  return result;
}

unsigned int stack_max_size(Stack s) { return s.max - s.min + 1; }

unsigned int stack_size(Stack s) { return s.top - s.min; }

void *stack_alloc(Stack *s, unsigned int bytes) {
  if (stack_size(*s) + bytes > stack_max_size(*s)) {
    unsigned int newsize = round_up_pow_2(stack_size(*s) + bytes);
    void *p = realloc(s->min, newsize);
    if (p == NULL) {
      perror("could not reallocate");
      exit(-200);
    }
    s->top = s->top - s->min + p;
    s->min = p;
    s->max = p + newsize - 1;
  }
  return s->top;
}

void *stack_push(Stack *s, unsigned int bytes) {
    s->top += bytes;
    return s->top;
}

void *stack_pop(Stack *s, unsigned int bytes) {
    s->top -= bytes;
    return s->top;
}
