/*
 * Definition of AudioSample class
*/

#ifndef AUDIO_H_INCLUDED
#define AUDIO_H_INCLUDED

#include <string>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

using namespace std;

class AudioSample {
  public:
    AudioSample();
    ~AudioSample();
    void play();
    bool load(string);
    float gain;
    float pan;
    float speed;
    ALLEGRO_PLAYMODE playbackMode;
  private:
    ALLEGRO_SAMPLE* sample;
};

#endif
