#ifndef GUI_H
#define GUI_H
#include "common.h"
#include "texture.h"

struct MenuItem
{
    char text[256];
    BOOL (*proc)(SDLKey, void*);
    void* arg;
};

struct Menu
{
    struct MenuItem *items;
    char title[256];
    int itemsNum;
    int currentItem;
};

struct Gui
{
    struct TextureManager* textureManager;
    int w;
    int h;
    GLuint image;
    GLuint fontTexture;
    struct Menu* currentMenu;
};

struct Gui* newGui(struct TextureManager* textureManager, int width, int heigth);
void delGui(struct Gui* gui);
void guiPrintf(struct Gui* gui, float x, float y, char * format, ...);
void guiDrawRect(struct Gui* gui, float x, float y, float w, float h, float red, float green, float blue);
void guiDrawImage(struct Gui* gui, float x, float y, float w, float h);
struct Menu* newMenu(const char* title);
void delMenu(struct Menu* menu);
void menuAddMenuItem(struct Menu* menu, struct MenuItem item);
void guiShowMenu(struct Gui* gui);
void guiNextMenuItem(struct Gui* gui);
void guiPrevMenuItem(struct Gui* gui);
BOOL guiClickMenuItem(struct Gui* gui, SDLKey key);
#endif /*GUI_H*/
