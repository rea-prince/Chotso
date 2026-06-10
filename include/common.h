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

#define MEMORY_SIZE 4096 // 4 KiB
#define STACK_SIZE 48    // 48 B

#define CHIP8_HEIGHT 32
#define CHIP8_WIDTH 64

#define WINDOW_HEIGHT 32
#define WINDOW_WIDTH 64


#endif
