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

    Chip8 chip8 = {0};
    Chip8_init(&chip8);

    FILE* instructions = fopen(argv[1], "rb");
    if (!instructions) {
        printf("Error loading instructions\n");
        printf("CWD ROM path: %s\n", argv[1]);
        return EXIT_FAILURE;
    }
    Chip8_load(&chip8, instructions);

    /* -------------- */

    SDL_Event event;

    uint64_t now       = SDL_GetTicks();
    uint64_t tick      = now;
    uint64_t lastTime  = now;
    uint64_t lastCycle = now;

    const uint16_t cpuHz = 1000 / CHIP8_HZ;
    const uint16_t displayHz = 1000 / DISPLAY_HZ;

    srand(time(NULL));

    while (chip8.run) {
        handle_input(&event, &chip8);
        now = SDL_GetTicks();

        /* CLOCK CYCLE @ 500Hz */

        if (chip8.waiting) {
            for (int i = 0; i < CHIP8_KEYS; i++) {
                if (chip8.keys[i]) {
                    chip8.V[chip8.WR] = i;
                    chip8.waiting = 0;
                    break;
                }
            }
        }
        if (!chip8.waiting && now - lastCycle >= cpuHz) {
            lastCycle = now;
            Chip8_cycle(&chip8);
            // printf("V0=%d V1=%d V2=%d V3=%d\n",
            //     chip8.V[0], chip8.V[1], chip8.V[2], chip8.V[3]);
        }

        /* TIMERS @ 60Hz */

        if (now - tick >= displayHz) {
            tick = now;
            if (chip8.DT > 0) {
                --chip8.DT;
            }
            if (chip8.ST > 0) {
                --chip8.ST;
            }
            update_texture(&chip8, tex);
            render_SDL(renderer, tex);
        }
        SDL_Delay(1);
    }

    destroy_SDL(window, renderer, tex);

    return EXIT_SUCCESS;
}
