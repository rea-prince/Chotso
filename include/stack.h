#ifndef STACK_H
#define STACK_H

#include "common.h"

#define STACK_SIZE 48    // 48 B

typedef struct {
    uint16_t stack[STACK_SIZE];
    uint16_t top;
    uint16_t size;
} Stack;

Stack Stack_create();

uint16_t Stack_top(Stack* stack);
bool Stack_empty(Stack* stack);

void Stack_push(Stack *stack, uint16_t element);
uint16_t Stack_pop(Stack *stack);

#endif
