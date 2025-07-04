/* Implemantion of the Event class */

#include <iostream>
#include <ctime>

#include "event_queue.h"
#include "audio.h"
#include "game.h"

using namespace std;

Event::Event(EventType eventType, void* ptrToEvent)
{
    type = eventType;
    event = ptrToEvent;
}
Event::~Event()
{
    switch (type)
    {
        case DIALOGUE_TEXT_EVENT:
            delete (DialogueEvent*)event;
            break;
        case DIALOGUE_OPTION_EVENT:
            delete (DialogueOptionEvent*)event;
            break;
        case AUDIO_START_EVENT:
            delete (AudioEvent*)event;
            break;
        case AUDIO_STOP_EVENT:
            delete (AudioEvent*)event;
            break;
        case WAIT_EVENT:
            delete (WaitEvent*)event;
            break;
    }
}
void Event::play(void* gamePtr)
{
    Game* game = (Game*)gamePtr;
    switch (type)
    {
        case DIALOGUE_TEXT_EVENT:
        {
            DialogueEvent* d_event = (DialogueEvent*)event;
            Dialogue& db = game->get_dialogue_box();
            db.set_text(d_event->text, d_event->name);
            break;
        }
        case DIALOGUE_OPTION_EVENT:
            //not yet implemented
            break;
        case AUDIO_START_EVENT:
        {
            AudioEvent* a_event = (AudioEvent*)event;
            AudioManager& audioManager = game->get_audio_manager();
            AudioSample* sample = audioManager.get_sample(a_event->sample);
            sample->play(a_event->loop, a_event->gain, a_event->pan, a_event->speed);
            break;
        }
        case AUDIO_STOP_EVENT:
        {
            AudioEvent* a_event = (AudioEvent*)event;
            AudioManager& audioManager = game->get_audio_manager();
            AudioSample* sample = audioManager.get_sample(a_event->sample);
            sample->stop();
            break;
        }
        case FUNC_EVENT:
        {
            FuncEvent* f_event = (FuncEvent*)event;
            f_event->func(game);
        }
        case WAIT_EVENT:
        {
            WaitEvent* w_event = (WaitEvent*)event;
            game->set_scheduled_func(clock() + (w_event->secs * CLOCKS_PER_SEC), w_event->func);
            break;
        }
    }
}
EventType Event::get_event_type()
{
    return type;
}
