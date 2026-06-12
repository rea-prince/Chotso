#ifndef HELPERS_C
#define HELPERS_C

#include "common.h"
#include "chip8.h"

void
handle_input(SDL_Event* windowEvent, bool* running) {
    while (SDL_PollEvent(windowEvent)) {
        if (SDL_QUIT == windowEvent->type)
            *running = false;
    }
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

        row = y * CHIP8_WIDTH / 8;

        for (int x = 0; x < CHIP8_WIDTH; x++) {

            targetPixel = (uint32_t*) (
                (uint8_t*) pixels + (y * pitch) + (x * sizeof(uint32_t))
            );

            col = row + (x / 8);

            pix = (chip8->display[col] >> (7 - (x % 8))) & 0x1;

            color = pix ? 0xFFFFFFFF : 0x000000FF;

            *targetPixel = color;
        }
    }

    SDL_UnlockTexture(tex);
}

int
init_SDL(SDL_Window* window, SDL_Renderer* renderer, SDL_Texture* tex) {
    SDL_Init( SDL_INIT_EVERYTHING );

    window = SDL_CreateWindow(
        "My renderer",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN
    );
    if (!window) {
        SDL_Quit();
        return -1;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) {
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }
    SDL_SetRenderTarget(renderer, NULL);

    tex = SDL_CreateTexture(
        renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING,
        CHIP8_WIDTH, CHIP8_HEIGHT
    );
    if (!tex) {
        SDL_DestroyWindow(window);
        SDL_DestroyRenderer(renderer);
        SDL_Quit();
        return -1;
    }

    SDL_SetRenderDrawColor( // background color (rgba)
        renderer,
        120, 180, 255,
        255
    );
    SDL_RenderSetScale(renderer, W_SCALE, H_SCALE);

    return 1;
}

void
destroy_SDL(SDL_Window* window, SDL_Renderer* renderer, SDL_Texture* tex) {
    SDL_DestroyTexture(tex);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void
render_SDL(SDL_Renderer* renderer, SDL_Texture* tex) {
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, tex, NULL, NULL);
    SDL_RenderPresent(renderer);
}

#endif
