/* Implementation of the Scene class */

#include <iostream>

#include "scene.h"
#include "game.h"

using namespace std;

Scene::Scene(void* gm_ptr, ALLEGRO_BITMAP* bg, void (*sf)(void*), void (*ce)(void*, int, int), void (*kpe)(void*, int), void (*dee)(void*))
{
    game_ptr = gm_ptr;
    clickEvent = ce;
    keyPressEvent = kpe;
    dialogueEndEvent = dee;
    startingFunc = sf;
    background = bg;
}

void Scene::start()
{
    cout << "Scene " << this << " starting!" << endl;
    if (startingFunc != NULL)
    {
        startingFunc(game_ptr);
        ((Game*)game_ptr)->next_event();
    }
}
bool Scene::click_event(int x, int y)
{
    if (clickEvent != NULL)
    {
        clickEvent(game_ptr, x, y);
        ((Game*)game_ptr)->next_event();
        return true;
    }
    else
        return false;
    
}
bool Scene::key_press_event(int keyCode)
{
    if (keyPressEvent != NULL)
    {
        keyPressEvent(game_ptr, keyCode);
        ((Game*)game_ptr)->next_event();
        return true;
    }
    else
        return false;
}
void Scene::dialogue_end_event()
{
    if (dialogueEndEvent != NULL)
        dialogueEndEvent(game_ptr);
}

void Scene::set_click_event(void (*ce)(void*, int, int))
{
    cout << "Set click event" << endl;
    clickEvent = ce;
}
void Scene::set_key_press_event(void (*kpe)(void*, int))
{
    keyPressEvent = kpe;
}
void Scene::set_dialogue_end_event(void (*dee)(void*))
{
    dialogueEndEvent = dee;
}

Actor* Scene::get_actor(string actor_name) 
{
  auto search = actors.find(actor_name);
  if (search != actors.end())
    return actors[actor_name];
  return NULL;
}

void Scene::create_actor(string name) 
{
  if (!get_actor(name))
    actors[name] = new Actor(name);
}

void Scene::draw()
{
    if (background != NULL)
        al_draw_bitmap(background, 0, 0, 0);
    for (auto pair : actors) {
        pair.second->draw();
    }
}
