/* Implementation of the Game class */

#include <iostream>

#include "game.h"

using namespace std;

Game::Game(void* (*event_proc)(ALLEGRO_THREAD*, void*), void* (*drawing_proc)(ALLEGRO_THREAD*, void*))
{
    window = new Window(480, 360, 960, 720);
    window->set_title("Between the Trees");
    window->clear();
    
    data = new ResourceLoader();
    data->load(0, this);
    
    dialogueBox = new Dialogue(data);
    
    eventThread = al_create_thread(event_proc, this);
    drawingThread = al_create_thread(drawing_proc, this);
    
    scenes = data->get_scenes();
    
    flags = 0;
    shouldStop = false;
    
    al_set_target_bitmap(NULL);
    
    al_start_thread(eventThread);
    al_start_thread(drawingThread);
    
    if (data->get_num_scenes() > 0)
    {
        currentScene = 0;
        scenes[0]->start();
    }
    else
        currentScene = -1;
}
Game::~Game()
{
    al_join_thread(eventThread, NULL);
    al_join_thread(drawingThread, NULL);
    cout << "Threads joined" << endl;
    al_destroy_thread(eventThread);
    al_destroy_thread(drawingThread);
    cout << "Threads destroyed" << endl;
    
    delete data;
    delete window;
    delete dialogueBox;
}

Window* Game::get_window()
{
    return window;
}
ResourceLoader& Game::get_data()
{
    return *data;
}
bool Game::set_scene(int index)
{
    if (index < data->get_num_scenes())
    {
        currentScene = index;
        scenes[index]->start();
        return true;
    }
    return false;
}
Scene* Game::get_scene()
{
    if (currentScene >= 0)
        return scenes[currentScene];
    return NULL;
}
int& Game::get_scene_index()
{
    return currentScene;
}
Dialogue& Game::get_dialogue_box() const
{
    return *dialogueBox;
}

void Game::set_text(string str)
{
    cout << "Dialogue box: " << dialogueBox << endl;
    dialogueBox->set_text(str);
}
void Game::set_text(string str, string name)
{
    dialogueBox->set_text(str, name);
}

void Game::set_bg_music(AudioSample* audio_ptr)
{
  audio_ptr->playbackMode = ALLEGRO_PLAYMODE_LOOP;
  audio_ptr->play();
}

void Game::set_flag(int flag, bool val)
{
    int check = pow(2, flag);
    if (flag < 32)
    {
        if (check & flags == check && !val)
            flags -= check;
        else if (check & flags != check && val)
            flags += check;
    }
}
bool Game::get_flag(int flag) const
{
    int check = pow(2, flag);
    return (check & flags == check);
}

void Game::set_mouse_coords(int x, int y)
{
    mouseX = x;
    mouseY = y;
}
int Game::get_mouse_x() const
{
    return mouseX;
}
int Game::get_mouse_y() const
{
    return mouseY;
}

void Game::stop()
{
    shouldStop = true;
}
bool Game::should_stop()
{
    return shouldStop;
}
