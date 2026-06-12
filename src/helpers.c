#ifndef HELPERS_C
#define HELPERS_C

#include "common.h"
#include "chip8.h"

/* MAP KEYS */

static uint8_t
map_keys(uint32_t key) {
    switch(key) {
        case SDLK_1: return 1;
        case SDLK_2: return 2;
        case SDLK_3: return 3;
        case SDLK_4: return 0xC;

        case SDLK_q: return 4;
        case SDLK_w: return 5;
        case SDLK_e: return 6;
        case SDLK_r: return 0xD;

        case SDLK_a: return 7;
        case SDLK_s: return 8;
        case SDLK_d: return 9;
        case SDLK_f: return 0xE;

        case SDLK_z: return 0xA;
        case SDLK_x: return 0x0;
        case SDLK_c: return 0xB;
        case SDLK_v: return 0xF;
    }

    return -1;
}

void
handle_input(SDL_Event* event, Chip8* chip8) {
    while (SDL_PollEvent(event)) {
        if (event->type == SDL_QUIT) {
            chip8->run = false;
            return;
        }

        if (event->type == SDL_KEYDOWN) {
            if (event->key.keysym.sym == SDLK_ESCAPE) {
                chip8->run = false;
                return;
            }
            int8_t key = map_keys(event->key.keysym.sym);
            if (key != -1) {
                chip8->keys[key] = 1;
                // printf("SDL key: %d -> CHIP8 key: %d\n",
                //        event->key.keysym.sym, key);
            }
        }

        if (event->type == SDL_KEYUP) {
            int8_t key = map_keys(event->key.keysym.sym);
            if (key != -1) {
                chip8->keys[key] = 0;
            }
        }
    }
}

int
init_SDL(SDL_Window** window, SDL_Renderer** renderer, SDL_Texture** tex) {
    if (SDL_Init( SDL_INIT_EVERYTHING ) != 0) {
        return -1;
    }

    *window = SDL_CreateWindow(
        "Chotso",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN
    );
    if (!window) {
        SDL_Quit();
        return -1;
    }

    *renderer = SDL_CreateRenderer(
        *window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );
    if (!*renderer) {
        SDL_DestroyWindow(*window);
        SDL_Quit();
        return -1;
    }
    SDL_SetRenderTarget(*renderer, NULL);

    *tex = SDL_CreateTexture(
        *renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING,
        CHIP8_WIDTH, CHIP8_HEIGHT
    );
    if (!tex) {
        SDL_DestroyWindow(*window);
        SDL_DestroyRenderer(*renderer);
        SDL_Quit();
        return -1;
    }

    SDL_SetRenderDrawColor( // background color (rgba)
        *renderer,
        120, 180, 255,
        255
    );
    // SDL_RenderSetScale(*renderer, W_SCALE, H_SCALE);

    return 1;
}

void
destroy_SDL(SDL_Window* window, SDL_Renderer* renderer, SDL_Texture* tex) {
    SDL_DestroyTexture(tex);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

/* Render Image */

void
update_texture(Chip8* chip8, SDL_Texture* tex) {

    void* pixels;
    int   pitch;

    uint32_t* targetPixel;
    uint32_t  color;
    uint8_t   pix;

    int row;
    int col;

    SDL_LockTexture(tex, NULL, &pixels, &pitch);

    for (int y = 0; y < CHIP8_HEIGHT; y++) {

        row = y * CHIP8_COL;

        for (int x = 0; x < CHIP8_WIDTH; x++) {

            targetPixel = (uint32_t*) (
                (uint8_t*) pixels + (y * pitch) + (x * sizeof(uint32_t))
            );

            col = row + (x / 8);

            pix = (chip8->display[col] >> (7 - (x % 8))) & 0x1;

            color = pix ? 0x00FF00FF : 0x000000FF;

            *targetPixel = color;
        }
    }

    SDL_UnlockTexture(tex);
}

void
render_SDL(SDL_Renderer* renderer, SDL_Texture* tex) {
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, tex, NULL, NULL);
    SDL_RenderPresent(renderer);
}

#endif
