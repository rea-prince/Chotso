#ifndef INSTRUCTIONS_C
#define INSTRUCTIONS_C

#include "common.h"
#include "helpers.h"
#include "chip8.h"

void
ex_0(Chip8* chip8, uint16_t instruction) {
    switch (instruction) {

        // clear display

        case 0x00E0: {
            memset(chip8->display, 0, sizeof(chip8->display));
        } break;

        // return from a subroutine

        case 0x00EE: {
            chip8->PC = chip8->stack[--chip8->SP];
        } break;
    }
}

void
ex_1(Chip8* chip8, uint16_t instruction) {

    // jump to location at nnn

    chip8->PC = instruction & 0x0FFF;
}

void
ex_2(Chip8* chip8, uint16_t instruction) {

    // call subroutine at nnn

    chip8->stack[chip8->SP++] = chip8->PC;
    chip8->PC = instruction & 0x0FFF;
}

void
ex_3(Chip8* chip8, uint16_t instruction) {

    // skip next instruction if Vx != kk

    if (chip8->V[(instruction & 0xF00) >> 8] == (instruction & 0xFF)) {
        chip8->PC += 2;
    }
}

void
ex_4(Chip8* chip8, uint16_t instruction) {

    // skip next instruction if Vx != kk

    if (chip8->V[(instruction & 0xF00) >> 8] != (instruction & 0xFF)) {
        chip8->PC += 2;
    }
}

void
ex_5(Chip8* chip8, uint16_t instruction) {

    // skip next instruction if Vx = Vy

    if (chip8->V[(instruction & 0xF00) >> 8] ==
        chip8->V[(instruction & 0x0F0) >> 4]) {
        chip8->PC += 2;
    }

}

void
ex_6(Chip8* chip8, uint16_t instruction) {

    // set Vx = kk

    chip8->V[(instruction & 0xF00) >> 8] = instruction & 0xFF;
}

void
ex_7(Chip8* chip8, uint16_t instruction) {

    // set Vx = Vx + kk

    chip8->V[(instruction & 0xF00) >> 8] += instruction & 0xFF;
}

void
ex_8(Chip8* chip8, uint16_t instruction) {

    uint16_t x = (instruction & 0xF00) >> 8;
    uint16_t y = (instruction & 0xF0) >> 4;

    switch(instruction & 0xF) {
        case 0x0: {
            chip8->V[x] = chip8->V[y];
        } break;

        case 0x1: {
            chip8->V[x] |= chip8->V[y];
        } break;

        case 0x2: {
            chip8->V[x] &= chip8->V[y];
        } break;

        case 0x3: {
            chip8->V[x] ^= chip8->V[y];
        } break;

        case 0x4: {

            uint8_t vx = chip8->V[x];
            uint8_t vy = chip8->V[y];

            chip8->V[x] = vx + vy;

            chip8->V[0xF] = ((uint16_t) vx + vy > 255) ? 1 : 0;

        } break;

        case 0x5: {
            uint8_t vx = chip8->V[x];
            uint8_t vy = chip8->V[y];

            chip8->V[x] = vx - vy;

            chip8->V[0xF] = vx > vy ? 1 : 0;
        } break;

        case 0x6: {

            /* AMBIGUOUS INSTRUCTION !!! */

            chip8->V[0xF] = chip8->V[x] & 0x1;
            chip8->V[x] = chip8->V[x] >> 1;

        } break;

        case 0x7: {
            chip8->V[0xF] = (chip8->V[y] > chip8->V[x]);
            chip8->V[x] = chip8->V[y] - chip8->V[x];
        } break;

        case 0xE: {

            /* AMBIGUOUS INSTRUCTION !!! */

            chip8->V[0xF] = chip8->V[x] & 0x80;
            chip8->V[x] = chip8->V[x] << 1;

        } break;
    }



}

void
ex_9(Chip8* chip8, uint16_t instruction) {

    // skip next instruction if Vx != Vy

    if (chip8->V[(instruction & 0xF00) >> 8] !=
        chip8->V[(instruction & 0x0F0) >> 4]) {
        chip8->PC += 2;
    }
}

void
ex_A(Chip8* chip8, uint16_t instruction) {

    // set I = nnn

    chip8->I = instruction & 0xFFF;

}

void
ex_B(Chip8* chip8, uint16_t instruction) {

    // jump to location nnn + V0

    chip8->PC = (instruction & 0xFFF) + chip8->V[0];

}

void
ex_C(Chip8* chip8, uint16_t instruction) {

    // set Vx = random byte AND kk

    chip8->V[(instruction & 0xF00) >> 8] = (rand() & 0xFF) & (instruction & 0xFF);
}

void
ex_D(Chip8* chip8, uint16_t instruction) {

    // display n-byte sprite starting at memory location I at (Vx, Vy), set VF = collision

    uint8_t x = chip8->V[(instruction & 0x0F00) >> 8];
    uint8_t y = chip8->V[(instruction & 0x00F0) >> 4];
    uint8_t height = (instruction & 0xF);

    // find byte of x,y in display

    uint8_t offset = x % 8;
    uint8_t sprite;
    uint8_t py;
    uint8_t left;
    uint8_t right;

    uint8_t* row;
    uint8_t* next;

    chip8->V[0xF] = 0;

    for (int spriteRow = 0; spriteRow < height; spriteRow++) {

        // get sprite

        sprite = chip8->memory[chip8->I + spriteRow];

        // actual y coordinate accounting for wrapping

        py = (y + spriteRow) % CHIP8_HEIGHT;

        row = &chip8->display[py * CHIP8_COL + (x / 8)];

        // left and right to account for offset

        left  = sprite >> offset;
        right = sprite << (8 - offset);

        // check for shared bits (overwritten); check spec

        if (*row & left) {
            chip8->V[0xF] = 1;
        }

        *row ^= left;

        if (offset) {
            next = row + 1;

            if (x + 8 > CHIP8_WIDTH) {
                next = &chip8->display[py * CHIP8_COL];
            }

            if (*next & right)
                chip8->V[0xF] = 1;

            *next ^= right;
        }
    }
}

void
ex_E(Chip8* chip8, uint16_t instruction) {

    // skip if key at Vx is up/down

    uint16_t key = chip8->V[(instruction & 0xF00) >> 8];

    switch(instruction & 0xFF) {
        case 0x9E: {
            if (chip8->keys[key]) {
                chip8->PC += 2;
            }
        } break;

        case 0xA1: {
            if (!chip8->keys[key]) {
                chip8->PC += 2;
            }
        } break;
    }
}

void
ex_F(Chip8* chip8, uint16_t instruction) {

    uint8_t x = (instruction & 0xF00) >> 8;

    switch(instruction & 0xFF) {
        case 0x07: {
            chip8->V[x] = chip8->DT;
        } break;

        case 0x0A: {
            chip8->waiting = 1;
            chip8->WR      = x;
        } break;

        case 0x15: {
            chip8->DT = chip8->V[x];
        } break;

        case 0x18: {
            chip8->ST = chip8->V[x];
        } break;

        case 0x1E: {
            chip8->I += chip8->V[x];
        } break;

        case 0x29: {
            chip8->I = 0x50 + (chip8->V[x] * 5);
        } break;

        case 0x33: {
            chip8->memory[chip8->I + 2] = chip8->V[x] % 10;
            chip8->memory[chip8->I + 1] = (chip8->V[x] / 10) % 10;
            chip8->memory[chip8->I]     = chip8->V[x] / 100;
        } break;

        case 0x55: {
            for (int i = 0; i <= x; i++) {
                chip8->memory[chip8->I + i] = chip8->V[i];
            }
        } break;

        case 0x65: {
            for (int i = 0; i <= x; i++) {
                chip8->V[i] = chip8->memory[chip8->I + i];
            }
        } break;
    }
}


#endif
