/* Implementation of the Actor class
 *
 * This is just a prototype Implementation, but the
 * data the actor should be holding would be it's name,
 * currently loaded image, position, and visiblity.
 *
 * It should have a draw method that is called, which would draw the image
 * using this info
 *
 * It should also have a load method that allows loading a characters
 * current emotion
 *
*/

#include "actor.h"
#include <allegro5/bitmap_draw.h>
#include <iostream>
#include <allegro5/bitmap_io.h>

using namespace std;

Actor::Actor(string input_name) {
  name = input_name;
  visible = false;
  image = NULL;
}

string Actor::get_name() {
  return name;
}

string Actor::get_emotion() {
  return emotion;
}

// all images for an actor are expected in 'name/emotion.png'
void Actor::load_emotion(string input_emotion) {
  string path = name + "/" + input_emotion + ".png";
  ALLEGRO_BITMAP* bitmap = al_load_bitmap(path.c_str());
  if (bitmap == NULL) {
    cout << name << " does not have emotion '" << input_emotion << "'" << endl;
    return;
  }
  emotion = input_emotion;
  image = bitmap;
} 

void Actor::show() {
  visible = true;
}

void Actor::hide() {
  visible = false;
}

void Actor::set_position(int px, int py) {
  x = px;
  y = py;
}

void Actor::draw() {
  if (visible) {
    al_draw_bitmap(image, x, y, 0);
  }
}
