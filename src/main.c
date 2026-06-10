#include "common.h"
#include "chip8.h"

int main(int argc, char *argv[]) {

    /* INITIALIZATION */

    SDL_Init( SDL_INIT_EVERYTHING );
    SDL_Window *window_ptr = SDL_CreateWindow(
        "My renderer",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN
    );
    if (!window_ptr) {
        SDL_Quit();
        return -1;
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(window_ptr, -1, 0);
    if (!renderer) {
        SDL_DestroyWindow(window_ptr);
        SDL_Quit();
        return -1;
    }
    SDL_SetRenderTarget(renderer, NULL);


    /* ------------------------------------------- */

    SDL_Event windowEvent; // input
    bool running = true;
    SDL_SetRenderDrawColor( // background color (rgba)
        renderer,
        120, 180, 255,
        255
    );

    /* STUFF */

    SDL_Texture *tex = SDL_CreateTexture(
        renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING,
        CHIP8_WIDTH, CHIP8_HEIGHT
    );
    Chip8 chip8 = Chip8_init();

    /* WINDOW LOOP */
    while (running) {
        while (SDL_PollEvent (&windowEvent)) {
            if (SDL_QUIT == windowEvent.type) {
                running = false;
            }
        }
        SDL_RenderClear(renderer);

        /* DRAW */

        Chip8_render(chip8, tex);
        SDL_RenderCopy(renderer, tex, NULL, NULL);

        /* ---- */

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(tex);

    /* DESTROY WINDOW */
    SDL_DestroyWindow(window_ptr);
    SDL_Quit();
    return EXIT_SUCCESS;
}
