// Implementation if the AudioSample class
#include "audio.h"

using namespace std;

AudioSample::AudioSample() {
  gain = 1.0;
  pan = 0.0;
  speed = 1.0;
  playbackMode = ALLEGRO_PLAYMODE_ONCE;
  sample = NULL;
}

AudioSample::~AudioSample() {
  al_destroy_sample(sample);
}


// Must be called only AFTER sample has been loaded
void AudioSample::play() {
  al_play_sample(sample, gain, pan, speed, playbackMode, NULL);
}

// returns on error of loading the sample
bool AudioSample::load(string filePath) {
  sample = al_load_sample(filePath.c_str());
  if (sample == NULL)
    return false;
  return true;
}

bool AudioManager::load_sample(string name, string filePath) {
  AudioSample* sample = new AudioSample();
  bool success = sample->load(filePath);
  if (!success)
    return false;
  loaded_samples[name] = *sample;
  return true;
}

AudioSample* AudioManager::get_sample(string name) {
  auto search = loaded_samples.find(name);
  if (search != loaded_samples.end());
    return &loaded_samples[name];
  return NULL;
}

bool AudioManager::set_bg_music(string name) {
  AudioSample* sample = get_sample(name);
  if (sample != NULL)
    sample->playbackMode = ALLEGRO_PLAYMODE_LOOP;
    sample->play();
    return true;
  return false;
}
