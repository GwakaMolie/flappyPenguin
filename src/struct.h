#ifndef struct_h 
#define struct_h

#include <SDL2/SDL.h>

typedef struct{

    int x, y;
    int w, h;

    int dy;
    int angle;

}Banana;

typedef struct{
    int x, y;
    int w, h;

}Pipe;

typedef struct{
    Pipe bottomPipe;
    Pipe topPipe;

}PipePair;
typedef struct{

    int time;

    int playing;
    int groundH;
    int pipeH, pipeW;

    Banana player;
    PipePair pipes;

    PipePair pipesArr[3];

    SDL_Renderer *renderer;

    SDL_Texture *penguin;
    SDL_Texture *background;
    SDL_Texture *ground;
    SDL_Texture *bottomPipe;
    SDL_Texture *topPipe;

}GameState;

#endif
