// Implementation if the AudioSample class
#include "audio.h"

using namespace std;

AudioSample::AudioSample() {
  gain = 1.0;
  pan = 0.0;
  speed = 1.0;
  sample = NULL;
}

AudioSample::~AudioSample() {
  al_destroy_sample(sample);
}


// Must be called only AFTER sample has been loaded
void AudioSample::play(bool loop, float g, float p, float s) {
  if (sample != NULL)
    al_play_sample(sample, gain + g, pan + p, speed * s, (loop ? ALLEGRO_PLAYMODE_LOOP : ALLEGRO_PLAYMODE_ONCE), &sample_id);
}

void AudioSample::stop() {
  al_stop_sample(&sample_id);
}

AudioManager::~AudioManager() {
  loaded_samples.clear();
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
