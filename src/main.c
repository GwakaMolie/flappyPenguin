#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include "functions.h"
#include "eventhandler.h"
#include <time.h>

int winW = 400, winH = 600;

void main(){

    GameState game;

    // video subsystem init && expetion handling
    if(SDL_Init(SDL_INIT_VIDEO) != 0){
        printf("Problem initializing SLD %s\n", SDL_GetError());
    }

    SDL_Window* window = SDL_CreateWindow("game",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          winW,winH,0);

    game.renderer = SDL_CreateRenderer(window,
                                       -1,
                                       SDL_RENDERER_ACCELERATED);

    srand(time(0));
    loadGame(&game, winW);

    while(game.playing){

        Drawing(&game);
        collisionDetect(&game, winH);

        eventHandler(&game);

        processing(&game);
        SDL_Delay(50);
    }

    SDL_DestroyTexture(game.penguin);
    SDL_DestroyTexture(game.topPipe);
    SDL_DestroyTexture(game.bottomPipe);
    SDL_DestroyTexture(game.ground);
    SDL_DestroyRenderer(game.renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

}
