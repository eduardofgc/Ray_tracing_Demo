//g++ -I src/include -L src/lib -o main main.cpp -lmingw32 -lSDL3 (FUNCIONA) [mingw32-make]
//g++ -I src/include -L src/lib -o main main.cpp -lmingw32 -lSDL2main -lSDL2 (ANTIGO)

#include <iostream>
#include <cmath>
#include <SDL3/SDL.h>
#include "util.h"

#define WHITE 0xffffffff

const int WIDTH = 800, HEIGHT = 600;
bool running = true;
int mouseX, mouseY;

int main(int argc, char *argv[]){
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("title", WIDTH, HEIGHT, SDL_WINDOW_HIGH_PIXEL_DENSITY);
    SDL_Surface* mySurface = SDL_GetWindowSurface(window);
    SDL_Event windowEvent;

    if (NULL == window){
        std::cout << "failed to create window\n";
    }

    Circle Ball(400, 300, 100, mySurface, WHITE);

    //main loop
    while (running){

        while (SDL_PollEvent(&windowEvent)){

            if (SDL_EVENT_QUIT == windowEvent.type){
                running = false;
            }

            Ball.FillCircle();


            SDL_UpdateWindowSurface(window);
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}