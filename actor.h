/* Defintions of the Actor class
 * 
*/

#ifndef ACTOR_H_INCLUDED
#define ACTOR_H_INCLUDED

#include <string>
#include <allegro5/allegro5.h>

using namespace std;

class Actor {
public:
  Actor(string);
  ~Actor();
  string get_name();
  string get_emotion();
  void load_emotion(string);
  void set_position(int, int);
  void show();
  void hide();
  void draw();
private:
  string name;
  string emotion;
  bool visible;
  int x;
  int y;
  ALLEGRO_BITMAP* image;
};

#endif
