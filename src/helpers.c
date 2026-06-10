#ifndef HELPERS_C
#define HELPERS_C

#include "common.h"

void
handle_input(SDL_Event* windowEvent, bool* running) {
    while (SDL_PollEvent(windowEvent)) {
        if (SDL_QUIT == windowEvent->type)
            running = false;
    }
}

#endif
