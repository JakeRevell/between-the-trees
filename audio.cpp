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
