#include "struct.h"

void eventHandler(GameState *game){

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch(event.type){
            case SDL_QUIT:{
                game->playing = 0;
                break;
              }
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym){
                    case SDLK_ESCAPE:{
                        game->playing = 0;
                        break;
                    }
                    case SDLK_SPACE:{
                        game->player.y -= 50;
                    }
                }
        }
    }
}

