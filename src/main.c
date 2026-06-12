#include "common.h"
#include "helpers.h"
#include "chip8.h"

int main(int argc, char* argv[]) {

    if (argc == 1) {
        printf("Usage: ./build/Chip8 <ROM>");
        return EXIT_FAILURE;
    }

    /* INITIALIZATION */

    SDL_Window*   window;
    SDL_Renderer* renderer;
    SDL_Texture*  tex;

    if (init_SDL(&window, &renderer, &tex) == -1) {
        printf("Error loading SDL\n");
        return EXIT_FAILURE;
    }

    /* -------------- */

    Chip8 chip8;
    Chip8_init(&chip8);

    FILE* instructions = fopen(argv[1], "rb");
    if (!instructions) {
        printf("Error loading instructions\n");
        printf("CWD ROM path: %s\n", argv[1]);
        return EXIT_FAILURE;
    }
    Chip8_load(&chip8, instructions);

    SDL_Event windowEvent;
    bool      running = true;

    uint64_t tick      = SDL_GetTicks();
    uint64_t lastTime  = SDL_GetTicks();
    uint64_t lastCycle = SDL_GetTicks();
    uint64_t now;

    while (running) {
        handle_input(&windowEvent, &running);
        now = SDL_GetTicks();

        /* CLOCK CYCLE */

        if (now - lastCycle >= (1000.0f / CHIP8_HZ)) {
            lastCycle = now;
            Chip8_fetch(&chip8);
            Chip8_decode_execute(&chip8);
        }

        /* TIMERS @ 60Hz */

        if (SDL_GetTicks() - tick >= (1000.0f / DISPLAY_HZ)) {
            tick = SDL_GetTicks();
            if (chip8.DT > 0) {
                --chip8.DT;
            }
            if (chip8.ST > 0) {
                --chip8.ST;
            }
        }

        /* DRAW */

        update_texture(&chip8, tex);
        render_SDL(renderer, tex);
    }

    destroy_SDL(window, renderer, tex);

    return EXIT_SUCCESS;
}
