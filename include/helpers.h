#ifndef HELPERS_H
#define HELPERS_H

#include "chip8.h"

void handle_input(SDL_Event* event, Chip8* chip8);
void update_texture(Chip8* chip8, SDL_Texture* tex);

int init_SDL(SDL_Window** window, SDL_Renderer** renderer, SDL_Texture** tex);
void destroy_SDL(SDL_Window* window, SDL_Renderer* renderer, SDL_Texture* tex);
void render_SDL(SDL_Renderer* renderer, SDL_Texture* tex);

#endif
