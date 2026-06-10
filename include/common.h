#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include <math.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

/* LIBRARIES */

#include "SDL.h"
#include "SDL_image.h"

/* DEFINITIONS */

// struct sizing

#define MEMORY_SIZE 4096 // 4 KiB
#define STACK_SIZE 48    // 48 B

#define CHIP8_HEIGHT 32
#define CHIP8_WIDTH 64

#define NIBBLES 4

// settings

#define TPS 60.0f


/* FOR SDL */

#define W_SCALE 20
#define H_SCALE 20
#define WINDOW_HEIGHT (CHIP8_HEIGHT * H_SCALE)
#define WINDOW_WIDTH (CHIP8_WIDTH * W_SCALE)


#endif
