/* Implementations of the scene functions */

#include <iostream>
#include "game.h"
#include "func.h"

using namespace std;

void scene0_0(void* gm_ptr)
{
    cout << "scene0_0" << endl;
    Game& game = *(Game*)gm_ptr;
    
    game.set_text("Dialogue test");
    game.set_text("Dialogue with name test", "Bob");
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
    game.after(5.0, scene0_1);
    game.set_text("Scheduled event test (wait 5 seconds)");
   
    game.get_scene()->set_click_event(advance_on_click);
    game.next_event(); //this should always be added at the end of these functions
}
void scene0_1(void* gm_ptr)
{
    cout << "scene0_1" << endl;
    Game& game = *(Game*)gm_ptr;
    game.get_scene()->set_key_press_event(scene0_keypress);
    
    game.play_audio("bg_music", 1);
    game.set_text("Keyboard event test: please press any key");
    
    game.next_event();
}

void scene0_keypress(void* gm_ptr, int key)
{
    cout << "scene0_keypress" << endl;
    Game& game = *(Game*)gm_ptr;
    game.clear_event_queue();
    game.get_scene()->set_key_press_event(NULL);
    game.get_scene()->set_click_event(scene0_click);
    
    game.set_text("You pressed the " + (string)al_keycode_to_name(key) + " key!\nClick event test: click the screen somewhere");
    
    game.next_event();
}
void scene0_click(void* gm_ptr, int x, int y)
{
    cout << "scene0_click" << endl;
    Game& game = *(Game*)gm_ptr;
    game.clear_event_queue();
    game.get_scene()->set_click_event(advance_on_click);
    
    game.set_text("You clicked at coordinates " + to_string(x) + ", " + to_string(y) + "!");
    game.set_text("Tests complete!");
    game.play_func(scene0_end);
    
    game.next_event();
}

void advance_on_click(void* gm_ptr, int x, int y) {
    Game& game = *(Game*)gm_ptr;
    game.next_event();
}

void scene0_end(void* gm_ptr)
{
    cout << "scene0_end" << endl;
    Game& game = *(Game*)gm_ptr;
    game.stop();
}
