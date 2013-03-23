#ifndef GAME_H
#define GAME_H

#include "common.h"
#include "settings.h"
#include "vector.h"
#include "texture.h"
#include "sound.h"
#include "model.h"
#include "car.h"
#include "camera.h"
#include "gui.h"
#include "prop.h"
#include "checkpoint.h"
#include "terrain.h"

struct Game
{
    struct Settings settings;
    struct TextureManager* textureManager;
    SDL_Surface* window;
    struct Camera cameras[2];
    struct SoundManager soundManager;

    struct Vector globalUp;

    float dragConstant;
    float frictionConstant;
    float brakeConstant;
    double gravity;

    int carsNum;
    struct CarPrototype *carPrototypes;
    int selectedCarPrototype;
    struct Car *cars;
    struct Model* carAppearance;
    struct Model* wheelAppearance;

    int propsNum;
    struct Prop *props;

    int checkpointNum;
    struct Checkpoint *checkpoints;
    struct Model* checkpointAppearance;
    struct Model* checkpointFinishAppearance;
    struct Vector checkpointHalfsize;

    int laps;
    double countingDown;

    struct Gui* gui;
    struct Menu *mainMenu;
    struct Menu *settingsMenu;
    struct Menu *keysMenu;

    struct Menu *gameMenu;
    struct Menu *gameChoiceMenu;
    struct Menu *carChoiceMenu;
    struct Menu *mapChoiceMenu;

    struct Terrain terrain;
    char mapFilename[256];

    int editMode;
    int editI; //object enumerator
    char editInfo[32];
    struct BoundingBox editSelector;
    BOOL debug;
};

BOOL mainMenu_resumeGame(SDLKey key, void* arg);
BOOL mainMenu_saveGame(SDLKey key, void* arg);
BOOL mainMenu_loadGame(SDLKey key, void* arg);
BOOL mainMenu_settingsSubmenu(SDLKey key, void* arg);
BOOL mainMenu_exitGame(SDLKey key, void* arg);
BOOL settingsMenu_Back(SDLKey key, void* arg);
BOOL settingsMenu_keysSubmenu(SDLKey key, void* arg);
BOOL settingsMenu_changeCamera(SDLKey key, void* arg);
BOOL settingsMenu_changeMusic(SDLKey key, void* arg);
BOOL settingsMenu_changeSound(SDLKey key, void* arg);

BOOL settingsMenu_changeFullscreen(SDLKey key, void* arg);
BOOL settingsMenu_dbgMode(SDLKey key, void* arg);
BOOL settingsMenu_editMode(SDLKey key, void* arg);
BOOL keysMenu_back(SDLKey key, void* arg);
BOOL keysMenu_changeKey(SDLKey key, void* arg);
BOOL gameMenu_newGame(SDLKey key, void* arg);
BOOL gameMenu_exit(SDLKey key, void* arg);
BOOL gameChoiceMenu_timeTrial(SDLKey key, void* arg);
BOOL gameChoiceMenu_headToHead(SDLKey key, void* arg);
BOOL gameChoiceMenu_back(SDLKey key, void* arg);
BOOL carChoiceMenu_car(SDLKey key, void* arg);
BOOL carChoiceMenu_back(SDLKey key, void* arg);
BOOL mapChoiceMenu_map(SDLKey key, void* arg);
BOOL mapChoiceMenu_back(SDLKey key, void* arg);

void delGame(struct Game* game);
BOOL init(struct Game* game);
BOOL render(struct Game* game);
BOOL procinput(struct Game* game);//return false on end
BOOL update(struct Game* game, double timeStep);
void saveMap(struct Game* game, const char* filename);
void loadMap(struct Game* game, const char* filename);
void saveGame(struct Game* game, const char* filename);
void loadGame(struct Game* game, const char* filename);

#endif /*GAME_H*/
