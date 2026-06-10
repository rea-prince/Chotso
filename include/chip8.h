#ifndef CHIP8_H
#define CHIP8_H

#include "common.h"
#include "stack.h"

typedef struct {

    /* MEMORY */

    uint8_t  memory[MEMORY_SIZE]; // RAM: 4 KiB
    uint16_t PC; // Register for instructions in memory

    uint8_t  V[16]; // Registers: general purpose
    uint16_t I;     // Register for memory addresses

    Stack stack;

    /* TIMERS */

    uint8_t DT; // delay timer
    uint8_t ST; // sound timer

    /* DISPLAY */

    uint8_t font[5 * 16]; // 16 characters, each with height of 5
    // TODO: Load this at runtime

    uint8_t display[CHIP8_HEIGHT * CHIP8_WIDTH / 8]; // 64 x 32 B&W pixels

} Chip8;

void Chip8_init(Chip8* chip8);
void Chip8_render(Chip8* chip8, SDL_Texture* tex);

/* DELAY */


/* SOUND */


/* CYCLE */

uint16_t Chip8_fetch(Chip8* chip8);
void Chip8_decode_execute(Chip8* chip8, uint16_t instruction);


#endif
