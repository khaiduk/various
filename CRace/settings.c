#include "settings.h"

struct Settings newSettings(void)
{
    struct Settings settings;
    settings.windowWidth = 800;
    settings.windowHeigth = 600;
    settings.windowBits = 32;
    settings.windowFullscreen = FALSE;

    settings.musicVolmue = 100;
    settings.fxVolmue = 100;

    settings.keys[0][KEY_DOWN] = SDLK_DOWN;
    settings.keys[0][KEY_UP] = SDLK_UP;
    settings.keys[0][KEY_LEFT] = SDLK_LEFT;
    settings.keys[0][KEY_RIGHT] = SDLK_RIGHT;

    settings.keys[1][KEY_DOWN] = SDLK_s;
    settings.keys[1][KEY_UP] = SDLK_w;
    settings.keys[1][KEY_LEFT] = SDLK_a;
    settings.keys[1][KEY_RIGHT] = SDLK_d;
    return settings;
}

struct Settings settingsLoad(const char* filename)
{
    struct Settings settings;
    FILE *file = fopen(filename,"r");
    if(!file)
    {
        printf("settingsLoad: cannot open file");
        return newSettings();
    }

    fscanf(file, "%d x %d x %d\n", &settings.windowWidth, &settings.windowHeigth, &settings.windowBits);
    fscanf(file, "%d\n", &settings.windowFullscreen);

    fscanf(file, "%d %d\n", &settings.musicVolmue, &settings.fxVolmue);

    fscanf(file, "%d %d %d %d\n", &settings.keys[0][KEY_DOWN], &settings.keys[0][KEY_UP],
           &settings.keys[0][KEY_LEFT], &settings.keys[0][KEY_RIGHT]);
    fscanf(file, "%d %d %d %d\n", &settings.keys[1][KEY_DOWN], &settings.keys[1][KEY_UP],
           &settings.keys[1][KEY_LEFT], &settings.keys[1][KEY_RIGHT]);
    fclose(file);
    return settings;
}

void settingsSave(struct Settings settings, const char* filename)
{
    FILE *file = fopen(filename,"w");
    if(!file)
    {
        printf("settingsSave: cannot open file");
        return;
    }

    fprintf(file, "%d x %d x %d\n", settings.windowWidth, settings.windowHeigth, settings.windowBits);
    fprintf(file, "%d\n", settings.windowFullscreen);

    fprintf(file, "%d %d\n", settings.musicVolmue, settings.fxVolmue);

    fprintf(file, "%d %d %d %d\n", settings.keys[0][KEY_DOWN], settings.keys[0][KEY_UP],
           settings.keys[0][KEY_LEFT], settings.keys[0][KEY_RIGHT]);
    fprintf(file, "%d %d %d %d\n", settings.keys[1][KEY_DOWN], settings.keys[1][KEY_UP],
           settings.keys[1][KEY_LEFT], settings.keys[1][KEY_RIGHT]);
    fclose(file);
}
