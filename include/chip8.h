#ifndef CHIP8_H
#define CHIP8_H

#include "common.h"

typedef struct {

    /* MEMORY */

    uint8_t  memory[CHIP8_MEMORY_SIZE]; // RAM: 4 KiB
    uint8_t  V[16]; // general purpose registers
    uint16_t PC;    // register for memory addresses
    uint16_t I;     // register for data

    /* STACK */

    uint16_t stack[CHIP8_STACK_SIZE];
    uint8_t  SP;

    /* TIMERS */

    uint8_t DT; // delay timer
    uint8_t ST; // sound timer

    /* DISPLAY AND INPUT */

    uint8_t keys[CHIP8_KEYS]; // 1 down; 0 up

    uint8_t waiting; // waiting bool
    uint8_t WR;      // wait register

    uint8_t run;
    uint8_t draw;
    uint8_t display[CHIP8_HEIGHT * CHIP8_COL]; // 64 x 32 B&W pixels

} Chip8;

void Chip8_init(Chip8* chip8);
void Chip8_load(Chip8* chip8, FILE* src);

/* CYCLE */

void Chip8_cycle(Chip8* chip8);


#endif
