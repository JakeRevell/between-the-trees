/* Declarations for the Dialogue class */

#ifndef DIALOGUE_H_INCLUDED
#define DIALOGUE_H_INCLUDED

#include <string>
#include <vector>
#include <ctime>
#include <allegro5/allegro_font.h>

#include "resource.h"

using namespace std;

struct Option
{
    string txt;
    void (*func)(void*);
    int y;
};

class Dialogue
{
    public:
        Dialogue(ResourceLoader*);
        
        void draw();
        
        int& get_state();
        void set_text(string);
        void set_text(string, string);
        void set_option(string, void (*)(void*));
        const int get_num_options();
        int& current_option();
        bool set_current_option_by_y(int);
        void play_current_option(void*);
        const bool is_on_option_chooser();
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
        vector<Option> options;
        int currentChar;
        int currentOp;
        bool onOptionChooser;
        ALLEGRO_FONT* font;
        ALLEGRO_BITMAP* textContainer;
        ALLEGRO_BITMAP* nameContainer;
};

#endif
