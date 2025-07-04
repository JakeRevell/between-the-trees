/* Declarations for the Dialogue class */

#ifndef DIALOGUE_H_INCLUDED
#define DIALOGUE_H_INCLUDED

#include <string>
#include <vector>
#include <ctime>
#include <allegro5/allegro_font.h>

#include "resource.h"

using namespace std;

class Dialogue
{
    public:
        Dialogue(ResourceLoader*);
        
        void draw();
        
        int& get_state();
        void set_text(string);
        void set_text(string, string);
        const string get_text();
        bool next_char();
        char get_current_char() const;
        string get_name() const;
        
        clock_t dialogueStartTime;
    
    private:
        float transition;
        string insert_newlines(string);
        int state; //0 - hidden; 1 - currently drawing text, char by char; 2 - text fully drawn, ready for next line; 3 - sliding in; 4 - sliding out
        string text;
        string name;
        int currentChar;
        ALLEGRO_FONT* font;
        ALLEGRO_BITMAP* textContainer;
        ALLEGRO_BITMAP* nameContainer;
};

#endif
