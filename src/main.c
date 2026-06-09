#include "common.h"


const int WIDTH = 800, HEIGHT = 800;

int main(int argc, char *argv[]) {

    /* INITIALIZATION */

    SDL_Init( SDL_INIT_EVERYTHING );
    SDL_Window *window_ptr = SDL_CreateWindow(
        "My renderer",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        800, 800,
        SDL_WINDOW_SHOWN
    );
    if (!window_ptr) {
        SDL_Quit();
        return -1;
    }
    SDL_Renderer *renderer_ptr = SDL_CreateRenderer(window_ptr, -1, 0);
    if (!renderer_ptr) {
        SDL_DestroyWindow(window_ptr);
        SDL_Quit();
        return -1;
    }
    SDL_SetRenderTarget(renderer_ptr, NULL);


    /* ------------------------------------------- */

    SDL_Event windowEvent; // input
    bool running = true;
    SDL_SetRenderDrawColor( // background color (rgba)
        renderer_ptr,
        120, 180, 255,
        255
    );

    /* WINDOW LOOP */
    while (running) {
        while (SDL_PollEvent (&windowEvent)) {
            if (SDL_QUIT == windowEvent.type) {
                running = false;
            }
        }

        /* Create ImGui frame */


        SDL_RenderClear(renderer_ptr); // clear renderer for imgui


        // ***rendering here renders in front of imgui***

        SDL_RenderPresent(renderer_ptr);
    }

    /* DESTROY WINDOW */
    SDL_DestroyWindow(window_ptr);
    SDL_Quit();
    return EXIT_SUCCESS;
}
