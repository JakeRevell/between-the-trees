/* Declarations for the ResourceLoader class
 *
 * After initialization, the load(int) function can be invoked
 * to load data (mainly images) based on the given value.
 *
 * I'm not sure how large this project will turn out to be, so
 * while we could theoretically load everything at the start of
 * the program, if this turns out to have significant performance
 * impacts we could also have designated loading sections between
 * certain scenes.
*/

#ifndef RESOURCE_H_INCLUDED
#define RESOURCE_H_INCLUDED

#include <allegro5/allegro_font.h>
#include "scene.h"
#include "audio.h"

class ResourceLoader
{
    public:
        ResourceLoader(AudioManager*);
        ~ResourceLoader();
        void load(int, void*);
        ALLEGRO_FONT* get_font() const;
        ALLEGRO_BITMAP* get_text_container() const;
        ALLEGRO_BITMAP* get_name_container() const;
        ALLEGRO_BITMAP* get_background(int) const;
        Scene** get_scenes() const;
        int get_num_scenes() const;
    
    private:
        ALLEGRO_FONT* font;
        ALLEGRO_BITMAP* textContainer;
        ALLEGRO_BITMAP* nameContainer;
        ALLEGRO_BITMAP** backgrounds;
        int numBackgrounds;
        Scene** loadedScenes;
        int numScenes;
        AudioManager* audioManager;
};

#endif
