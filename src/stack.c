#ifndef STACK_C
#define STACK_C

#include "common.h"
#include "stack.h"

Stack
Stack_create() {
    return (Stack) { .size = CHIP8_STACK_SIZE };
}

uint16_t
Stack_top(Stack* stack) {
    return stack->top;
}
bool
Stack_empty(Stack* stack) {
    return (stack->top == 0);
}

void
Stack_push(Stack *stack, uint16_t element) {
    stack->stack[++stack->top] = element;
}
uint16_t
Stack_pop(Stack *stack) {
    return stack->stack[stack->top--];
}

#endif
