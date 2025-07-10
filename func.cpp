/* Implementations of the scene functions */

#include <iostream>
#include "game.h"
#include "func.h"
#include "scene.h"
#include "actor.h"

using namespace std;

void scene0_start(void* gm_ptr)
{
    cout << "scene0_start" << endl;
    Game& game = *(Game*)gm_ptr;
    
    Scene* current_scene = game.get_scene();
    Actor* test = new Actor("Car");
    test->load_emotion("happy");
    current_scene->add_actor(test);

    game.set_text("Dialogue test");
    game.set_text("Dialogue with name test", "Bob");
    game.set_text("Dialogue options test");
    game.set_text("What kind of functions would you like to test?");
    game.set_option("Audio", scene0_audio);
    game.set_option("Scheduled events", scene0_wait0);
    game.set_option("Mouse click / keyboard events", scene0_event);
    game.set_option("Actors", scene0_actor);
}
void scene0_audio(void* gm_ptr)
{
    cout << "scene0_audio" << endl;
    Game& game = *(Game*)gm_ptr;
    
    game.play_audio("bg_music");
    game.set_text("Audio test");
    game.stop_audio("bg_music");
    game.set_text("Audio stop test");
    game.play_audio("short_clip", 1);
    game.set_text("Looping audio test");
    game.stop_audio("short_clip");
    game.play_audio("bg_music", 0, -0.95, -1.0, 2.0);
    game.set_text("Audio gain, pan, and speed test");
    game.stop_audio("bg_music");
    game.set_text("Goodbye!");
    game.play_func(scene0_end);
}
void scene0_wait0(void* gm_ptr)
{
    cout << "scene0_wait" << endl;
    Game& game = *(Game*)gm_ptr;
    
    game.after(5.0, scene0_wait1);
    game.set_text("Scheduled event test (wait 5 seconds)");
}
void scene0_wait1(void* gm_ptr)
{
    cout << "scene0_wait1" << endl;
    Game& game = *(Game*)gm_ptr;
    
    game.set_text("Test complete!\nGoodbye!");
    game.play_func(scene0_end);
}
void scene0_event(void* gm_ptr)
{
    cout << "scene0_event" << endl;
    Game& game = *(Game*)gm_ptr;
    game.get_scene()->set_key_press_event(scene0_keypress);
    
    game.play_audio("bg_music", 1);
    game.set_text("Keyboard event test: please press any key");
}
void scene0_keypress(void* gm_ptr, int key)
{
    cout << "scene0_keypress" << endl;
    Game& game = *(Game*)gm_ptr;
    game.clear_event_queue();
    game.get_scene()->set_key_press_event(NULL);
    game.get_scene()->set_click_event(scene0_click);
    
    game.set_text("You pressed the " + (string)al_keycode_to_name(key) + " key!\nClick event test: click the screen somewhere");
}
void scene0_click(void* gm_ptr, int x, int y)
{
    cout << "scene0_click" << endl;
    Game& game = *(Game*)gm_ptr;
    game.clear_event_queue();
    game.get_scene()->set_click_event(NULL);
    
    game.set_text("You clicked at coordinates " + to_string(x) + ", " + to_string(y) + "!");
    game.set_text("Tests complete!\nGoodbye!");
    game.play_func(scene0_end);
}

void scene0_actor(void* gm_ptr)
{
  cout << "scene0_actor" << endl;
  Game& game = *(Game*)gm_ptr;
  Actor* car = game.get_scene()->get_actor("Car");
  if (car == NULL) {
    cout << "car is null" << endl;
  }
  car->load_emotion("never");
  car->set_position(100, 100);
  car->show();
  cout << car->get_emotion() << endl;
  game.set_text("I am a car", car->get_name());
  game.play_func(scene0_end);
}


void scene0_end(void* gm_ptr)
{
    cout << "scene0_end" << endl;
    Game& game = *(Game*)gm_ptr;
    game.stop();
}
