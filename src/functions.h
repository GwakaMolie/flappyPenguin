#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "struct.h"

void pipesPosRand(PipePair *p){
        //random
        p->topPipe.y = (rand() % 250) * -1;
        p->bottomPipe.y = p->topPipe.y+300+150; //300 >> pipeH 150 >> the gape 

        //printf("t: %d\nb: %d\n\n",p->topPipe.y,p->bottomPipe.y);
}

void loadGame(GameState *game, int scrW){

    game->time = 0;

    game->player.x = 50;
    game->player.y = 200;

    game->player.w = 38;
    game->player.h = 56;

    game->player.dy = 7;
    game->player.angle = 0;
    
    game->groundH = 100;

    game->pipeH = 300;
    game->pipeW = 50;

    for(int i = 0; i < 3; i++){
        pipesPosRand(&game->pipesArr[i]);
    }

    int initx = scrW;

    for(int i = 0; i < 3; i++){
        //CONST
        game->pipesArr[i].topPipe.w = game->pipeW;
        game->pipesArr[i].bottomPipe.w = game->pipeW;
        game->pipesArr[i].topPipe.h = game->pipeH ;
        game->pipesArr[i].bottomPipe.h = game->pipeH;

        game->pipesArr[i].topPipe.x = initx;
        game->pipesArr[i].bottomPipe.x = initx;

        initx += 200;
    }

    game->playing = 1;

    SDL_Surface *penguinSurf = IMG_Load("./assets/b.png");
    game->penguin = SDL_CreateTextureFromSurface(game->renderer, penguinSurf);
    SDL_FreeSurface(penguinSurf);

    SDL_Surface *bgSurf = IMG_Load("./assets/bg.png");
    game->background = SDL_CreateTextureFromSurface(game->renderer, bgSurf);
    SDL_FreeSurface(bgSurf);

    SDL_Surface *groundSurf = IMG_Load("./assets/ground.png");
    game->ground = SDL_CreateTextureFromSurface(game->renderer, groundSurf);
    SDL_FreeSurface(groundSurf);

    SDL_Surface *bpSurf = IMG_Load("./assets/bottom_pipe.png");
    game->bottomPipe = SDL_CreateTextureFromSurface(game->renderer, bpSurf);
    SDL_FreeSurface(bpSurf);

    SDL_Surface *tpSurf = IMG_Load("./assets/top_pipe.png");
    game->topPipe = SDL_CreateTextureFromSurface(game->renderer, tpSurf);
    SDL_FreeSurface(tpSurf);

}


void Drawing(GameState *game){

    SDL_RenderClear(game->renderer);

    SDL_RenderCopy(game->renderer, game->background, NULL, NULL);

    SDL_Rect penguinRect = {game->player.x, game->player.y, game->player.w, game->player.h};
    //SDL_RendererFlip flip = SDL_FLIP_NONE;

    //SDL_RenderCopyEx(game->renderer,
                     //game->penguin,
                     //NULL,
                     //&penguinRect,
                     //game->player.angle,
                     //NULL,
                     //flip);

    SDL_RenderCopy(game->renderer, game->penguin, NULL, &penguinRect);

    for(int i = 0; i < 3; i++){
        SDL_Rect topPipeRect =    {game->pipesArr[i].topPipe.x,
                                   game->pipesArr[i].topPipe.y,
                                   game->pipesArr[i].topPipe.w,
                                   game->pipesArr[i].topPipe.h};

        SDL_Rect bottomPipeRect = {game->pipesArr[i].bottomPipe.x,
                                   game->pipesArr[i].bottomPipe.y,
                                   game->pipesArr[i].bottomPipe.w,
                                   game->pipesArr[i].bottomPipe.h};

        SDL_RenderCopy(game->renderer, game->topPipe, NULL, &topPipeRect);
        SDL_RenderCopy(game->renderer, game->bottomPipe, NULL, &bottomPipeRect);

    }

    SDL_Rect groundRect = {0, 500, 400, game->groundH};
    SDL_RenderCopy(game->renderer, game->ground, NULL, &groundRect);

    SDL_RenderPresent(game->renderer);

}

void processing(GameState *game){
    game->time ++;
    game->player.y += game->player.dy;

    for(int i = 0; i < 3; i++){
        game->pipesArr[i].bottomPipe.x -= 10;
        game->pipesArr[i].topPipe.x -= 10;

        // when the pipe is out of the screen change its y position to 600
        if(game->pipesArr[i].topPipe.x+game->pipeW <= 0){
            game->pipesArr[i].topPipe.x = 600-game->pipeW;
            game->pipesArr[i].bottomPipe.x = 600-game->pipeW;
            pipesPosRand(&game->pipesArr[i]);
        }
    }
}

void collisionDetect(GameState *game, int scrH){

    if(game->player.y+game->player.h >= scrH - game->groundH )
        game->player.y = scrH - game->player.h - game->groundH;
    else if (game->player.y <= 0) 
        game->player.y = 0;

    int pw = game->player.w, ph = game->player.h;

    for(int i = 0; i < 3; i++){

        int px = game->player.x, py = game->player.y;
        int tpx = game->pipesArr[i].topPipe.x, tpy = game->pipesArr[i].topPipe.y;
        int bpx = game->pipesArr[i].bottomPipe.x, bpy = game->pipesArr[i].bottomPipe.y;


        // top pipe coll
        if(px+pw > tpx && px < tpx+game->pipeW && py <= tpy+game->pipeH){ 
            SDL_Delay(400);
            game->playing = 0;
        }
        // bottom pipe coll
        else if(px+pw > bpx && px < bpx+game->pipeW && py+ph > bpy){ 
            SDL_Delay(400);
            game->playing = 0;
        }
    }
}
