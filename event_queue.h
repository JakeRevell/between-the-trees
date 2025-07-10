/* Declarations for the Event class, which should be used in a queue in the Game object */

#ifndef EVENT_QUEUE_H_INCLUDED
#define EVENT_QUEUE_H_INCLUDED

#include <string>

using namespace std;

typedef void* (*OptionFunc)(int);

enum EventType
{
    DIALOGUE_TEXT_EVENT,
    DIALOGUE_OPTION_EVENT,
    AUDIO_START_EVENT,
    AUDIO_STOP_EVENT,
    FUNC_EVENT,
    WAIT_EVENT //for playing a function after a specified amount of time (does not pause or stop the current function, however)
};

struct DialogueEvent
{
    string text;
    string name;
};

struct DialogueOptionEvent
{
    string text;
    void (*func)(void*);
};

struct AudioEvent
{
    string sample;
    bool loop;
    float gain;
    float pan;
    float speed;
};

struct FuncEvent
{
    void (*func)(void*);
};

struct WaitEvent
{
    float secs;
    void (*func)(void*);
};

class Event
{
    public:
        Event(EventType, void*);
        ~Event();
        void play(void*);
        EventType get_event_type();
    private:
        EventType type;
        void* event;
};

#endif
