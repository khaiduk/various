#include "game.h"

/*MENU ITEMS*/
BOOL mainMenu_resumeGame(SDLKey key, void* arg)
{
    struct Gui* gui = (struct Gui*)(arg);
    if(SDLK_SPACE  == key || SDLK_RETURN == key)
    {
        gui->currentMenu = NULL;
    }
    return TRUE;
}

BOOL mainMenu_saveGame(SDLKey key, void* arg)
{
    struct Game* game = (struct Game*)(arg);
    if(SDLK_SPACE  == key || SDLK_RETURN == key)
    {
        saveGame(game, "game.sav");
    }
    return TRUE;
}

BOOL mainMenu_loadGame(SDLKey key, void* arg)
{
    struct Game* game = (struct Game*)(arg);
    if(SDLK_SPACE  == key || SDLK_RETURN == key)
    {
        loadGame(game, "game.sav");
        game->gui->currentMenu = NULL;
    }
    return TRUE;
}

BOOL mainMenu_settingsSubmenu(SDLKey key, void* arg)
{
    struct Game* game = (struct Game*)(arg);
    if(SDLK_SPACE  == key || SDLK_RETURN == key)
    {
        game->gui->currentMenu = game->settingsMenu;
        game->gui->currentMenu->currentItem = 0;
    }
    return TRUE;
}

BOOL mainMenu_exitGame(SDLKey key, void* arg)
{
    struct Game* game = (struct Game*)(arg);
    if(SDLK_SPACE  == key || SDLK_RETURN == key)
    {
        game->gui->currentMenu = game->gameMenu;
        game->carsNum = 0;
        game->gui->currentMenu->currentItem = 0;
    }
    return TRUE;
}

BOOL settingsMenu_keysSubmenu(SDLKey key, void* arg)
{
    struct Game* game = (struct Game*)(arg);
    if(SDLK_SPACE  == key || SDLK_RETURN == key)
    {
        game->gui->currentMenu = game->keysMenu;
        game->gui->currentMenu->currentItem = 0;
    }
    return TRUE;
}

BOOL settingsMenu_Back(SDLKey key, void* arg)
{
    struct Game* game = (struct Game*)(arg);
    if(SDLK_SPACE  == key || SDLK_RETURN == key)
    {
        if(game->carsNum>0)
            game->gui->currentMenu = game->mainMenu;
        else
            game->gui->currentMenu = game->gameMenu;
    }
    return TRUE;

}

BOOL settingsMenu_changeCamera(SDLKey key, void* arg)
{
    struct Game* game = (struct Game*)(arg);
    if(SDLK_SPACE  == key || SDLK_RETURN == key || SDLK_LEFT  == key || SDLK_RIGHT  == key)
    {
        if(CAMERA_MODE_FIXED == game->cameras[0].mode)
        {
            game->cameras[0].mode = CAMERA_MODE_TPP;
            game->cameras[1].mode = CAMERA_MODE_TPP;
            strcpy(game->gui->currentMenu->items[game->gui->currentMenu->currentItem].text, "Camera: TPP");
        }
        else /*(CAMERA_MODE_TPP == game->camera.mode)*/
        {
            game->cameras[0].mode = CAMERA_MODE_FIXED;
            game->cameras[1].mode = CAMERA_MODE_FIXED;
            strcpy(game->gui->currentMenu->items[game->gui->currentMenu->currentItem].text, "Camera: Fixed");
        }
    }
    return TRUE;

}

BOOL settingsMenu_changeFullscreen(SDLKey key, void* arg)
{
    struct Game* game = (struct Game*)(arg);
    if(SDLK_SPACE  == key || SDLK_RETURN == key || SDLK_LEFT  == key || SDLK_RIGHT  == key)
    {
        if(game->settings.windowFullscreen)
        {
            game->settings.windowFullscreen = FALSE;
            strcpy(game->gui->currentMenu->items[game->gui->currentMenu->currentItem].text, "Fullscreen: False");
        }
        else
        {
            game->settings.windowFullscreen = TRUE;
            strcpy(game->gui->currentMenu->items[game->gui->currentMenu->currentItem].text, "Fullscreen: True");
        }
    }
    return TRUE;

}

BOOL settingsMenu_changeMusic(SDLKey key, void* arg)
{
    struct Game* game = (struct Game*)(arg);
    if(SDLK_LEFT  == key)
    {
        game->settings.musicVolmue -= 5;
        if(game->settings.musicVolmue<0)
            game->settings.musicVolmue = 0;
        sprintf(game->gui->currentMenu->items[game->gui->currentMenu->currentItem].text,
                "Music: %d%%", game->settings.musicVolmue);

    }
    else if(SDLK_RIGHT == key)
    {
        game->settings.musicVolmue += 5;
        if(game->settings.musicVolmue>100)
            game->settings.musicVolmue = 100;
        sprintf(game->gui->currentMenu->items[game->gui->currentMenu->currentItem].text,
                "Music: %d%%", game->settings.musicVolmue);
    }
    soundManagerUpdateVolmue(&game->soundManager);
    return TRUE;
}

BOOL settingsMenu_changeSound(SDLKey key, void* arg)
{
    struct Game* game = (struct Game*)(arg);
    if(SDLK_LEFT  == key)
    {
        game->settings.fxVolmue -= 5;
        if(game->settings.fxVolmue<0)
            game->settings.fxVolmue = 0;
        sprintf(game->gui->currentMenu->items[game->gui->currentMenu->currentItem].text,
                "Sound: %d%%", game->settings.fxVolmue);

    }
    else if(SDLK_RIGHT == key)
    {
        game->settings.fxVolmue += 5;
        if(game->settings.fxVolmue>100)
            game->settings.fxVolmue = 100;
        sprintf(game->gui->currentMenu->items[game->gui->currentMenu->currentItem].text,
                "Sound: %d%%", game->settings.fxVolmue);
    }
    soundManagerUpdateVolmue(&game->soundManager);
    return TRUE;
}

BOOL keysMenu_back(SDLKey key, void* arg)
{
    struct Game* game = (struct Game*)(arg);
    if(SDLK_SPACE  == key || SDLK_RETURN == key)
    {
        game->gui->currentMenu = game->settingsMenu;
    }
    return TRUE;
}

BOOL keysMenu_changeKey(SDLKey key, void* arg)
{
    struct Game* game = (struct Game*)(arg);
    char *txt = game->gui->currentMenu->items[abs(game->gui->currentMenu->currentItem)].text;

    if(game->gui->currentMenu->currentItem<0)
    {
        game->gui->currentMenu->currentItem = -game->gui->currentMenu->currentItem;
        game->settings.keys[(game->gui->currentMenu->currentItem-1)/4][(game->gui->currentMenu->currentItem-1)%4] = key;
        sprintf(txt, "%s %s", txt, SDL_GetKeyName(key));
    }
    else if(SDLK_SPACE  == key || SDLK_RETURN == key)
    {
        txt = strchr(txt, ':') + 1;
        *txt = '\0';
        game->gui->currentMenu->currentItem = -game->gui->currentMenu->currentItem;
    }
    return TRUE;
}

BOOL settingsMenu_dbgMode(SDLKey key, void* arg)
{
    struct Game* game = (struct Game*)(arg);
    if(SDLK_SPACE  == key || SDLK_RETURN == key || SDLK_LEFT  == key || SDLK_RIGHT  == key)
    {
        if(game->debug)
        {
            game->debug = FALSE;
            strcpy(game->gui->currentMenu->items[game->gui->currentMenu->currentItem].text, "Debug Mode: No");
            glClearColor(0.7f, 0.9f, 1.0f, 0.5f);
        }
        else
        {
            game->debug = TRUE;
            strcpy(game->gui->currentMenu->items[game->gui->currentMenu->currentItem].text, "Debug Mode: Yes");
            glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
        }
    }
    return TRUE;

}

BOOL settingsMenu_editMode(SDLKey key, void* arg)
{
    struct Game* game = (struct Game*)(arg);
    if(SDLK_SPACE  == key || SDLK_RETURN == key || SDLK_LEFT  == key || SDLK_RIGHT  == key)
    {
        if(game->editMode)
        {
            game->editMode = 0;
            strcpy(game->gui->currentMenu->items[game->gui->currentMenu->currentItem].text, "Edit Mode: No");
        }
        else
        {
            game->editMode = 1;
            strcpy(game->gui->currentMenu->items[game->gui->currentMenu->currentItem].text, "Edit Mode: Yes");
            game->editSelector = newBoundingBox();
        }
    }
    return TRUE;

}

BOOL gameMenu_newGame(SDLKey key, void* arg)
{
    struct Game* game = (struct Game*)(arg);
    if(SDLK_SPACE  == key || SDLK_RETURN == key)
    {
        game->gui->currentMenu = game->gameChoiceMenu;
        game->gui->currentMenu->currentItem = 0;
    }
    return TRUE;
}

BOOL gameMenu_exit(SDLKey key, void* arg)
{
    if(SDLK_SPACE  == key || SDLK_RETURN == key)
    {
        return FALSE;
    }
    return TRUE;
}

BOOL gameChoiceMenu_timeTrial(SDLKey key, void* arg)
{
    struct Game* game = (struct Game*)(arg);
    if(SDLK_SPACE  == key || SDLK_RETURN == key)
    {
        game->carsNum = 1;
        game->gui->currentMenu = game->carChoiceMenu;
        game->gui->currentMenu->currentItem = 0;
    }
    return TRUE;
}

BOOL gameChoiceMenu_headToHead(SDLKey key, void* arg)
{
    struct Game* game = (struct Game*)(arg);
    if(SDLK_SPACE  == key || SDLK_RETURN == key)
    {
        game->carsNum = 2;
        game->gui->currentMenu = game->carChoiceMenu;
        game->gui->currentMenu->currentItem = 0;
    }
    return TRUE;
}

BOOL gameChoiceMenu_back(SDLKey key, void* arg)
{
    struct Game* game = (struct Game*)(arg);
    if(SDLK_SPACE  == key || SDLK_RETURN == key)
    {
        game->gui->currentMenu = game->gameMenu;
        game->gui->currentMenu->currentItem = 0;
    }
    return TRUE;
}

BOOL carChoiceMenu_car(SDLKey key, void* arg)
{
    struct Game* game = (struct Game*)(arg);
    if(SDLK_SPACE  == key || SDLK_RETURN == key)
    {
        char buffer[256];
        sprintf(buffer, "car%d.obj", game->gui->currentMenu->currentItem);
        delmodel(game->carAppearance);
        game->carAppearance = modelLoadFromFile(buffer, game->textureManager);
        game->selectedCarPrototype = game->gui->currentMenu->currentItem;
        game->gui->currentMenu = game->mapChoiceMenu;
        game->gui->currentMenu->currentItem = 0;
    }
    return TRUE;
}

BOOL carChoiceMenu_back(SDLKey key, void* arg)
{
    struct Game* game = (struct Game*)(arg);
    if(SDLK_SPACE  == key || SDLK_RETURN == key)
    {
        game->gui->currentMenu = game->gameChoiceMenu;
        game->gui->currentMenu->currentItem = 0;
    }
    return TRUE;
}

BOOL mapChoiceMenu_map(SDLKey key, void* arg)
{
    struct Game* game = (struct Game*)(arg);
    if(SDLK_SPACE  == key || SDLK_RETURN == key)
    {
        char buffer[256];
        sprintf(buffer, "map%d.map", game->gui->currentMenu->currentItem);
        loadMap(game, buffer);
        game->gui->currentMenu = NULL;
    }
    return TRUE;
}

BOOL mapChoiceMenu_back(SDLKey key, void* arg)
{
    struct Game* game = (struct Game*)(arg);
    if(SDLK_SPACE  == key || SDLK_RETURN == key)
    {
        game->gui->currentMenu = game->carChoiceMenu;
        game->gui->currentMenu->currentItem = 0;
    }
    return TRUE;
}
/*END MENU ITEMS*/

void delGame(struct Game* game)
{
    int i;
    settingsSave(game->settings, "settings.txt");

    delTerrain(game->terrain);

    if(game->carAppearance)
        delmodel(game->carAppearance);
    if(game->wheelAppearance)
        delmodel(game->wheelAppearance);
    if(game->carPrototypes)
        free(game->carPrototypes);
    if(game->cars)
        free(game->cars);
    for(i=0;i<game->propsNum;i++)
        delmodel(game->props[i].appearance);
    if(game->props)
        free(game->props);
    if(game->checkpointAppearance)
        delmodel(game->checkpointAppearance);
    if(game->checkpoints)
        free(game->checkpoints);
    delTextureManager(game->textureManager);

    if(game->mainMenu)
        delMenu(game->mainMenu);
    if(game->settingsMenu)
        delMenu(game->settingsMenu);
    if(game->keysMenu)
        delMenu(game->keysMenu);
    if(game->gameMenu)
        delMenu(game->gameMenu);
    if(game->gameChoiceMenu)
        delMenu(game->gameChoiceMenu);
    if(game->carChoiceMenu)
        delMenu(game->carChoiceMenu);
    if(game->mapChoiceMenu)
        delMenu(game->mapChoiceMenu);

    delGui(game->gui);

    alutExit();
}

BOOL init(struct Game* game)
{
    int i;
    struct MenuItem menuItem;

    game->settings = settingsLoad("settings.txt");

    game->soundManager = newSoundManager(&game->settings);

    game->window = SDL_SetVideoMode(game->settings.windowWidth, game->settings.windowHeigth,
                                    game->settings.windowBits, SDL_OPENGL | (game->settings.windowFullscreen?SDL_FULLSCREEN:0));
    SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_ALPHA_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
    SDL_GL_SetAttribute( SDL_GL_STENCIL_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
    SDL_WM_SetCaption ("CRace", NULL);

    glViewport(0,0,game->window->w,game->window->h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f,(float)game->window->w/(float)game->window->h,0.1f,100.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glShadeModel(GL_SMOOTH);
    glClearColor(0.7f, 0.9f, 1.0f, 0.5f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_COLOR_MATERIAL);

    glEnable(GL_LIGHTING);
    GLfloat ambientLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat  diffuseLight[] = { 0.7f, 0.7f, 0.7f, 1.0f };
    GLfloat lightPos[] = { 50.f, 50.0f, 0.0f, 1.0f };
    glLightfv(GL_LIGHT0,GL_AMBIENT,ambientLight);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuseLight);
    glLightfv(GL_LIGHT0,GL_POSITION,lightPos);
    glEnable(GL_LIGHT0);

    game->globalUp = vectorZero();
    game->globalUp.y = 1;

    game->frictionConstant = 0.5;
    game->dragConstant = game->frictionConstant/30;
    game->brakeConstant = 0.01;
    game->gravity = 0.00098;

    if(!(game->textureManager = newTextureManager()))
    {
        printf("Nie mozna zaalokowac menadzera tekstur");
        return FALSE;
    }

    if(!(game->gui = newGui(game->textureManager, game->window->w, game->window->h)))
    {
        printf("Nie mozna zaalokowac interfejsu");
        delGame(game);
        return FALSE;
    }

    game->carsNum = 0;

    game->cars = malloc(2 * sizeof *game->cars);
    if(!game->cars)
    {
        printf("init: cannot alocate memory");
        delGame(game);
        return FALSE;
    }

    game->terrain = newTerrain(game->textureManager);
    strncpy(game->mapFilename, "mapa.map", 256);
    game->carAppearance = modelLoadFromFile("car0.obj", game->textureManager);
    game->wheelAppearance = modelLoadFromFile("wheel.obj", game->textureManager);

    for(i=0;i<2;i++)
    {
        game->cars[i]=newCar(newCarPrototype());
        game->cars[i].position.z = i*5;
        game->cars[i].lastBoundingBox = carBoundingBox(&game->cars[i]);
        game->cars[i].nextCheckpoint = 0;
    }

    game->propsNum = 5;

    game->props = malloc(game->propsNum * sizeof *game->props);
    if(!game->props)
    {
        printf("init: cannot alocate memory");
        delGame(game);
        return FALSE;
    }

    for(i=0;i<game->propsNum;i++)
    {
        game->props[i]=newProp();
        if(!(game->props[i].appearance = modelLoadFromFile("dom.obj", game->textureManager)))
        {
            game->propsNum = i-1;
            delGame(game);
            return FALSE;
        }
        game->props[i].position.z=-15;
        game->props[i].position.x=-20+15*i;
        game->props[i].position.y= terrainGetHeight(&game->terrain, game->props[i].position.x, game->props[i].position.z)-1;
    }


    game->checkpointNum = 5;
    game->checkpointHalfsize.x = 1;
    game->checkpointHalfsize.y = 6;
    game->checkpointHalfsize.z = 7;
    game->checkpoints = malloc(game->checkpointNum * sizeof *game->checkpoints);
    if(!game->checkpoints)
    {
        printf("init: cannot alocate memory");
        delGame(game);
        return FALSE;
    }
    if(!(game->checkpointAppearance = modelLoadFromFile("checkpoint.obj", game->textureManager)))
    {
        delGame(game);
        return FALSE;
    }
    if(!(game->checkpointFinishAppearance = modelLoadFromFile("checkerboard.obj", game->textureManager)))
    {
        delGame(game);
        return FALSE;
    }
    for(i=0;i<game->checkpointNum;i++)
    {
        game->checkpoints[i]=newCheckpoint();
        game->checkpoints[i].position.z= (0==i || 3==i || 4==i) ? 0: -30;
        game->checkpoints[i].position.x= (0==i || 1==i) ? 40: ( 4==i ? 0 : -20 );
        game->checkpoints[i].position.y= terrainGetHeight(&game->terrain, game->checkpoints[i].position.x, game->checkpoints[i].position.z);
    }

    game->cameras[0].position.x=0;
    game->cameras[0].position.y=10;
    game->cameras[0].position.z=10;
    game->cameras[0].mode = CAMERA_MODE_TPP;

    game->cameras[1].position.x=0;
    game->cameras[1].position.y=10;
    game->cameras[1].position.z=10;
    game->cameras[1].mode = CAMERA_MODE_TPP;

    game->countingDown = -3;

    game->mainMenu = newMenu("== Paused ==");

    strcpy(menuItem.text, "Resume");
    menuItem.proc = mainMenu_resumeGame;
    menuItem.arg = game->gui;
    menuAddMenuItem(game->mainMenu, menuItem);

    strcpy(menuItem.text, "Save");
    menuItem.proc = mainMenu_saveGame;
    menuItem.arg = game;
    menuAddMenuItem(game->mainMenu, menuItem);

    strcpy(menuItem.text, "Load");
    menuItem.proc = mainMenu_loadGame;
    menuItem.arg = game;
    menuAddMenuItem(game->mainMenu, menuItem);

    strcpy(menuItem.text, "Settings");
    menuItem.proc = mainMenu_settingsSubmenu;
    menuItem.arg = game;
    menuAddMenuItem(game->mainMenu, menuItem);

    strcpy(menuItem.text, "Exit");
    menuItem.proc = mainMenu_exitGame;
    menuItem.arg = game;
    menuAddMenuItem(game->mainMenu, menuItem);


    game->settingsMenu = newMenu("Settings");

    strcpy(menuItem.text, "Keys");
    menuItem.proc = settingsMenu_keysSubmenu;
    menuItem.arg = game;
    menuAddMenuItem(game->settingsMenu, menuItem);

    strcpy(menuItem.text, "Camera: TPP");
    menuItem.proc = settingsMenu_changeCamera;
    menuItem.arg = game;
    menuAddMenuItem(game->settingsMenu, menuItem);

    strcpy(menuItem.text, game->settings.windowFullscreen?"Fullscreen: True":"Fullscreen: False");
    menuItem.proc = settingsMenu_changeFullscreen;
    menuItem.arg = game;
    menuAddMenuItem(game->settingsMenu, menuItem);

    sprintf(menuItem.text, "Music: %d%%", game->settings.musicVolmue);
    menuItem.proc = settingsMenu_changeMusic;
    menuItem.arg = game;
    menuAddMenuItem(game->settingsMenu, menuItem);

    sprintf(menuItem.text, "Sound: %d%%", game->settings.fxVolmue);
    menuItem.proc = settingsMenu_changeSound;
    menuItem.arg = game;
    menuAddMenuItem(game->settingsMenu, menuItem);

    strcpy(menuItem.text, "Debug Mode: No");
    menuItem.proc = settingsMenu_dbgMode;
    menuItem.arg = game;
    menuAddMenuItem(game->settingsMenu, menuItem);

    strcpy(menuItem.text, "Edit Mode: No");
    menuItem.proc = settingsMenu_editMode;
    menuItem.arg = game;
    menuAddMenuItem(game->settingsMenu, menuItem);

    strcpy(menuItem.text, "Back");
    menuItem.proc = settingsMenu_Back;
    menuItem.arg = game;
    menuAddMenuItem(game->settingsMenu, menuItem);

    game->keysMenu = newMenu("Keys");

    strcpy(menuItem.text, "Back");
    menuItem.proc = keysMenu_back;
    menuItem.arg = game;
    menuAddMenuItem(game->keysMenu, menuItem);

    for(i=0;i<2;i++)
    {
        int j;
        char k[4][6] = { "Up   ", "Down ", "Left ", "Right"};
        for(j=0;j<4;j++)
        {
            sprintf(menuItem.text, "P%d %s: %s", i, k[j], SDL_GetKeyName(game->settings.keys[i][j]));
            menuItem.proc = keysMenu_changeKey;
            menuItem.arg = game;
            menuAddMenuItem(game->keysMenu, menuItem);
        }
    }


    game->gameMenu = newMenu("Main menu");

    strcpy(menuItem.text, "New Game");
    menuItem.proc = gameMenu_newGame;
    menuItem.arg = game;
    menuAddMenuItem(game->gameMenu, menuItem);

    strcpy(menuItem.text, "Load Game");
    menuItem.proc = mainMenu_loadGame;
    menuItem.arg = game;
    menuAddMenuItem(game->gameMenu, menuItem);


    strcpy(menuItem.text, "Settings");
    menuItem.proc = mainMenu_settingsSubmenu;
    menuItem.arg = game;
    menuAddMenuItem(game->gameMenu, menuItem);

    strcpy(menuItem.text, "Exit");
    menuItem.proc = gameMenu_exit;
    menuItem.arg = NULL;
    menuAddMenuItem(game->gameMenu, menuItem);


    game->gameChoiceMenu = newMenu("Choose game mode");

    strcpy(menuItem.text, "Time trial");
    menuItem.proc = gameChoiceMenu_timeTrial;
    menuItem.arg = game;
    menuAddMenuItem(game->gameChoiceMenu, menuItem);

    strcpy(menuItem.text, "Head To Head");
    menuItem.proc = gameChoiceMenu_headToHead;
    menuItem.arg = game;
    menuAddMenuItem(game->gameChoiceMenu, menuItem);

    strcpy(menuItem.text, "Back");
    menuItem.proc = gameChoiceMenu_back;
    menuItem.arg = game;
    menuAddMenuItem(game->gameChoiceMenu, menuItem);


    game->carChoiceMenu = newMenu("Choose car");


    FILE *carsFile = fopen("cars.txt","r");
    if(!carsFile)
    {
        printf("init: cannot open cars file");
        delGame(game);
        return FALSE;
    }
    int carProtoNum;
    fscanf(carsFile, "%d\n", &carProtoNum);
    game->carPrototypes = malloc(carProtoNum * sizeof *game->carPrototypes);
    if(!game->carPrototypes)
    {
        printf("init: cannot alocate memory");
        delGame(game);
        return FALSE;
    }
    for(i=0;i<carProtoNum;i++)
    {
        fgets(menuItem.text, 256, carsFile);
        fscanf(carsFile, "%lg %lg %lg %lg %lg %lg\n",
               &game->carPrototypes[i].halfSize.x, &game->carPrototypes[i].halfSize.y, &game->carPrototypes[i].halfSize.z,
               &game->carPrototypes[i].wheelsPos.x, &game->carPrototypes[i].wheelsPos.y, &game->carPrototypes[i].wheelsPos.z);
        menuItem.proc = carChoiceMenu_car;
        menuItem.arg = game;
        menuAddMenuItem(game->carChoiceMenu, menuItem);
    }

    strcpy(menuItem.text, "Back");
    menuItem.proc = carChoiceMenu_back;
    menuItem.arg = game;
    menuAddMenuItem(game->carChoiceMenu, menuItem);


    game->mapChoiceMenu = newMenu("Choose map");

    FILE *mapsFile = fopen("maps.txt","r");
    if(!mapsFile)
    {
        printf("init: cannot open maps file");
    }
    int mapsNum;

    fscanf(mapsFile, "%d\n", &mapsNum);
    for(i=0;i<mapsNum;i++)
    {
        fgets(menuItem.text, 256, mapsFile);
        menuItem.proc = mapChoiceMenu_map;
        menuItem.arg = game;
        menuAddMenuItem(game->mapChoiceMenu, menuItem);
    }
    fclose(mapsFile);

    strcpy(menuItem.text, "Back");
    menuItem.proc = mapChoiceMenu_back;
    menuItem.arg = game;
    menuAddMenuItem(game->mapChoiceMenu, menuItem);

    game->gui->currentMenu = game->gameMenu;
    game->gui->currentMenu->currentItem = 0;

    game->debug = FALSE;
    game->editMode = FALSE;
    game->editI = 0;
    game->editSelector = newBoundingBox();
    strcpy(game->editInfo, "editMode on");

    return TRUE;
}

BOOL render(struct Game* game)
{
    int i,j,c;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    if(game->gui->currentMenu == game->gameMenu ||
       game->gui->currentMenu == game->gameChoiceMenu ||
       game->gui->currentMenu == game->carChoiceMenu ||
       game->gui->currentMenu == game->mapChoiceMenu ||
       0==game->carsNum)
    {
        guiShowMenu(game->gui);
        if(game->gui->currentMenu == game->gameMenu)
        {
            game->gui->image = getTexture(game->textureManager, "logo.bmp", TRUE);
            guiDrawImage(game->gui, 350, 200, 300, 300);
        }
        else if(game->gui->currentMenu == game->gameChoiceMenu)
        {
            switch(game->gui->currentMenu->currentItem)
            {
                case 0:
                    game->gui->image = getTexture(game->textureManager, "time.bmp", TRUE);
                    break;
                case 1:
                    game->gui->image = getTexture(game->textureManager, "duel.bmp", TRUE);
                    break;
                case 2: default:
                    game->gui->image = getTexture(game->textureManager, "back.bmp", TRUE);
                    break;
            }
            guiDrawImage(game->gui, 350, 200, 300, 300);
        }
        else if(game->gui->currentMenu == game->carChoiceMenu)
        {
            if(game->gui->currentMenu->currentItem == game->gui->currentMenu->itemsNum - 1)
                game->gui->image = getTexture(game->textureManager, "back.bmp", TRUE);
            else
            {
                char filename[256];
                sprintf(filename, "car%d.bmp", game->gui->currentMenu->currentItem);
                game->gui->image = getTexture(game->textureManager, filename, TRUE);

            }
            guiDrawImage(game->gui, 350, 200, 300, 300);
        }
        else if(game->gui->currentMenu == game->mapChoiceMenu)
        {
            if(game->gui->currentMenu->currentItem == game->gui->currentMenu->itemsNum - 1)
                game->gui->image = getTexture(game->textureManager, "back.bmp", TRUE);
            else
            {
                char filename[256];
                sprintf(filename, "map%d.bmp", game->gui->currentMenu->currentItem);
                game->gui->image = getTexture(game->textureManager, filename, TRUE);

            }
            guiDrawImage(game->gui, 350, 200, 300, 300);
        }
        SDL_GL_SwapBuffers( );
        return TRUE;
    }

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f,(float)game->window->w/(float)game->window->h*game->carsNum,0.1f,100.0f);
    glMatrixMode(GL_MODELVIEW);

    for(c=0;c<game->carsNum;c++)
    {
        glViewport(0,(game->carsNum-(c+1))*game->window->h/game->carsNum,game->window->w,game->window->h/game->carsNum);
        glLoadIdentity();

        if(game->editMode)
            gluLookAt(game->cameras[c].position.x,game->cameras[c].position.y,game->cameras[c].position.z,
                      game->editSelector.position.x,game->editSelector.position.y,game->editSelector.position.z,
                      0,1,0);
        else
            gluLookAt(game->cameras[c].position.x,game->cameras[c].position.y,game->cameras[c].position.z,
                      game->cars[c].position.x,game->cars[c].position.y,game->cars[c].position.z,
                      0,1,0);
        /*GROUND*/
        if(! game->debug)
        {
            terrainRender(&game->terrain);
        }


        for(i=0;i<game->carsNum;i++)
        {
            if(game->debug)
            {
                carRender(&game->cars[i], game->carAppearance, game->wheelAppearance);
                glDisable(GL_TEXTURE_2D);
                struct BoundingBox bb= carBoundingBox(&game->cars[i]);
                boundingBoxRender(&bb);
                glEnable(GL_TEXTURE_2D);
            }
            else
                carRender(&game->cars[i], game->carAppearance, game->wheelAppearance);
        }

        for(i=0;i<game->propsNum;i++)
        {
            if(game->debug)
            {
                glDisable(GL_TEXTURE_2D);
                struct BoundingBox bb= propBoundingBox(&game->props[i]);
                boundingBoxRender(&bb);
                glEnable(GL_TEXTURE_2D);
            }
            else
            {
                glPushMatrix();
                glTranslatef(game->props[i].position.x,game->props[i].position.y,game->props[i].position.z);
                vectorMulMatrixCoords(game->props[i].direction, game->props[i].up);;
                modelDisplay(game->props[0].appearance);
                glPopMatrix();
            }
        }

        i=game->cars[c].nextCheckpoint;
        if(i < game->checkpointNum-1)
        {
            glPushMatrix();
            glTranslatef(game->checkpoints[i].position.x,game->checkpoints[i].position.y,game->checkpoints[i].position.z);
            struct Vector globalUp = vectorZero();
            globalUp.y=1.0;
            vectorMulMatrixCoords(game->checkpoints[i].direction, globalUp);
            glEnable( GL_BLEND );
            glBlendFunc( GL_DST_COLOR, GL_SRC_ALPHA );
            modelDisplay(game->checkpointAppearance);
            glDisable( GL_BLEND );
            glPopMatrix();
        }

        glPushMatrix();
        glTranslatef(game->checkpoints[game->checkpointNum-1].position.x,
                     game->checkpoints[game->checkpointNum-1].position.y,
                     game->checkpoints[game->checkpointNum-1].position.z);
        struct Vector globalUp = vectorZero();
        globalUp.y=1.0;
        vectorMulMatrixCoords(game->checkpoints[game->checkpointNum-1].direction, globalUp);
        modelDisplay(game->checkpointFinishAppearance);
        glPopMatrix();

        if(game->editMode)
        {
            if(4 == game->editMode)
            game->editSelector.position.y = terrainGetHeight(&game->terrain, game->editSelector.position.x, game->editSelector.position.z);
            boundingBoxRender(&game->editSelector);
        }
    }



    glViewport(0,0,game->window->w,game->window->h);
    if(!game->editMode)
    {
        if(game->countingDown<1)
        {
            if(game->countingDown<0 )
            {
                guiDrawRect(game->gui, game->gui->w/2, game->gui->h/2 - 15, 30, 30, 1, 1, 1);
                guiPrintf(game->gui, game->gui->w/2, game->gui->h/2 - 15, "%.0f", -game->countingDown);
            }
            else
            {
                guiDrawRect(game->gui, game->gui->w/2 - 50, game->gui->h/2 - 15, 100, 30, 1, 1, 1);
                guiPrintf(game->gui, game->gui->w/2 - 50, game->gui->h/2 - 15, "START");
            }
        }

        if(1 == game->carsNum && game->cars[0].lap > game->laps)
        {
            guiDrawRect(game->gui, game->gui->w/2 - 50, game->gui->h/2 - 30, 200, 60, 1, 1, 1);
            guiPrintf(game->gui, game->gui->w/2 - 50, game->gui->h/2 - 30, "your time:");
            guiPrintf(game->gui, game->gui->w/2 - 50, game->gui->h/2, "%6.2f", game->cars[0].raceTime);
        }
        else if(2 == game->carsNum)
        {
            if(game->cars[0].lap > game->laps)
            {
                guiDrawRect(game->gui, game->gui->w/2 - 50, game->gui->h*1/4 - 15, 160, 30, 1, 1, 1);
                if(game->cars[0].raceTime < game->cars[1].raceTime)
                    guiPrintf(game->gui, game->gui->w/2 - 50, game->gui->h*1/4 - 15, "You  win");
                else
                    guiPrintf(game->gui, game->gui->w/2 - 50, game->gui->h*1/4 - 15, "You lose");

            }
            if(game->cars[1].lap > game->laps)
            {
                guiDrawRect(game->gui, game->gui->w/2 - 50, game->gui->h*3/4 - 15, 160, 30, 1, 1, 1);
                if(game->cars[0].raceTime > game->cars[1].raceTime)
                    guiPrintf(game->gui, game->gui->w/2 - 50, game->gui->h*3/4 - 15, "You  win");
                else
                    guiPrintf(game->gui, game->gui->w/2 - 50, game->gui->h*3/4 - 15, "You lose");

            }
        }

        for(i=0;i<game->terrain.height;i++)
        {
            for(j=0;j<game->terrain.width; j++)
            {
                float r, g, b;
                if('*'==game->terrain.texmap[i][j])
                {
                    r = 0.3;
                    g = 0.8;
                    b = 0.3;
                }
                else
                {
                    r = 0.2;
                    g = 0.2;
                    b = 0.2;
                }
                guiDrawRect(game->gui, game->gui->w - 135 + 3*j, 15 + 3*i, 3, 3, r, g, b);
            }
        }
        guiDrawRect(game->gui, game->gui->w - 135 + 3*(game->cars[0].position.x/TILE_SIZE + game->terrain.width/2)-1,
                    15 + 3*(game->cars[0].position.z/TILE_SIZE + game->terrain.height/2)-1, 4, 4, 1.0, 0.0, 0.2);
        if(2 == game->carsNum)
            guiDrawRect(game->gui, game->gui->w - 135 + 3*(game->cars[1].position.x/TILE_SIZE + game->terrain.width/2)-1,
                        15 + 3*(game->cars[1].position.z/TILE_SIZE + game->terrain.height/2)-1, 4, 4, 0.2, 0.0, 1.0);


        for(c=0;c<game->carsNum;c++)
        {
            guiDrawRect(game->gui, game->gui->w - 140,  (c+1)*game->gui->h/game->carsNum - 38, 140, 20, 0.8, 1, 0.8);
            guiPrintf(game->gui, game->gui->w - 140, (c+1)*game->gui->h/game->carsNum - 40, "Lap %d/%d", game->cars[c].lap, game->laps);

            guiDrawRect(game->gui, 15, (c+1)*game->gui->h/game->carsNum - 88, 320, 80, 0.8, 1, 0.8);
            guiPrintf(game->gui, 15, (c+1)*game->gui->h/game->carsNum - 90, "Race time:%6.2f", game->cars[c].raceTime);
            guiPrintf(game->gui, 15, (c+1)*game->gui->h/game->carsNum - 60, "Lap time: %6.2f", game->cars[c].currentTime);
            guiPrintf(game->gui, 15, (c+1)*game->gui->h/game->carsNum - 30, "Best lap: %6.2f", game->cars[c].bestTime);

            guiDrawRect(game->gui, 15, (c+1)*game->gui->h/game->carsNum - 120, 300, 30, 1, 0.3, 0.2);
            guiDrawRect(game->gui, 15, (c+1)*game->gui->h/game->carsNum - 120, fabs(vectorDot(game->cars[c].velocity, game->cars[c].direction))*50*300, 30, 0, 1, 0);
        }
    }
    else
    {
        guiDrawRect(game->gui, 15, game->gui->h - 58, 440, 50, 1, 1, 1);
        guiPrintf(game->gui, 15, game->gui->h - 60, "EDIT MODE:");
        guiPrintf(game->gui, 15, game->gui->h - 30, game->editInfo);
    }
    guiShowMenu(game->gui);
    SDL_GL_SwapBuffers( );
    return TRUE;
}

BOOL procinput(struct Game* game)
{
    SDL_Event event;
    static Uint8 keyState[SDLK_LAST] = {0};
    while(SDL_PollEvent (&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                return FALSE;
            case SDL_KEYDOWN:
                keyState[event.key.keysym.sym] = 1;
                if(game->gui->currentMenu == game->keysMenu && game->gui->currentMenu->currentItem < 0)
                {
                    if(! guiClickMenuItem(game->gui, event.key.keysym.sym) )
                        return FALSE;
                }
                else if(SDLK_ESCAPE == event.key.keysym.sym)
                {
                    if(game->gui->currentMenu == game->gameMenu ||
                       game->gui->currentMenu == game->gameChoiceMenu ||
                       game->gui->currentMenu == game->carChoiceMenu ||
                       game->gui->currentMenu == game->mapChoiceMenu ||
                       0 == game->carsNum)
                    {
                        soundManagerClick(&game->soundManager);
                        if( (game->gui->currentMenu == game->keysMenu && game->gui->currentMenu->currentItem == 0) ||
                           game->gui->currentMenu->currentItem == game->gui->currentMenu->itemsNum-1)
                        {
                            if(! guiClickMenuItem(game->gui, SDLK_RETURN) )
                                return FALSE;
                        }
                        else
                        {
                            if(game->gui->currentMenu == game->keysMenu)
                                game->gui->currentMenu->currentItem = 0;
                            else
                                game->gui->currentMenu->currentItem = game->gui->currentMenu->itemsNum-1;
                        }

                    }
                    else if(!(game->gui->currentMenu))
                    {
                        game->gui->currentMenu = game->mainMenu;
                        game->gui->currentMenu->currentItem = 0;
                    }
                    else
                    {
                        soundManagerClick(&game->soundManager);
                        game->gui->currentMenu = NULL;
                    }
                }
                else if(SDLK_UP == event.key.keysym.sym)
                {
                    if(game->gui->currentMenu)
                    {
                        soundManagerClick(&game->soundManager);
                        guiPrevMenuItem(game->gui);
                    }
                    else if(game->editMode)
                    {
                        game->cameras[0].position.x += TILE_SIZE;
                        game->cameras[1].position.x += TILE_SIZE;
                    }
                }
                else if(SDLK_DOWN == event.key.keysym.sym)
                {
                    if(game->gui->currentMenu)
                    {
                        soundManagerClick(&game->soundManager);
                        guiNextMenuItem(game->gui);
                    }
                    else if(game->editMode)
                    {
                        game->cameras[0].position.x -= TILE_SIZE;
                        game->cameras[1].position.x -= TILE_SIZE;
                    }
                }
                else if(game->editMode)
                {
                    if(SDLK_LEFT == event.key.keysym.sym)
                    {
                        game->cameras[0].position.z -= TILE_SIZE;
                        game->cameras[1].position.z -= TILE_SIZE;
                    }
                    else if(SDLK_RIGHT == event.key.keysym.sym)
                    {
                        game->cameras[0].position.z += TILE_SIZE;
                        game->cameras[1].position.z += TILE_SIZE;
                    }
                    else if(SDLK_1 == event.key.keysym.sym)
                    {

                        strcpy(game->editInfo, "car start pos 1");
                        game->editMode = 1;
                        game->editI = 0;
                        game->editSelector = carBoundingBox(&game->cars[0]);
                    }
                    else if(SDLK_2 == event.key.keysym.sym)
                    {
                        strcpy(game->editInfo, "car start pos 2");
                        game->editMode = 2;
                        game->editI = 0;
                        game->editSelector = carBoundingBox(&game->cars[1]);
                    }
                    else if(SDLK_3 == event.key.keysym.sym)
                    {
                        strcpy(game->editInfo, "props");
                        game->editMode = 3;
                        if(game->propsNum > 0)
                        {
                            game->editI = 0;
                            game->editSelector = propBoundingBox(&game->props[game->editI]);
                        }
                        else
                        {
                            game->editI = -1;
                            game->editSelector = newBoundingBox();
                        }
                    }
                    else if(SDLK_4 == event.key.keysym.sym)
                    {
                        strcpy(game->editInfo, "terrain");
                        game->editMode = 4;
                        game->editSelector = newBoundingBox();
                    }
                    else if(SDLK_5 == event.key.keysym.sym)
                    {
                        strcpy(game->editInfo, "checkpoints");
                        game->editMode = 5;
                        if(game->checkpointNum > 0)
                        {
                            game->editI = 0;
                            game->editSelector = checkpointBoundingBox(game->checkpoints[game->editI], game->checkpointHalfsize);
                        }
                        else
                        {
                            game->editI = -1;
                            game->editSelector = newBoundingBox();
                        }
                    }
                    else if(SDLK_q == event.key.keysym.sym && game->editI>=0)
                    {
                        if(3==game->editMode)
                        {
                            game->editI--;
                            if(game->editI<0)
                                game->editI = game->propsNum-1;
                            game->editSelector = propBoundingBox(&game->props[game->editI]);
                        }
                        if(5==game->editMode)
                        {
                            game->editI--;
                            if(game->editI<0)
                                game->editI = game->checkpointNum-1;
                            game->editSelector = checkpointBoundingBox(game->checkpoints[game->editI], game->checkpointHalfsize);
                        }
                        sprintf(game->editInfo, "%d",  game->editI);
                    }
                    else if(SDLK_e == event.key.keysym.sym && game->editI>=0)
                    {
                        if(3==game->editMode)
                        {
                            game->editI++;
                            if(game->editI>=game->propsNum)
                                game->editI = 0;
                            game->editSelector = propBoundingBox(&game->props[game->editI]);
                        }
                        if(5==game->editMode)
                        {
                            game->editI++;
                            if(game->editI>=game->checkpointNum)
                                game->editI = 0;
                            game->editSelector = checkpointBoundingBox(game->checkpoints[game->editI], game->checkpointHalfsize);
                        }
                        sprintf(game->editInfo, "%d",  game->editI);
                    }
                    else if(SDLK_a == event.key.keysym.sym && game->editI>=0)
                    {
                        if(4==game->editMode)
                            game->editSelector.position.z += TILE_SIZE;
                        else
                            game->editSelector.position.z += 1.0;
                        if(1 == game->editMode)
                            carRestoreBoundingBox(&game->cars[0], game->editSelector);
                        else if(2 == game->editMode)
                            carRestoreBoundingBox(&game->cars[1], game->editSelector);
                        else if(3 == game->editMode)
                            propRestoreBoundingBox(&game->props[game->editI], game->editSelector);
                        else if(5 == game->editMode)
                            checkpointRestoreBoundingBox(&game->checkpoints[game->editI], game->editSelector);
                        sprintf(game->editInfo, "%f, %f, %f", game->editSelector.position.x, game->editSelector.position.y, game->editSelector.position.z);
                    }
                    else if(SDLK_d == event.key.keysym.sym && game->editI>=0)
                    {
                        if(4==game->editMode)
                            game->editSelector.position.z -= TILE_SIZE;
                        else
                            game->editSelector.position.z -= 1.0;
                        if(1 == game->editMode)
                            carRestoreBoundingBox(&game->cars[0], game->editSelector);
                        else if(2 == game->editMode)
                            carRestoreBoundingBox(&game->cars[1], game->editSelector);
                        else if(3 == game->editMode)
                            propRestoreBoundingBox(&game->props[game->editI], game->editSelector);
                        else if(5 == game->editMode)
                            checkpointRestoreBoundingBox(&game->checkpoints[game->editI], game->editSelector);
                        sprintf(game->editInfo, "%f, %f, %f", game->editSelector.position.x, game->editSelector.position.y, game->editSelector.position.z);
                    }
                    else if(SDLK_w == event.key.keysym.sym && game->editI>=0)
                    {
                        if(4==game->editMode)
                            game->editSelector.position.x += TILE_SIZE;
                        else
                            game->editSelector.position.x += 1.0;
                        if(1 == game->editMode)
                            carRestoreBoundingBox(&game->cars[0], game->editSelector);
                        else if(2 == game->editMode)
                            carRestoreBoundingBox(&game->cars[1], game->editSelector);
                        else if(3 == game->editMode)
                            propRestoreBoundingBox(&game->props[game->editI], game->editSelector);
                        else if(5 == game->editMode)
                            checkpointRestoreBoundingBox(&game->checkpoints[game->editI], game->editSelector);
                        sprintf(game->editInfo, "%f, %f, %f", game->editSelector.position.x, game->editSelector.position.y, game->editSelector.position.z);
                    }
                    else if(SDLK_s == event.key.keysym.sym && game->editI>=0)
                    {
                        if(4==game->editMode)
                            game->editSelector.position.x -= TILE_SIZE;
                        else
                            game->editSelector.position.x -= 1.0;
                        if(1 == game->editMode)
                            carRestoreBoundingBox(&game->cars[0], game->editSelector);
                        else if(2 == game->editMode)
                            carRestoreBoundingBox(&game->cars[1], game->editSelector);
                        else if(3 == game->editMode)
                            propRestoreBoundingBox(&game->props[game->editI], game->editSelector);
                        else if(5 == game->editMode)
                            checkpointRestoreBoundingBox(&game->checkpoints[game->editI], game->editSelector);
                        sprintf(game->editInfo, "%f, %f, %f", game->editSelector.position.x, game->editSelector.position.y, game->editSelector.position.z);
                    }
                    else if(SDLK_r == event.key.keysym.sym && 4!=game->editMode && game->editI>=0)
                    {
                        game->editSelector.position.y += 1.0;
                        if(1 == game->editMode)
                            carRestoreBoundingBox(&game->cars[0], game->editSelector);
                        else if(2 == game->editMode)
                            carRestoreBoundingBox(&game->cars[1], game->editSelector);
                        else if(3 == game->editMode)
                            propRestoreBoundingBox(&game->props[game->editI], game->editSelector);
                        else if(5 == game->editMode)
                            checkpointRestoreBoundingBox(&game->checkpoints[game->editI], game->editSelector);
                        sprintf(game->editInfo, "%f, %f, %f", game->editSelector.position.x, game->editSelector.position.y, game->editSelector.position.z);
                    }
                    else if(SDLK_f == event.key.keysym.sym && 4!=game->editMode && game->editI>=0)
                    {
                        game->editSelector.position.y -= 1.0;
                        if(1 == game->editMode)
                            carRestoreBoundingBox(&game->cars[0], game->editSelector);
                        else if(2 == game->editMode)
                            carRestoreBoundingBox(&game->cars[1], game->editSelector);
                        else if(3 == game->editMode)
                            propRestoreBoundingBox(&game->props[game->editI], game->editSelector);
                        else if(5 == game->editMode)
                            checkpointRestoreBoundingBox(&game->checkpoints[game->editI], game->editSelector);
                        sprintf(game->editInfo, "%f, %f, %f", game->editSelector.position.x, game->editSelector.position.y, game->editSelector.position.z);
                    }
                    else if(SDLK_z == event.key.keysym.sym && 4!=game->editMode && game->editI>=0)
                    {
                        game->editSelector.direction = vectorRotate(0.1, game->editSelector.up, game->editSelector.direction);
                        if(1 == game->editMode)
                            carRestoreBoundingBox(&game->cars[0], game->editSelector);
                        else if(2 == game->editMode)
                            carRestoreBoundingBox(&game->cars[1], game->editSelector);
                        else if(3 == game->editMode)
                            propRestoreBoundingBox(&game->props[game->editI], game->editSelector);
                        else if(5 == game->editMode)
                            checkpointRestoreBoundingBox(&game->checkpoints[game->editI], game->editSelector);
                        sprintf(game->editInfo, "%f, %f, %f", game->editSelector.position.x, game->editSelector.position.y, game->editSelector.position.z);
                    }
                    else if(SDLK_x == event.key.keysym.sym && 4!=game->editMode && game->editI>=0)
                    {
                        game->editSelector.direction = vectorRotate(-0.1, game->editSelector.up, game->editSelector.direction);
                        if(1 == game->editMode)
                            carRestoreBoundingBox(&game->cars[0], game->editSelector);
                        else if(2 == game->editMode)
                            carRestoreBoundingBox(&game->cars[1], game->editSelector);
                        else if(3 == game->editMode)
                            propRestoreBoundingBox(&game->props[game->editI], game->editSelector);
                        else if(5 == game->editMode)
                            checkpointRestoreBoundingBox(&game->checkpoints[game->editI], game->editSelector);
                        sprintf(game->editInfo, "%f, %f, %f", game->editSelector.position.x, game->editSelector.position.y, game->editSelector.position.z);
                    }
                    else if(SDLK_c == event.key.keysym.sym && 4!=game->editMode && 5!=game->editMode && game->editI>=0)
                    {
                        game->editSelector.up = vectorRotate(-0.1, game->editSelector.direction, game->editSelector.up);
                        if(1 == game->editMode)
                            carRestoreBoundingBox(&game->cars[0], game->editSelector);
                        else if(2 == game->editMode)
                            carRestoreBoundingBox(&game->cars[1], game->editSelector);
                        else if(3 == game->editMode)
                            propRestoreBoundingBox(&game->props[game->editI], game->editSelector);
                        sprintf(game->editInfo, "%f, %f, %f", game->editSelector.position.x, game->editSelector.position.y, game->editSelector.position.z);
                    }
                    else if(SDLK_v == event.key.keysym.sym && 4!=game->editMode && 5!=game->editMode && game->editI>=0)
                    {
                        game->editSelector.up = vectorRotate(0.1, game->editSelector.direction, game->editSelector.up);
                        if(1 == game->editMode)
                            carRestoreBoundingBox(&game->cars[0], game->editSelector);
                        else if(2 == game->editMode)
                            carRestoreBoundingBox(&game->cars[1], game->editSelector);
                        else if(3 == game->editMode)
                            propRestoreBoundingBox(&game->props[game->editI], game->editSelector);
                        sprintf(game->editInfo, "%f, %f, %f", game->editSelector.position.x, game->editSelector.position.y, game->editSelector.position.z);
                    }
                    else if(SDLK_EQUALS == event.key.keysym.sym && (1==game->editMode || 2==game->editMode))
                    {
                        struct BoundingBox bb = newBoundingBox();
                        bb.halfSize = game->editSelector.halfSize;
                        bb.position.y=5;
                        game->editSelector = bb;
                        if(1 == game->editMode)
                            carRestoreBoundingBox(&game->cars[0], game->editSelector);
                        else if(2 == game->editMode)
                            carRestoreBoundingBox(&game->cars[1], game->editSelector);
                    }
                    else if(SDLK_EQUALS == event.key.keysym.sym && 3==game->editMode)
                    {
                        struct Prop *props;
                        game->propsNum++;
                        props = realloc(game->props, game->propsNum * sizeof *game->props);
                        if(!props)
                        {
                            game->propsNum--;
                            sprintf(game->editInfo, "cannot add prop");
                        }
                        else
                        {
                            game->props = props;
                            game->editI = game->propsNum - 1;
                            game->props[game->editI]=newProp();
                            if(!(game->props[game->editI].appearance = modelLoadFromFile("dom.obj", game->textureManager)))
                            {
                                game->propsNum--;
                                game->props = realloc(game->props, game->propsNum * sizeof *game->props);
                                sprintf(game->editInfo, "cannot add prop");
                            }
                            else
                            {
                                game->editSelector = propBoundingBox(&game->props[game->editI]);
                                sprintf(game->editInfo, "added prop: %d", game->editI);
                            }
                        }
                    }
                    else if(SDLK_EQUALS == event.key.keysym.sym && 5==game->editMode)
                    {
                        struct Checkpoint *checkpoints;
                        game->checkpointNum++;
                        checkpoints = realloc(game->checkpoints, game->checkpointNum * sizeof *game->checkpoints);
                        if(!checkpoints)
                        {
                            game->checkpointNum--;
                            sprintf(game->editInfo, "cannot add checkpoint");
                        }
                        else
                        {
                            game->checkpoints = checkpoints;
                            game->editI = game->checkpointNum - 1;
                            game->checkpoints[game->editI]=newCheckpoint();
                            game->editSelector = checkpointBoundingBox(game->checkpoints[game->editI], game->checkpointHalfsize);
                            sprintf(game->editInfo, "added checkpoint: %d", game->editI);
                        }
                    }
                    else if(SDLK_MINUS == event.key.keysym.sym && 3==game->editMode && game->propsNum>0)
                    {
                        delmodel(game->props[game->editI].appearance);
                        game->props[game->editI] = game->props[game->propsNum-1];
                        game->propsNum--;
                        game->props = realloc(game->props, game->propsNum * sizeof *game->props);
                        if( game->propsNum>0)
                            game->editSelector = propBoundingBox(&game->props[game->editI]);
                        else
                            game->editI = -1;
                    }
                    else if(SDLK_MINUS == event.key.keysym.sym && 5==game->editMode && game->checkpointNum>1)
                    {
                        game->checkpointNum--;
                        game->checkpoints = realloc(game->checkpoints, game->checkpointNum * sizeof *game->checkpoints);
                        game->editI = game->checkpointNum - 1;
                        if( game->checkpointNum>0)
                            game->editSelector = checkpointBoundingBox(game->checkpoints[game->editI], game->checkpointHalfsize);
                        else
                            game->editI = -1;
                    }
                    else if(SDLK_r == event.key.keysym.sym && 4==game->editMode)
                    {
                        int i = game->editSelector.position.x/TILE_SIZE + game->terrain.width/2;
                        int j = game->editSelector.position.z/TILE_SIZE + game->terrain.height/2;
                        game->terrain.heightmap[j][i]+=0.25;
                        sprintf(game->editInfo, "%f", game->terrain.heightmap[j][i]);
                    }
                    else if(SDLK_f == event.key.keysym.sym && 4==game->editMode)
                    {
                        int i = game->editSelector.position.x/TILE_SIZE + game->terrain.width/2;
                        int j = game->editSelector.position.z/TILE_SIZE + game->terrain.height/2;
                        game->terrain.heightmap[j][i]-=0.25;
                        sprintf(game->editInfo, "%f", game->terrain.heightmap[j][i]);
                    }
                    else if(SDLK_v == event.key.keysym.sym && 4==game->editMode)
                    {
                        int i = game->editSelector.position.x/TILE_SIZE + game->terrain.width/2;
                        int j = game->editSelector.position.z/TILE_SIZE + game->terrain.height/2;
                        if('*'==game->terrain.texmap[j][i])
                            game->terrain.texmap[j][i]='#';
                        else if('#'==game->terrain.texmap[j][i])
                            game->terrain.texmap[j][i]='|';
                        else if('|'==game->terrain.texmap[j][i])
                            game->terrain.texmap[j][i]='-';
                        else if('-'==game->terrain.texmap[j][i])
                            game->terrain.texmap[j][i]='*';
                        sprintf(game->editInfo, "%c", game->terrain.texmap[j][i]);
                    }
                    else if(SDLK_m == event.key.keysym.sym)
                    {
                        saveMap(game, "saved_map.map");
                    }
                    else
                        if(game->gui->currentMenu)
                            if(! guiClickMenuItem(game->gui, event.key.keysym.sym) )
                                return FALSE;
                }
                else
                {
                    if(game->gui->currentMenu)
                    {
                        soundManagerClick(&game->soundManager);
                        if(! guiClickMenuItem(game->gui, event.key.keysym.sym) )
                            return FALSE;
                    }
                }

                break;
            case SDL_KEYUP:
                keyState[event.key.keysym.sym] = 0;
                break;
            default:
                break;
        }
    }

    if(!(game->gui->currentMenu) && game->countingDown>=0)
    {
        int i;
        for(i=0;i<game->carsNum;i++)
        {
            game->cars[i].throttle = 0;
            game->cars[i].turn = 0;
            game->cars[i].brake = FALSE;

            if(keyState[game->settings.keys[i][KEY_LEFT]])
                game->cars[i].turn += 1;
            if(keyState[game->settings.keys[i][KEY_RIGHT]])
                game->cars[i].turn -= 1;
            if(keyState[game->settings.keys[i][KEY_UP]])
                game->cars[i].throttle += 0.1;
            if(keyState[game->settings.keys[i][KEY_DOWN]])
                game->cars[i].throttle -= 0.1;
        }

    }

    return TRUE;
}

BOOL update(struct Game* game, double timeStep)
{
    if(NULL != game->gui->currentMenu)
    {
        soundManagerPlayMusic(&game->soundManager);
        soundManagerEngine(&game->soundManager, 0, 0);
        soundManagerEngine(&game->soundManager, 1, 0);
    }
    else
    {
        int c;
        soundManagerStopMusic(&game->soundManager);
        for(c=0;c<game->carsNum;c++)
            soundManagerEngine(&game->soundManager, c, fabs(vectorDot(game->cars[c].velocity, game->cars[c].direction))*50);
    }

    if(CAMERA_MODE_TPP == game->cameras[0].mode)
    {
        int i;
        for(i=0;i<game->carsNum;i++)
        {
            struct Vector dir = game->cars[i].direction;
            if(vectorDot(game->cars[i].direction, game->cars[i].velocity)<-0.001)
            dir = vectorTimes(dir, -1);

            if(!game->editMode)
            {
                cameraFollow(&game->cameras[i], game->cars[i].position, dir, 15);
            }

        }
    }
    else
    {
        struct Vector pos;
        pos.x = 0;
        pos.z = 15;
        pos.y = 15;
        if(!game->editMode)
        {
            game->cameras[0].position = pos;
            game->cameras[1].position = pos;
        }
    }
    if(NULL == game->gui->currentMenu && !game->editMode)
    {
        game->countingDown += timeStep/1000;
        if(game->countingDown<0)
        {
            return TRUE;
        }
        int i, car_i;
        for(car_i=0;car_i<game->carsNum;car_i++)
        {
            carZeroForce(&game->cars[car_i]);
        }
        /* FORCES: */
        for(car_i=0;car_i<game->carsNum;car_i++)
        {
            struct Vector gravity = vectorTimes(game->globalUp, - 1 * game->gravity * game->cars[car_i].mass);
            carApplyForce(&game->cars[car_i], gravity, vectorZero()); // gravity


            for(i=0;i<WHEELS_NUM;i++)
            {
                struct Vector offset = vectorAdd( vectorTimes(game->cars[car_i].direction,
                                                              game->cars[car_i].wheels[i].offset.z),
                                       vectorAdd( vectorTimes(game->cars[car_i].up,
                                                              game->cars[car_i].wheels[i].offset.y),
                                                vectorTimes(vectorCross(game->cars[car_i].direction, game->cars[car_i].up),
                                                            game->cars[car_i].wheels[i].offset.x )));
                                      // offset in global frame of reference

                struct Vector velo = game->cars[car_i].velocity;
                velo = vectorAdd(velo, vectorTimes(vectorCross(game->cars[car_i].angularVelocity, offset), 0.005)); // velocity of wheel

                //suspension
                double k = 0.063;
                double x = -terrainGetHeight(&game->terrain, game->cars[car_i].position.x + offset.x,game->cars[car_i].position.z + offset.z)
                            +game->cars[car_i].position.y + offset.y;
                if(x<0) x=0;
                x-=4.2;
                struct Vector response = vectorTimes(game->globalUp,-k*x);
                carApplyForce(&game->cars[car_i], response, offset);

                //suspension dapming
                double c = 2;
                double v = velo.y;
                struct Vector damping = vectorTimes(game->globalUp,-c*v);
                carApplyForce(&game->cars[car_i], damping, offset);

                offset.y= 0;//assume wheel if on ground
                // traction
                if(game->cars[car_i].wheels[i].drive)
                {
                    double rpm = 0.05;
                    struct Vector driveForce = vectorTimes(game->cars[car_i].direction, game->cars[car_i].throttle * rpm);
                    carApplyForce(&game->cars[car_i], driveForce, offset);
                }

                // cornering
                double wheelAngle = game->cars[car_i].wheels[i].drive? 0 : -game->cars[car_i].wheelAngle;
                struct Vector wheelDir = vectorRotate(wheelAngle, game->cars[car_i].up ,game->cars[car_i].direction);
                wheelDir.y = 0;
                struct Vector wheelRight = vectorCross(wheelDir, game->cars[car_i].up);
                wheelRight = vectorNormalize(wheelRight);
                velo.y = 0;
                if(vectorLength(velo)>0.01)
                    velo = vectorNormalize(velo);
                else
                    velo = vectorTimes(velo, 100);
                struct Vector corneringForce = vectorTimes( wheelRight, vectorDot(wheelRight, velo) * -0.1);
                carApplyForce(&game->cars[car_i], corneringForce, offset);

                game->cars[car_i].wheels[i].ypos = 0.5 + terrainGetHeight(&game->terrain, game->cars[car_i].position.x + offset.x, game->cars[car_i].position.z + offset.z);
            }
            carApplyForce(&game->cars[car_i],
                          vectorTimes(game->cars[car_i].velocity, -1*game->dragConstant* vectorLength(game->cars[car_i].velocity)),
                          vectorZero()); // drag
            carApplyForce(&game->cars[car_i], vectorTimes(game->cars[car_i].velocity, -1*game->frictionConstant), vectorZero()); // friction

            if( vectorLength(game->cars[car_i].velocity) > 0 && game->cars[car_i].brake)
            {
                struct Vector brakeForce = vectorTimes(vectorNormalize(game->cars[car_i].velocity), -1*game->brakeConstant);
                brakeForce.y = 0;
                carApplyForce(&game->cars[car_i], brakeForce, vectorZero()); // brake
            }
            if(game->cars[car_i].turn > EPSILON)
            {
                game->cars[car_i].wheelAngle += 0.01;
            }
            else if(game->cars[car_i].turn < -EPSILON)
            {
                game->cars[car_i].wheelAngle -= 0.01;
            }
            else
            {
                if(game->cars[car_i].wheelAngle > EPSILON) game->cars[car_i].wheelAngle -= 0.01;
                else if(game->cars[car_i].wheelAngle < -EPSILON) game->cars[car_i].wheelAngle += 0.01;
            }
            if(game->cars[car_i].wheelAngle > 0.1)
                game->cars[car_i].wheelAngle=0.1;
            if(game->cars[car_i].wheelAngle < -0.1)
                game->cars[car_i].wheelAngle=-0.1;
        }

        /* COLISIONS: */
        for(car_i=0;car_i<game->carsNum;car_i++)
        {
            struct Vector collisionPoint;
            struct Vector collisionNormal;
            for(i=car_i+1;i<game->carsNum;i++)
            {
                if(vectorLength(vectorSub(game->cars[car_i].position,game->cars[i].position)) < 5)
                {
                    if(boundingBoxCollide(carBoundingBox(&game->cars[car_i]), carBoundingBox(&game->cars[i])))
                    {
                        soundManagerCrash(&game->soundManager);

                        boundingBoxCollisionPoint(&collisionNormal,&collisionPoint,game->cars[car_i].lastBoundingBox, game->cars[i].lastBoundingBox ,carBoundingBox(&game->cars[car_i]), carBoundingBox(&game->cars[i]));

                        carRestoreBoundingBox(&game->cars[car_i], game->cars[car_i].lastBoundingBox);
                        carRestoreBoundingBox(&game->cars[i], game->cars[i].lastBoundingBox);
                        struct Vector r_a = vectorSub(game->cars[car_i].position,collisionPoint);
                        struct Vector r_b = vectorSub(game->cars[i].position,collisionPoint);
                        r_a.y = game->cars[car_i].position.y;
                        r_b.y = game->cars[i].position.y;
                        struct Vector v_a = vectorAdd(game->cars[car_i].velocity, vectorTimes(vectorCross(game->cars[car_i].angularVelocity, r_a), 0.005));
                        struct Vector v_b = vectorAdd(game->cars[i].velocity, vectorTimes(vectorCross(game->cars[i].angularVelocity, r_b), 0.005));
                        struct Vector v_ab = vectorSub(v_a, v_b);
                        double impulse = 1.5*vectorDot(v_ab,collisionNormal)/2;
                        game->cars[car_i].velocity = vectorAdd(game->cars[car_i].velocity, vectorTimes(collisionNormal, -impulse));
                        game->cars[car_i].angularVelocity = vectorAdd(game->cars[car_i].angularVelocity, vectorTimes(vectorCross(r_a, collisionNormal), -impulse));
                        game->cars[i].velocity = vectorAdd(game->cars[i].velocity, vectorTimes(collisionNormal, impulse));
                        game->cars[i].angularVelocity = vectorAdd(game->cars[car_i].angularVelocity, vectorTimes(vectorCross(r_b, collisionNormal), impulse));
                    }
                }

            }

            for(i=0;i<game->propsNum;i++)
            {
                if(boundingBoxCollide(propBoundingBox(&game->props[i]), carBoundingBox(&game->cars[car_i])))
                {
                    soundManagerCrash(&game->soundManager);
                    boundingBoxCollisionPoint(&collisionNormal,&collisionPoint,game->cars[car_i].lastBoundingBox, propBoundingBox(&game->props[i]) ,carBoundingBox(&game->cars[car_i]), propBoundingBox(&game->props[i]));
                    carRestoreBoundingBox(&game->cars[car_i], game->cars[car_i].lastBoundingBox);
                    struct Vector r = vectorSub(game->cars[car_i].position,collisionPoint);
                    r.y = game->cars[car_i].position.y;
                    struct Vector v = vectorAdd(game->cars[car_i].velocity, vectorTimes(vectorCross(game->cars[car_i].angularVelocity, r), 0.005));
                    double impulse = 1.5*vectorDot(v,collisionNormal);
                    game->cars[car_i].velocity = vectorAdd(game->cars[car_i].velocity, vectorTimes(collisionNormal, -impulse));
                    game->cars[car_i].angularVelocity = vectorAdd(game->cars[car_i].angularVelocity, vectorTimes(vectorCross(r, collisionNormal), -impulse));
                }
            }
        }

        /* INTEGRATING */
        for(car_i=0;car_i<game->carsNum;car_i++)
        {
            game->cars[car_i].lastBoundingBox = carBoundingBox(&game->cars[car_i]);
            game->cars[car_i].angularVelocity = vectorAdd(game->cars[car_i].angularVelocity, game->cars[car_i].torque);
            game->cars[car_i].direction = vectorRotate( vectorLength(game->cars[car_i].angularVelocity),
                                                   game->cars[car_i].angularVelocity, game->cars[car_i].direction);
            game->cars[car_i].up = vectorRotate( vectorLength(game->cars[car_i].angularVelocity), game->cars[car_i].angularVelocity, game->cars[car_i].up);

            game->cars[car_i].velocity = vectorAdd(game->cars[car_i].velocity, vectorTimes(game->cars[car_i].force, timeStep/game->cars[car_i].mass));
            game->cars[car_i].velocity = vectorRotate( vectorLength(game->cars[car_i].angularVelocity),
                                                  game->cars[car_i].angularVelocity, game->cars[car_i].velocity);

            game->cars[car_i].wheelRotate += vectorDot(game->cars[car_i].direction, game->cars[car_i].velocity)*600; /*rolling wheels*/

            game->cars[car_i].position = vectorAdd(game->cars[car_i].position, vectorTimes(game->cars[car_i].velocity, timeStep));

        }

        for(car_i=0;car_i<game->carsNum;car_i++)
        {
            if(boundingBoxCollide(carBoundingBox(&game->cars[car_i]),
                                  checkpointBoundingBox(game->checkpoints[game->cars[car_i].nextCheckpoint], game->checkpointHalfsize)))
            {
                game->cars[car_i].nextCheckpoint++;
                if(game->cars[car_i].nextCheckpoint == game->checkpointNum && game->cars[car_i].lap <= game->laps)
                {
                    game->cars[car_i].lap++;

                    if(game->cars[car_i].lap > game->laps)
                    {
                        game->cars[car_i].nextCheckpoint = game->checkpointNum - 1; // set checkpoint to finish line
                    }
                    else
                    {
                        game->cars[car_i].nextCheckpoint = 0;
                    }
                    if(game->cars[car_i].currentTime < game->cars[car_i].bestTime || game->cars[car_i].bestTime < EPSILON)
                    {
                        game->cars[car_i].bestTime = game->cars[car_i].currentTime;
                    }
                    game->cars[car_i].currentTime = 0;
                }
            }

            if(game->cars[car_i].lap <= game->laps)
            {
                game->cars[car_i].currentTime += timeStep/1000;
                game->cars[car_i].raceTime += timeStep/1000;
            }
        }
    }
    return TRUE;
}

void saveMap(struct Game* game, const char* filename)
{
    int i,j;
    FILE *file = fopen(filename,"w");
    if(!file)
    {
        printf("saveMap: cannot open file");
        return;
    }

    fprintf(file, "%lg %lg %lg %lg %lg %lg %lg %lg %lg\n",
            game->cars[0].position.x, game->cars[0].position.y, game->cars[0].position.z,
            game->cars[0].direction.x, game->cars[0].direction.y, game->cars[0].direction.z,
            game->cars[0].up.x, game->cars[0].up.y, game->cars[0].up.z);
    fprintf(file, "%lg %lg %lg %lg %lg %lg %lg %lg %lg\n",
            game->cars[1].position.x,   game->cars[1].position.y,   game->cars[1].position.z,
            game->cars[1].direction.x,  game->cars[1].direction.y,  game->cars[1].direction.z,
            game->cars[1].up.x,         game->cars[1].up.y,         game->cars[1].up.z);
    fprintf(file, "%d\n", game->propsNum);
    for(i=0;i<game->propsNum;i++)
    {
        fprintf(file, "%s\n", game->props[i].appearance->filename);
        fprintf(file, "%lg %lg %lg %lg %lg %lg %lg %lg %lg\n",
                game->props[i].position.x,   game->props[i].position.y,   game->props[i].position.z,
                game->props[i].direction.x,  game->props[i].direction.y,  game->props[i].direction.z,
                game->props[i].up.x,         game->props[i].up.y,         game->props[i].up.z);
        fprintf(file, "%lg %lg %lg\n",
                game->props[i].halfSize.x, game->props[i].halfSize.y, game->props[i].halfSize.z);
    }
    fprintf(file, "%d\n", game->laps);
    fprintf(file, "%d\n", game->checkpointNum);
    for(i=0;i<game->checkpointNum;i++)
    {
        fprintf(file, "%lg %lg %lg %lg %lg %lg\n",
                game->checkpoints[i].position.x,   game->checkpoints[i].position.y,   game->checkpoints[i].position.z,
                game->checkpoints[i].direction.x,  game->checkpoints[i].direction.y,  game->checkpoints[i].direction.z);
    }
    for(i=0;i<game->terrain.height;i++)
    {
        for(j=0;j<game->terrain.width;j++)
            fprintf(file, "%c", game->terrain.texmap[i][j]);
        fprintf(file,"\n");
    }
    for(i=0;i<game->terrain.height;i++)
    {
        for(j=0;j<game->terrain.width;j++)
            fprintf(file, "%c", (char)(game->terrain.heightmap[i][j]*4) + ' ');
        fprintf(file,"\n");
    }

    fclose(file);
}


void loadMap(struct Game* game, const char* filename)
{
    int i,j;
    FILE *file = fopen(filename,"r");
    if(!file)
    {
        printf("loadMap: cannot open file");
        return;
    }
    strncpy(game->mapFilename, filename, 256);
    game->countingDown = -3;
    game->laps = 2;
    game->cars[0] = newCar(game->carPrototypes[game->selectedCarPrototype]);
    game->cars[1] = newCar(game->carPrototypes[game->selectedCarPrototype]);
    fscanf(file, "%lg %lg %lg %lg %lg %lg %lg %lg %lg\n",
            &game->cars[0].position.x,  &game->cars[0].position.y,  &game->cars[0].position.z,
            &game->cars[0].direction.x, &game->cars[0].direction.y, &game->cars[0].direction.z,
            &game->cars[0].up.x,        &game->cars[0].up.y,        &game->cars[0].up.z);
    fscanf(file, "%lg %lg %lg %lg %lg %lg %lg %lg %lg\n",
            &game->cars[1].position.x,  &game->cars[1].position.y,  &game->cars[1].position.z,
            &game->cars[1].direction.x, &game->cars[1].direction.y, &game->cars[1].direction.z,
            &game->cars[1].up.x,        &game->cars[1].up.y,        &game->cars[1].up.z);

    for(i=0;i<game->propsNum;i++)
        delmodel(game->props[i].appearance);
    if(game->props)
        free(game->props);

    fscanf(file, "%d\n", &game->propsNum);

    game->props = malloc(game->propsNum * sizeof *game->props);
    if(!game->props)
    {
        printf("loadMap: cannot alocate memory");
        delGame(game);
        return;
    }
    for(i=0;i<game->propsNum;i++)
    {
        char filename[256];
        game->props[i]=newProp();
        fscanf(file, "%s\n", filename);
        if(!(game->props[i].appearance = modelLoadFromFile(filename, game->textureManager)))
        {
            game->propsNum = i-1;
            delGame(game);
            return;
        }
        fscanf(file, "%lg %lg %lg %lg %lg %lg %lg %lg %lg\n",
                &game->props[i].position.x,   &game->props[i].position.y,   &game->props[i].position.z,
                &game->props[i].direction.x,  &game->props[i].direction.y,  &game->props[i].direction.z,
                &game->props[i].up.x,         &game->props[i].up.y,         &game->props[i].up.z);
        fscanf(file, "%lg %lg %lg\n",
                &game->props[i].halfSize.x, &game->props[i].halfSize.y, &game->props[i].halfSize.z);
    }


    if(game->checkpoints)
        free(game->checkpoints);

    fscanf(file, "%d\n", &game->laps);
    fscanf(file, "%d\n", &game->checkpointNum);
    game->checkpoints = malloc(game->checkpointNum * sizeof *game->checkpoints);
    if(!game->checkpoints)
    {
        printf("loadMap: cannot alocate memory");
        delGame(game);
        return;
    }
    for(i=0;i<game->checkpointNum;i++)
    {
        fscanf(file, "%lg %lg %lg %lg %lg %lg\n",
                &game->checkpoints[i].position.x,  &game->checkpoints[i].position.y,  &game->checkpoints[i].position.z,
                &game->checkpoints[i].direction.x, &game->checkpoints[i].direction.y, &game->checkpoints[i].direction.z);
    }
    for(i=0;i<game->terrain.height;i++)
    {
        for(j=0;j<game->terrain.width;j++)
            fscanf(file, "%c", &game->terrain.texmap[i][j]);
        fgetc(file); // get newline
#ifdef __linux__
        fgetc(file); // get newline
#endif
    }
    for(i=0;i<game->terrain.height;i++)
    {
        for(j=0;j<game->terrain.width;j++)
        {
            char h;
            fscanf(file, "%c", &h);
            game->terrain.heightmap[i][j] = (double)(h-' ')/4.0;
        }
        fgetc(file); // get newline
#ifdef __linux__
        fgetc(file); // get newline
#endif

    }

    fclose(file);
}

void saveGame(struct Game* game, const char* filename)
{
    FILE *file = fopen(filename,"w");
    if(!file)
    {
        printf("saveGame: cannot open file");
        return;
    }

    fprintf(file, "%d\n", game->carsNum);
    fprintf(file, "%s\n", game->carAppearance->filename);
    fprintf(file, "%d\n", game->selectedCarPrototype);
    fprintf(file, "%s\n", game->mapFilename);

    fprintf(file, "%lg %lg %lg %lg %lg %lg %lg %lg %lg %lg %lg %lg %lg %lg %lg\n",
            game->cars[0].position.x, game->cars[0].position.y, game->cars[0].position.z,
            game->cars[0].direction.x, game->cars[0].direction.y, game->cars[0].direction.z,
            game->cars[0].up.x, game->cars[0].up.y, game->cars[0].up.z,
            game->cars[0].velocity.x, game->cars[0].velocity.y, game->cars[0].velocity.z,
            game->cars[0].angularVelocity.x, game->cars[0].angularVelocity.y, game->cars[0].angularVelocity.z);
    fprintf(file, "%lg %lg %lg %d %d\n",
            game->cars[0].raceTime,
            game->cars[0].currentTime,
            game->cars[0].bestTime,
            game->cars[0].lap,
            game->cars[0].nextCheckpoint);
    fprintf(file, "%lg %lg %lg %lg %lg %lg %lg %lg %lg %lg %lg %lg %lg %lg %lg\n",
            game->cars[1].position.x,   game->cars[1].position.y,   game->cars[1].position.z,
            game->cars[1].direction.x,  game->cars[1].direction.y,  game->cars[1].direction.z,
            game->cars[1].up.x,         game->cars[1].up.y,         game->cars[1].up.z,
            game->cars[1].velocity.x,   game->cars[1].velocity.y,   game->cars[1].velocity.z,
            game->cars[1].angularVelocity.x, game->cars[1].angularVelocity.y, game->cars[1].angularVelocity.z);
    fprintf(file, "%lg %lg %lg %d %d\n",
            game->cars[1].raceTime,
            game->cars[1].currentTime,
            game->cars[1].bestTime,
            game->cars[1].lap,
            game->cars[1].nextCheckpoint);
    fclose(file);
}

void loadGame(struct Game* game, const char* filename)
{
    char str[256];
    int i,j;
    FILE *file = fopen(filename,"r");
    if(!file)
    {
        printf("loadGame: cannot open file");
        return;
    }

    fscanf(file, "%d\n", &i);
    game->carsNum = i;
    fscanf(file, "%s\n", str);
    game->carAppearance = modelLoadFromFile(str, game->textureManager);
    fscanf(file, "%d\n", &game->selectedCarPrototype);
    fscanf(file, "%s\n", str);
    loadMap(game, str);
    game->countingDown = 3;

    fscanf(file, "%lg %lg %lg %lg %lg %lg %lg %lg %lg %lg %lg %lg %lg %lg %lg\n",
            &game->cars[0].position.x, &game->cars[0].position.y, &game->cars[0].position.z,
            &game->cars[0].direction.x, &game->cars[0].direction.y, &game->cars[0].direction.z,
            &game->cars[0].up.x, &game->cars[0].up.y, &game->cars[0].up.z,
            &game->cars[0].velocity.x, &game->cars[0].velocity.y, &game->cars[0].velocity.z,
            &game->cars[0].angularVelocity.x, &game->cars[0].angularVelocity.y, &game->cars[0].angularVelocity.z);
    fscanf(file, "%lg %lg %lg %d %d\n",
            &game->cars[0].raceTime,
            &game->cars[0].currentTime,
            &game->cars[0].bestTime,
            &game->cars[0].lap,
            &game->cars[0].nextCheckpoint);
    fscanf(file, "%lg %lg %lg %lg %lg %lg %lg %lg %lg %lg %lg %lg %lg %lg %lg\n",
            &game->cars[1].position.x,   &game->cars[1].position.y,   &game->cars[1].position.z,
            &game->cars[1].direction.x,  &game->cars[1].direction.y,  &game->cars[1].direction.z,
            &game->cars[1].up.x,         &game->cars[1].up.y,         &game->cars[1].up.z,
            &game->cars[1].velocity.x,   &game->cars[1].velocity.y,   &game->cars[1].velocity.z,
            &game->cars[1].angularVelocity.x, &game->cars[1].angularVelocity.y, &game->cars[1].angularVelocity.z);
    fscanf(file, "%lg %lg %lg %d %d\n",
            &game->cars[1].raceTime,
            &game->cars[1].currentTime,
            &game->cars[1].bestTime,
            &game->cars[1].lap,
            &game->cars[1].nextCheckpoint);
    fclose(file);

    for(i=0;i<4;i++)
    {
        for(j=0;j<2;j++)
        {
                struct Vector offset = vectorAdd( vectorTimes(game->cars[j].direction,
                                                              game->cars[j].wheels[i].offset.z),
                                       vectorAdd( vectorTimes(game->cars[j].up,
                                                              game->cars[j].wheels[i].offset.y),
                                                vectorTimes(vectorCross(game->cars[j].direction, game->cars[j].up),
                                                            game->cars[j].wheels[i].offset.x )));
                                      // offset in global frame of reference
                offset.y=0;
                game->cars[j].wheels[i].ypos = 0.5 + terrainGetHeight(&game->terrain, game->cars[j].position.x + offset.x, game->cars[j].position.z + offset.z);
        }
    }

}
