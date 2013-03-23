#include "sound.h"


struct SoundManager newSoundManager(struct Settings* settings)
{
    int i;
    struct SoundManager sm;
    sm.settings = settings;
    alutInit(NULL, 0);
    if(alGetError() != AL_NO_ERROR)
    {
        printf("newSoundManager: cannot initalize ALUT");
        return sm;
    }

    alGenBuffers(SOUND_COUNT, sm.buffers);
    alGenSources(SOUND_SOURCE_COUNT, sm.sources);

    char filenames[SOUND_COUNT][256] =
    {
        "music.wav",
        "click.wav",
        "crash.wav",
        "engine.wav"
    };

    ALfloat zeroVector[3]  = {0.0, 0.0, 0.0};
    ALfloat zeroVector6[6] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

    for(i=0;i<SOUND_COUNT;i++)
    {
        ALenum format;
        ALsizei size;
        ALvoid* data;
        ALsizei freq;
        ALboolean loop;

        alutLoadWAVFile(filenames[i], &format, &data, &size, &freq, &loop);
        alBufferData(sm.buffers[i], format, data, size, freq);
        alutUnloadWAV(format, data, size, freq);
    }

    for(i=0;i<SOUND_SOURCE_COUNT;i++)
    {
        if(SOUND_SOURCE_ENGINE1 == i || SOUND_SOURCE_ENGINE2 == i)
            alSourcei (sm.sources[i], AL_BUFFER,   sm.buffers[SOUND_ENGINE]);
        else
            alSourcei (sm.sources[i], AL_BUFFER,   sm.buffers[i]);
        alSourcef (sm.sources[i], AL_PITCH,    1.0);
        if(SOUND_SOURCE_MUSIC == i)
            alSourcef (sm.sources[i], AL_GAIN, settings->musicVolmue / 100.0);
        else
            alSourcef (sm.sources[i], AL_GAIN, settings->fxVolmue / 100.0);
        alSourcefv(sm.sources[i], AL_POSITION, zeroVector);
        alSourcefv(sm.sources[i], AL_VELOCITY, zeroVector);
        if(SOUND_SOURCE_CLICK == i || SOUND_SOURCE_CRASH == i)
            alSourcei (sm.sources[i], AL_LOOPING,  AL_FALSE);
        else
            alSourcei (sm.sources[i], AL_LOOPING,  AL_TRUE);
    }

    alListenerfv(AL_POSITION,    zeroVector);
    alListenerfv(AL_VELOCITY,    zeroVector);
    alListenerfv(AL_ORIENTATION, zeroVector6);

    return sm;
}

void delSoundManager(struct SoundManager *sm)
{
    alDeleteSources(SOUND_COUNT, sm->buffers);
    alDeleteSources(SOUND_SOURCE_COUNT, sm->sources);
}

void soundManagerUpdateVolmue(struct SoundManager *sm)
{
    int i;
    for(i=0;i<SOUND_SOURCE_COUNT;i++)
    {
        if(SOUND_SOURCE_MUSIC == i)
            alSourcef (sm->sources[i], AL_GAIN, sm->settings->musicVolmue / 100.0);
        else
            alSourcef (sm->sources[i], AL_GAIN, sm->settings->fxVolmue / 100.0);
    }
}

void soundManagerPlayMusic(struct SoundManager *sm)
{
    ALint sourceState;
    alGetSourcei(sm->sources[SOUND_SOURCE_MUSIC], AL_SOURCE_STATE, &sourceState);
    if(AL_PLAYING != sourceState)
        alSourcePlay(sm->sources[SOUND_SOURCE_MUSIC]);
}

void soundManagerStopMusic(struct SoundManager *sm)
{
    alSourceStop(sm->sources[SOUND_SOURCE_MUSIC]);
}

void soundManagerClick(struct SoundManager *sm)
{
    alSourcePlay(sm->sources[SOUND_SOURCE_CLICK]);
}

void soundManagerCrash(struct SoundManager *sm)
{
    ALint sourceState;
    alGetSourcei(sm->sources[SOUND_SOURCE_CRASH], AL_SOURCE_STATE, &sourceState);
    if(AL_PLAYING != sourceState)
        alSourcePlay(sm->sources[SOUND_SOURCE_CRASH]);
}

void soundManagerEngine(struct SoundManager *sm, int engine, double velocity)
{
    ALint sourceState;
    alGetSourcei(sm->sources[SOUND_SOURCE_ENGINE1 + engine], AL_SOURCE_STATE, &sourceState);
    if(velocity <= EPSILON)
    {
        alSourceStop(sm->sources[SOUND_SOURCE_ENGINE1 + engine]);
    }
    else
    {
        if(AL_PLAYING != sourceState)
        {
            alSourcePlay(sm->sources[SOUND_SOURCE_ENGINE1 + engine]);
        }
        alSourcef (sm->sources[SOUND_SOURCE_ENGINE1 + engine], AL_PITCH, 1+velocity);
        if(velocity < 0.1)
            alSourcef (sm->sources[SOUND_SOURCE_ENGINE1 + engine], AL_GAIN, sm->settings->fxVolmue/100*velocity*10.0);
        else
            alSourcef (sm->sources[SOUND_SOURCE_ENGINE1 + engine], AL_GAIN, sm->settings->fxVolmue/100.0);
    }
}

