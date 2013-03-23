#include "gui.h"

struct Gui* newGui(struct TextureManager* textureManager, int width, int heigth)
{
    struct Gui* gui = malloc(sizeof *gui);
    if(!gui)
    {
        printf("newGui: cannot alocate memory");
        return NULL;
    }
    gui->textureManager = textureManager;
    gui->image = 0;
    gui->fontTexture = getTexture(textureManager, "font.bmp", FALSE);
    gui->w = width;
    gui->h = heigth;
    gui->currentMenu = NULL;
    return gui;
}

void delGui(struct Gui* gui)
{
    free(gui);
}

void guiPrintf(struct Gui* gui, float x, float y, char * format, ...)
{
    char buffer[256];
    unsigned int i;

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, gui->w, 0, gui->h);
    glScalef(1, -1, 1);
    glTranslatef(0, -gui->h, 0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);

    glEnable(GL_TEXTURE_2D);
    glColor3f(1.0,1.0,1.0);

    va_list args;
    va_start (args, format);
    vsprintf (buffer,format, args);
    va_end (args);

    for(i=0;i<strlen(buffer);i++)
    {
        float coordx, coordy, width;
        coordx = (float)(buffer[i]%16)/16.0;
        coordy = (float)(buffer[i]/16)/16.0;
        width = 20;

        glBlendFunc(GL_DST_COLOR,GL_ZERO);
        glBindTexture(GL_TEXTURE_2D, gui->fontTexture);
        glBegin(GL_QUADS);
            glTexCoord2f(coordx,coordy);
            glVertex2f((x + i*width), y);
            glTexCoord2f(coordx,coordy + 1/16.0);
            glVertex2f((x + i*width), y + width);
            glTexCoord2f(coordx + 1/16.0, coordy + 1/16.0);
            glVertex2f((x + i*width + width), y + width);
            glTexCoord2f(coordx + 1/16.0, coordy);
            glVertex2f((x + i*width + width), y);
        glEnd();
    }

    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

void guiDrawRect(struct Gui* gui, float x, float y, float w, float h, float red, float green, float blue)
{
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, gui->w, 0, gui->h);
    glScalef(1, -1, 1);
    glTranslatef(0, -gui->h, 0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);
    glColor3f(red, green, blue);

    glBegin(GL_QUADS);
        glVertex2f(x,y);
        glVertex2f(x,y + h);
        glVertex2f(x + w,y + h);
        glVertex2f(x + w,y);
    glEnd();

    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

void guiDrawImage(struct Gui* gui, float x, float y, float w, float h)
{
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, gui->w, 0, gui->h);
    glScalef(1, -1, 1);
    glTranslatef(0, -gui->h, 0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glBindTexture(GL_TEXTURE_2D, gui->image);

    glBegin(GL_QUADS);
        glTexCoord2f(0, 0);
        glVertex2f(x,y);
        glTexCoord2f(0, 1);
        glVertex2f(x,y + h);
        glTexCoord2f(1, 1);
        glVertex2f(x + w,y + h);
        glTexCoord2f(1, 0);
        glVertex2f(x + w,y);
    glEnd();

    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

struct Menu* newMenu(const char* title)
{
    struct Menu* menu = malloc(sizeof *menu);
    if(!menu)
    {
        printf("newMenu: cannot alocate memory");
        return NULL;
    }
    strncpy(menu->title, title, 256);
    menu->items = NULL;
    menu->itemsNum = 0;
    menu->currentItem = 0;
    return menu;
}

void delMenu(struct Menu* menu)
{
    free(menu->items);
}

void menuAddMenuItem(struct Menu* menu, struct MenuItem item)
{
    if(!menu)
        return;
    menu->itemsNum++;
    menu->items = realloc(menu->items, menu->itemsNum * sizeof *menu->items);
    menu->items[menu->itemsNum - 1] = item;
}

void guiShowMenu(struct Gui* gui)
{
    int i;
    if(!gui->currentMenu)
        return;
    guiDrawRect(gui, 10, 10, 400, 20+25*gui->currentMenu->itemsNum, 0.8, 0.8, 1);
    guiPrintf(gui, 10, 10, " %s", gui->currentMenu->title);
    for(i=0;i<gui->currentMenu->itemsNum;i++)
    {
        if(i == abs(gui->currentMenu->currentItem))
            guiPrintf(gui, 10, 30+i*25, ">> %s", gui->currentMenu->items[i].text);
        else
            guiPrintf(gui, 10, 30+i*25, "   %s", gui->currentMenu->items[i].text);
    }
}

void guiNextMenuItem(struct Gui* gui)
{
    if(!gui->currentMenu)
        return;
    gui->currentMenu->currentItem++;
    while(gui->currentMenu->currentItem >= gui->currentMenu->itemsNum)
        gui->currentMenu->currentItem -=gui->currentMenu->itemsNum;
}

void guiPrevMenuItem(struct Gui* gui)
{
    if(!gui->currentMenu)
        return;
    gui->currentMenu->currentItem--;
    while(gui->currentMenu->currentItem < 0)
        gui->currentMenu->currentItem +=gui->currentMenu->itemsNum;
}

BOOL guiClickMenuItem(struct Gui* gui, SDLKey key)
{
    if(!gui->currentMenu)
        return TRUE;
    if(!(gui->currentMenu->items[abs(gui->currentMenu->currentItem)].proc))
        return TRUE;
    return (gui->currentMenu->items[abs(gui->currentMenu->currentItem)].proc)(key, gui->currentMenu->items[abs(gui->currentMenu->currentItem)].arg);

}

