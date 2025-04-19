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
        
        void draw(int) const;
        
        int& get_state();
        void set_text(string);
        void set_text(string, string);
        vector<string>& get_text();
        bool next_line(); //returns 0 on fail
        string get_current_line() const;
        bool next_char();
        char get_current_char() const;
        string get_name() const;
        bool& show_name();
        
        clock_t dialogueStartTime;
    
    private:
        string insert_newlines(string);
        int state; //0 - hidden; 1 - currently drawing text, char by char; 2 - text fully drawn, ready for next line
        vector<string> text;
        int currentLine;
        int currentChar;
        string name;
        bool showName;
        ALLEGRO_FONT* font;
        ALLEGRO_BITMAP* textContainer;
        ALLEGRO_BITMAP* nameContainer;
};

#endif
