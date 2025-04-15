/* Declarations for the Scene class */

#ifndef SCENE_H_INCLUDED
#define SCENE_H_INCLUDED

#include <allegro5/allegro.h>

class Scene
{
    public:
        Scene(void*, ALLEGRO_BITMAP*, void (*)(void*), void (*)(void*, int, int), void (*)(void*, int), void (*)(void*));
        void start();
        void click_event(int, int);
        void key_press_event(int);
        void dialogue_end_event();
        void set_click_event(void (*)(void*, int, int));
        void set_key_press_event(void (*)(void*, int));
        void set_dialogue_end_event(void (*)(void*));
        void draw();
    private:
        void* game_ptr;
        void (*startingFunc)(void*);
        void (*clickEvent)(void*, int, int);
        void (*keyPressEvent)(void*, int);
        void (*dialogueEndEvent)(void*);
        ALLEGRO_BITMAP* background;
};

#endif