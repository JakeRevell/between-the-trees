/* Declarations for the Game class */

#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <allegro5/allegro.h>
#include <cmath>
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
        void set_text(string);
        void set_text(string, string);
        void set_bg_music(AudioSample*);
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
        Dialogue* dialogueBox;
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
