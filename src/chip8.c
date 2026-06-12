#ifndef CHIP8_C
#define CHIP8_C

#include "common.h"
#include "chip8.h"
#include "instructions.h"

/* Initialize Chip8 */

// TO BE CHANGED

const uint8_t font[80] = {
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
};

void
Chip8_init(Chip8* chip8) {

    *chip8 = (Chip8) {
        .PC = 0x200,
        .SP = 0,
        .run = 1
    };

    memcpy(&chip8->memory[0x50], font, sizeof(font));
}


/* LOAD INSTRUCTIONS */

void
Chip8_load(Chip8* chip8, FILE* src) {
    fread(
        &chip8->memory[chip8->PC],
        (size_t) (CHIP8_MEMORY_SIZE - (0x1FF)),
        1, src
    );
}

/* CYCLE */

void
Chip8_cycle(Chip8* chip8) {

    /* FETCH */

    uint16_t instruction =
        (chip8->memory[chip8->PC] << 8) |
        chip8->memory[chip8->PC + 1];

    chip8->PC += 2;

    /* DECODE & EXECUTE */

    switch(instruction & 0xF000) {
        case 0x0000: {
            ex_0(chip8, instruction);
        } break;

        case 0x1000: {
            ex_1(chip8, instruction);
        } break;

        case 0x2000: {
            ex_2(chip8, instruction);
        } break;

        case 0x3000: {
            ex_3(chip8, instruction);
        } break;

        case 0x4000: {
            ex_4(chip8, instruction);
        } break;

        case 0x5000: {
            ex_5(chip8, instruction);
        } break;

        case 0x6000: {
            ex_6(chip8, instruction);
        } break;

        case 0x7000: {
            ex_7(chip8, instruction);
        } break;

        case 0x8000: {
            ex_8(chip8, instruction);
        } break;

        case 0x9000: {
            ex_9(chip8, instruction);
        } break;

        case 0xA000: {
            ex_A(chip8, instruction);
        } break;

        case 0xB000: {
            ex_B(chip8, instruction);
        } break;

        case 0xC000: {
            ex_C(chip8, instruction);
        } break;

        case 0xD000: {
            ex_D(chip8, instruction);
        } break;

        case 0xE000: {
            ex_E(chip8, instruction);
        } break;

        case 0xF000: {
            ex_F(chip8, instruction);
        } break;

        default: {
            return;
        }
    }

}

#endif
