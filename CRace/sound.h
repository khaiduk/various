#ifndef SOUND_H
#define SOUND_H
#include "common.h"
#include "settings.h"

#define SOUND_MUSIC 0
#define SOUND_CLICK 1
#define SOUND_CRASH 2
#define SOUND_ENGINE 3
#define SOUND_COUNT 4

#define SOUND_SOURCE_MUSIC 0
#define SOUND_SOURCE_CLICK 1
#define SOUND_SOURCE_CRASH 2
#define SOUND_SOURCE_ENGINE1 3
#define SOUND_SOURCE_ENGINE2 4
#define SOUND_SOURCE_COUNT 5

struct SoundManager
{
    struct Settings *settings;
    ALuint buffers[SOUND_COUNT];
    ALuint sources[SOUND_SOURCE_COUNT];
};

struct SoundManager newSoundManager(struct Settings* settings);
void delSoundManager(struct SoundManager *sm);
void soundManagerUpdateVolmue(struct SoundManager *sm);
void soundManagerPlayMusic(struct SoundManager *sm);
void soundManagerStopMusic(struct SoundManager *sm);
void soundManagerClick(struct SoundManager *sm);
void soundManagerCrash(struct SoundManager *sm);
void soundManagerEngine(struct SoundManager *sm, int engine, double velocity);

#endif /*SOUND_H*/


