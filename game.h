/* Declarations for the Game class */

#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <allegro5/allegro.h>
#include <cmath>
#include <ctime>
#include <queue>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "window.h"
#include "resource.h"
#include "scene.h"
#include "dialogue.h"
#include "audio.h"
#include "event_queue.h"

class Game {
    public:
        Game(void* (*)(ALLEGRO_THREAD*, void*), void* (*)(ALLEGRO_THREAD*, void*));
        ~Game();
        Window* get_window();
        ResourceLoader& get_data();
        bool set_scene(int);
        Scene* get_scene();
        int& get_scene_index();
        Dialogue& get_dialogue_box() const;
        AudioManager& get_audio_manager() const;
        void clear_event_queue();
        void set_text(string, string="");
        void set_option(string, void (*)(void*));
        void play_audio(string, bool=false, float=0.0, float=0.0, float=1.0);
        void stop_audio(string);
        void play_func(void (*)(void*));
        void after(float, void (*)(void*)); //used to add a scheduled event
        void next_event();
        void set_scheduled_func(clock_t, void (*)(void*)); //
        time_t get_scheduled_time();                       //
        void play_scheduled_func();                        //
        void play_selected_option();                       //used internally by the event queue system (don't call these in func.cpp)
        void set_flag(int, bool);
        bool get_flag(int) const;
        void set_mouse_coords(int, int);
        int get_mouse_x() const;
        int get_mouse_y() const;
        void stop();
        bool should_stop();
    private:
        Window* window;
        ResourceLoader* data;
        AudioManager* audioManager;
        Dialogue* dialogueBox;
        queue<Event> eventQueue;
        clock_t waitUntil;
        void (*scheduledFunc)(void*);
        Scene** scenes;
        ALLEGRO_THREAD* eventThread;
        ALLEGRO_THREAD* drawingThread;
        int currentScene;
        int flags;
        int mouseX;
        int mouseY;
        bool shouldStop;
};

#endif
