/*
 * Definition of AudioSample class
 *
 * This is just a basic wrapper for an allegro sample
 * 
 * currently added a basic loading function, but possibly could be
 * added as a resource to be loaded by the resource loader?
 *
 * Also, we might need some sort of orchestrator for the audio samples,
 * could be implemented in the game class or somewhere else if necessary?
 *
*/

#ifndef AUDIO_H_INCLUDED
#define AUDIO_H_INCLUDED

#include <string>
#include <unordered_map>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

using namespace std;

class AudioSample {
  public:
    AudioSample();
    ~AudioSample();
    void play(bool, float, float, float);
    void stop();
    bool load(string);
    float gain;
    float pan;
    float speed;
  private:
    ALLEGRO_SAMPLE* sample;
    ALLEGRO_SAMPLE_ID sample_id;
};

class AudioManager {
  public:
    ~AudioManager();
    bool load_sample(string, string);
    AudioSample* get_sample(string);
  private:
    unordered_map<string, AudioSample> loaded_samples;
};

#endif
