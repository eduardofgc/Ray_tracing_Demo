//g++ -I src/include -L src/lib -o main main.cpp -lmingw32 -lSDL3 (FUNCIONA) [mingw32-make]
//g++ -I src/include -L src/lib -o main main.cpp -lmingw32 -lSDL2main -lSDL2 (ANTIGO)

#include <iostream>
#include <cmath>
#include <SDL3/SDL.h>
#include "util.h"

#define WHITE 0xffffffff

const int WIDTH = 800, HEIGHT = 600;
bool running = true;
float mouseX, mouseY;

int main(int argc, char *argv[]){
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("ray tracing", WIDTH, HEIGHT, SDL_WINDOW_HIGH_PIXEL_DENSITY);
    SDL_Surface* mySurface = SDL_GetWindowSurface(window);
    SDL_Event windowEvent;

    if (NULL == window){
        std::cout << "failed to create window\n";
    }

    Circle Ball(400, 300, 100, mySurface, WHITE);
    Sun LightSource(200, 150, 50, mySurface, WHITE); //FIXME
    float mouseX, mouseY;

    //main loop
    while (running){

        while (SDL_PollEvent(&windowEvent)){

            if (SDL_EVENT_QUIT == windowEvent.type){
                running = false;
            }
        }

        SDL_ClearSurface(mySurface, 0, 0, 0, 0);

        Ball.FillCircle();
        LightSource.DrawRays(Ball);
        LightSource.FillCircle();

        //drag sun with mouse
        Uint32 buttons = SDL_GetMouseState(&mouseX, &mouseY);

        if (buttons & SDL_BUTTON_LMASK && mouseX >= LightSource.xPos - LightSource.radius && mouseX <= LightSource.xPos + LightSource.radius && mouseY >= LightSource.yPos - LightSource.radius && mouseY <= LightSource.yPos + LightSource.radius){
            LightSource.xPos = mouseX;
            LightSource.yPos = mouseY;
        }

        //move obstacle with wasd
        const bool* keyState = SDL_GetKeyboardState(NULL);

        if (keyState[SDL_SCANCODE_W]){
            Ball.yPos = Ball.yPos - 5;
        }
        if (keyState[SDL_SCANCODE_S]){
            Ball.yPos = Ball.yPos + 5;
        }

        if (keyState[SDL_SCANCODE_A]){
            Ball.xPos = Ball.xPos - 5;
        }
        if (keyState[SDL_SCANCODE_D]){
            Ball.xPos = Ball.xPos + 5;
        }
            
        SDL_UpdateWindowSurface(window);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}