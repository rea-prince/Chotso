#ifndef CHIP8_C
#define CHIP8_C

#include "common.h"
#include "chip8.h"
#include "instructions.h"

/* Initialize Chip8 */

void
Chip8_init(Chip8* chip8) {
    *chip8 = (Chip8) {
        .font = {
            0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
            0x20, 0x60, 0x20, 0x20, 0x70, // 1
            0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
            0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
            0x90, 0x90, 0xF0, 0x10, 0x10, // 4
            0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
            0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
            0xF0, 0x10, 0x20, 0x40, 0x40, // 7
            0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
            0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
            0xF0, 0x90, 0xF0, 0x90, 0x90, // A
            0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
            0xF0, 0x80, 0x80, 0x80, 0xF0, // C
            0xE0, 0x90, 0x90, 0x90, 0xE0, // D
            0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
            0xF0, 0x80, 0xF0, 0x80, 0x80  // F
        }
    };
}


/* LOAD INSTRUCTIONS */

void
Chip8_load(Chip8* chip8, FILE* src) {

    fread(
        &chip8->memory[0x200],
        (size_t) (MEMORY_SIZE - (0x1FF)),
        1, src
    );

    chip8->PC = 0x200;

}

/* FETCH INSTRUCTION */

uint16_t
Chip8_fetch(Chip8* chip8) {
    uint16_t instruction = 0x0;

    instruction += (chip8->memory[chip8->PC++] << 8);
    instruction += chip8->memory[chip8->PC];

    return instruction;
}

/* DECODE INSTRUCTION */

void
Chip8_decode_execute(Chip8* chip8, uint16_t instruction) {
    uint8_t n[NIBBLES] = {
        (instruction >> 12) & 0xF,
        (instruction >> 8) & 0xF,
        (instruction >> 4) & 0xF,
        instruction & 0x000F
    };

    // all tentative for now

    /* CLEAR SCREEN */

    if (instruction == 0x00E0) {
        memset(chip8->display, 0, sizeof(chip8->display));
    } else if (n[0] == 0x1) {
        // jump
        chip8->PC = (instruction & 0x0FFF);
    } else if (n[0] == 0x6) {
        // set reg
        chip8->V[ (instruction >> 8) & 0x000F ] = instruction & 0x00FF;
    } else if (n[0] == 0x7) {
        // add
        chip8->V[ (instruction >> 8) & 0x000F ] += instruction & 0x00FF;
    } else if (n[0] == 0xA) {
        chip8->I = instruction & 0x0FFF;
    } else if (n[0] == 0xD) {

        uint8_t x = chip8->V[(instruction & 0x0F00) >> 8];
        uint8_t y = chip8->V[(instruction & 0x00F0) >> 4];
        uint8_t height = (instruction & 0xF);

        // find byte of x,y in display

        uint8_t offset = x % 8;

        chip8->V[0xF] = 0;

        for (int spriteRow = 0; spriteRow < height; spriteRow++) {

            // get sprite

            uint8_t sprite = chip8->memory[chip8->I + spriteRow];

            // actual y coordinate accounting for wrapping

            uint8_t py = (y + spriteRow) % CHIP8_HEIGHT;

            uint8_t* row = &chip8->display[py * CHIP8_COL + (x / 8)];

            // left and right to account for offset

            uint8_t left  = sprite >> offset;
            uint8_t right = sprite << (8 - offset);

            // check for shared bits (overwritten); check spec

            if (*row & left) {
                chip8->V[0xF] = 1;
            }

            *row ^= left;

            if (offset) {
                uint8_t* next = row + 1;

                if (x + 8 > CHIP8_WIDTH) {
                    next = &chip8->display[py * CHIP8_COL];
                }

                if (*next & right)
                    chip8->V[0xF] = 1;

                *next ^= right;
            }
        }
    }
}

/* CYCLE */



#endif
