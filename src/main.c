#include "common.h"
#include "helpers.h"
#include "chip8.h"

int main(int argc, char *argv[]) {

    /* INITIALIZATION */

    SDL_Window*   window;
    SDL_Renderer* renderer;
    SDL_Texture*  tex;

    if (init_SDL(window, renderer, tex) == -1) {
        printf("Error loading SDL\n");
        return EXIT_FAILURE;
    }

    /* -------------- */

    Chip8* chip8;
    Chip8_init(chip8);

    FILE* instructions = fopen(TEST_ROM, "rb");
    if (!instructions) {
        printf("Error loading instructions\n");
        return EXIT_FAILURE;
    }
    Chip8_load(chip8, instructions);

    SDL_Event windowEvent;
    bool running = true;

    uint16_t instruction;

    while (running) {
        handle_input(&windowEvent, &running);

        /* AWAIT CLOCK */

        /* RUN CHIP */


        instruction = Chip8_fetch(chip8);
        Chip8_decode_execute(chip8, instruction);


        /* DRAW */

        update_texture(chip8, tex);
        render_SDL(renderer, tex);
    }

    destroy_SDL(window, renderer, tex);

    return EXIT_SUCCESS;
}
