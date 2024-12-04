#include <iostream>
#include <vector>

#include "headers/complex.h"
#include <SDL2/SDL.h>

using std::min;
using std::vector;

const int HEIGHT = 400;
const int WIDTH = 400;

double ZOOM = 100;
double SHIFT_X = 0.01;
double SHIFT_Y = -0.01;

int* generate_mandelbrot(int n) {
    int* pixels = new int[WIDTH * HEIGHT];

    for (int x = 0; x < WIDTH; x++) {
        for (int y = 0; y < HEIGHT; y++) {
            // std::cout << x << ", " << y << std::endl;
            double xc = ((double) (x) - WIDTH / 2) / ZOOM - 0.75 + SHIFT_X;
            double yc = ((double) (y) - WIDTH / 2) / ZOOM + SHIFT_Y;

            int iter = complex::test(
                new complex(0, 0),
                new complex(xc, yc),
                n
            );

            if (iter == n) {
                pixels[x + y * WIDTH] = 0x00000000;
            } else {
                int color = 0xFF000000;
                color |= min(51 + iter * 5, 255) << 16; 
                color |= min(41 + iter * 5, 255) << 8;
                color |= min(240 + iter * 5, 255);

                pixels[x + y * WIDTH] = color;
            }
        }
    }

    return pixels;
}

int main(int argc, char *argv[]) {
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window *window = SDL_CreateWindow(
        "SDL", 
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
        WIDTH, HEIGHT, 
        SDL_WINDOW_ALLOW_HIGHDPI
    );

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_RenderSetLogicalSize(renderer, WIDTH, HEIGHT);
    
    SDL_Texture* texture = 	texture = SDL_CreateTexture(
        renderer, 
        SDL_PIXELFORMAT_ARGB8888, 
        SDL_TEXTUREACCESS_STREAMING, 
        WIDTH, HEIGHT
    );

    if (window == NULL) return 1;

    SDL_Event event;
    bool running = true;
    while (running) {
        SDL_UpdateTexture(texture, nullptr, generate_mandelbrot(50), WIDTH * sizeof(unsigned int));
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, nullptr, nullptr);
        SDL_RenderPresent(renderer);

        ZOOM += 2;
        SHIFT_Y += 0.001;
        SHIFT_Y += 0.001;

        if (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT: { 
                    running = false;
                    break;
                }

                case SDL_KEYDOWN: { 
                    switch (event.key.keysym.sym) {
                        case SDLK_ESCAPE: {
                            running = false;
                            break;
                        }

                        default: { break; }
                    }
                }

                default: { break; }
            }
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}