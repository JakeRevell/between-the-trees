/* Implementation of the Game class */

#include <iostream>

#include "game.h"

using namespace std;

Game::Game(void* (*event_proc)(ALLEGRO_THREAD*, void*), void* (*drawing_proc)(ALLEGRO_THREAD*, void*))
{
    window = new Window(480, 360, 960, 720);
    window->set_title("Between the Trees");
    window->clear();
    
    audioManager = new AudioManager();

    data = new ResourceLoader(audioManager);
    data->load(0, this);
    
    dialogueBox = new Dialogue(data);
    
    waitUntil = 0;
    scheduledFunc = NULL;
    
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
    delete audioManager;
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
AudioManager& Game::get_audio_manager() const
{
    return *audioManager;
}

void Game::clear_event_queue()
{
    queue<Event> empty;
    eventQueue.swap(empty);
}

void Game::set_text(string str, string name)
{
    eventQueue.emplace(DIALOGUE_TEXT_EVENT, new DialogueEvent{str, name});
}
void Game::set_option(string text, void (*func)(void*))
{
    eventQueue.emplace(DIALOGUE_OPTION_EVENT, new DialogueOptionEvent{text, func});
}
void Game::play_audio(string name, bool loop, float gain, float pan, float speed)
{
    eventQueue.emplace(AUDIO_START_EVENT, new AudioEvent{name, loop, gain, pan, speed});
}
void Game::stop_audio(string name)
{
    eventQueue.emplace(AUDIO_STOP_EVENT, new AudioEvent{name, 0});
}
void Game::play_func(void (*func)(void*))
{
    eventQueue.emplace(FUNC_EVENT, new FuncEvent{func});
}
void Game::after(float secs, void (*func)(void*))
{
    eventQueue.emplace(WAIT_EVENT, new WaitEvent{secs, func});
}
void Game::next_event()
{
    if (!(eventQueue.empty()))
    {
        Event& event = eventQueue.front();
        event.play(this);
        EventType type = event.get_event_type();
        eventQueue.pop();
        if (!(eventQueue.empty()))
        {
            if (type != DIALOGUE_TEXT_EVENT && type != DIALOGUE_OPTION_EVENT && dialogueBox->get_state() != 0)
            {
                dialogueBox->get_state() = 4;
                next_event();
            }
            else if (eventQueue.front().get_event_type() == DIALOGUE_OPTION_EVENT)
                next_event();
        }
    }
    else
    {
        if (dialogueBox->get_state() == 2 && !(dialogueBox->is_on_option_chooser()))
            dialogueBox->get_state() = 4;
    }
}

void Game::set_scheduled_func(clock_t tm, void (*func)(void*))
{
    waitUntil = tm;
    scheduledFunc = func;
}
time_t Game::get_scheduled_time()
{
    return waitUntil;
}
void Game::play_scheduled_func()
{
    waitUntil = 0;
    scheduledFunc(this);
    next_event();
}
void Game::play_selected_option()
{
    dialogueBox->play_current_option(this);
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
