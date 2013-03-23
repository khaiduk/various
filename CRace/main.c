#include "common.h"
#include "game.h"

int main (int argc, char *argv[])
{
    BOOL isRunning;
    struct Game game;
    Uint32 lastTimeUpdate, dt;
    Uint32 timeAccumulator = 0;
    Uint32 timeStep = 30;

    if(SDL_Init(SDL_INIT_VIDEO)<0)
    {
        printf("Nie mozna zainicjalizowac SDL\n");
        return -1;
    }
    atexit(SDL_Quit);
    if(!init(&game))
    {
            printf("Wystapil blad");
            exit(EXIT_FAILURE);
    }

    lastTimeUpdate = SDL_GetTicks();

    for(isRunning=TRUE;isRunning;)
    {
        if(!procinput(&game))
            break;

        dt = SDL_GetTicks() - lastTimeUpdate;
        timeAccumulator += dt;
        lastTimeUpdate += dt;
        for(; timeAccumulator > timeStep; timeAccumulator -= timeStep)
        {
            isRunning=update(&game, timeStep);
        }

        isRunning=render(&game);
    }
    delGame(&game);
    return 0;
}
