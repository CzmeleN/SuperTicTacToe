#include <SDL3/SDL.h>
#include <cstdlib>

extern "C" void startGame() {
    SDL_Log("Starting the game!");
}

extern "C" void exitGame() {
    SDL_Log("Exiting the game...");
    SDL_Quit();
    exit(0);
}
