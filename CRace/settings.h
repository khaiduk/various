#ifndef SETTINGS_H
#define SETTINGS_H
#include "common.h"

#define KEY_UP 0
#define KEY_DOWN 1
#define KEY_LEFT 2
#define KEY_RIGHT 3

struct Settings
{
    int windowWidth;
    int windowHeigth;
    int windowBits;
    int musicVolmue;
    int fxVolmue;
    BOOL windowFullscreen;
    int keys[2][4];
};

struct Settings newSettings(void);
struct Settings settingsLoad(const char* filename);
void settingsSave(struct Settings settings, const char* filename);

#endif /*SETTINGS_H*/


