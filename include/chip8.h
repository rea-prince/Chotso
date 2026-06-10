#ifndef CHIP8_H
#define CHIP8_H

#include "common.h"

#define MEMORY_SIZE 4096

#define DISPLAY_HEIGHT 8
#define DISPLAY_WIDTH 4

typedef struct Chip8 {

    /* MEMORY */

    uint8_t  memory[MEMORY_SIZE]; // RAM: 4 KiB
    uint8_t  V[16]; // Registers: general purpose
    uint8_t  *PC;   // Program Counter: pointer to instruction in memory
    uint16_t *I;    // Index: pointer to locations in memory

    /* STACK (will just use an array for now) */



    /* DISPLAY */

    uint8_t display[DISPLAY_HEIGHT * DISPLAY_WIDTH]; // 64 x 32 B&W pixels
} Chip8;


#endif
