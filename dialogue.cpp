/* Implementation of the Scene class */

#include <iostream>
#include <cmath>
#include "dialogue.h"

using namespace std;

int smooth_transition(int l_bound, int r_bound, float val)
{
    //return (2 - (cos(val * M_PI) + 1)) * (r_bound - l_bound) / 2 + l_bound;
    return sqrt(1.0 - pow(val - 1, 2)) * (r_bound - l_bound) + l_bound;
}

Dialogue::Dialogue(ResourceLoader* data)
{
    transition = 0.0;
    state = 0;
    currentChar = 0;
    name = "";
    
    font = data->get_font();
    textContainer = data->get_text_container();
    nameContainer = data->get_name_container();
    
    dialogueStartTime = clock();
}

void Dialogue::draw()
{
    int y = 372 - smooth_transition(0, 72, transition);
    if (text.size() > 0 && state > 0)
    {
        if (textContainer != NULL)
        {
            al_draw_bitmap(textContainer, 0, y, 0);
        }
        
        if (name != "")
        {
            if (nameContainer != NULL)
            {
                //cout << ((int)(name.size()) - 40) * 8 << endl;
                al_draw_bitmap(nameContainer, ((int)(name.size()) - 39) * 8, y - 12, 0);
            }
            al_draw_text(font, al_map_rgb(255, 255, 255), 2, y - 9, 0, name.c_str());
        }
        
        if (state == 1 || state == 2)
        {
            y = 300;
            int write_y = y + 3;
            int start = 0;
            int end = text.find('\n');
            if (end == -1)
                end = text.length();
            
            while (start < text.length())
            {
                if (state == 1 && currentChar < end)
                {
                    al_draw_text(font, al_map_rgb(255, 255, 255), 2, write_y, 0, text.substr(start, currentChar - start + 1).c_str());
                    break;
                }
                else
                {
                    al_draw_text(font, al_map_rgb(255, 255, 255), 2, write_y, 0, text.substr(start, end - start).c_str());
                    start = end + 1;
                    end = text.find('\n', start);
                    if (end == -1)
                        end = text.length();
                    write_y += 12;
                }
            }
        }
        else if (state == 3)
        {
            if (transition < 1)
                transition += 0.1;
            else
                state = 1;
        }
        else if (state == 4)
        {
            if (transition > 0.0)
                transition -= 0.1;
            else
            {
                state = 0;
            }
        }
    }
}

int& Dialogue::get_state()
{
    return state;
}
void Dialogue::set_text(string str)
{
    cout << "test" << endl;
    text = insert_newlines(str);
    if (state == 0 || state == 2)
    {
        state = 3;
    }
}
void Dialogue::set_text(string str, string nm)
{
    text = insert_newlines(str);
    if (state == 0)
    {
        state = 3;
    }
    else if (state == 2 || state == 4)
    {
        state = 1;
    }
    name = nm;
}

string Dialogue::insert_newlines(string str) 
{
  vector<int> positions = {-1};
  int end_sub = 0;
  int i = 0;
  while (end_sub != -1) {
    end_sub = str.find("\n", positions.back() + 1);
    if (end_sub == -1)
      positions.push_back(str.length());
    else {
      positions.push_back(end_sub);
      i++;
    }
  }

  i = 0;
  while (i < (positions.size() - 1))
  {
    int start = positions[i] + 1;
    int end = positions[i + 1];
    int index;
    if ((end - start) > 60)
    {
      index = str.substr(start, start + 60).rfind(" ");
      index += start;
      str.insert(index + 1, "\n");
      positions[i] = index + 2;
      for (int j = i + 1; j < positions.size(); j++) {
        positions[j]++;
      }
    }
    else
    {
      i++;
    }
  }
  return str;
}

const string Dialogue::get_text()
{
    return text;
}
bool Dialogue::next_char()
{
    currentChar++;
    if (currentChar >= text.size())
    {
        state = 2;
        currentChar = 0;
        return false;
    }
    return true;
}
char Dialogue::get_current_char() const
{
    return text[currentChar];
}
string Dialogue::get_name() const
{
    return name;
}
