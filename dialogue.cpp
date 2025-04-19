/* Implementation of the Scene class */

#include <iostream>
#include "dialogue.h"

using namespace std;

Dialogue::Dialogue(ResourceLoader* data)
{
    state = 0;
    currentLine = 0;
    currentChar = 0;
    name = "";
    showName = false;
    
    font = data->get_font();
    textContainer = data->get_text_container();
    nameContainer = data->get_name_container();
    
    dialogueStartTime = clock();
}

void Dialogue::draw(int y) const
{
    if (text.size() > 0 && state > 0)
    {
        if (textContainer != NULL)
        {
            al_draw_bitmap(textContainer, 0, y, 0);
        }
        
        if (showName)
        {
            if (nameContainer != NULL)
                al_draw_bitmap(nameContainer, 0, y - 10, 0);
            al_draw_text(font, al_map_rgb(255, 255, 255), 2, y - 8, 0, name.c_str());
        }
        
        string str = text[currentLine];
        int write_y = y + 2;
        int start = 0;
        int end = str.find('\n');
        if (end == -1)
            end = str.length();
        
        while (start < str.length())
        {
            if (state == 1 && currentChar < end)
            {
                al_draw_text(font, al_map_rgb(255, 255, 255), 2, write_y, 0, str.substr(start, currentChar - start + 1).c_str());
                break;
            }
            else
            {
                al_draw_text(font, al_map_rgb(255, 255, 255), 2, write_y, 0, str.substr(start, end - start).c_str());
                start = end + 1;
                end = str.find('\n', start);
                if (end == -1)
                    end = str.length();
                write_y += 8;
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
    cout << this << ": Setting text to " << str << endl;
    str = insert_newlines(str);
    text.push_back(str);
    if (state == 0)
        state = 1;
}
void Dialogue::set_text(string str, string nm)
{
    cout << this << ": Setting text to " << str << endl;
    str = insert_newlines(str);
    text.push_back(str);
    if (nm != "")
    {
        name = nm;
        showName = true;
    }
    else
    {
        showName = false;
    }
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

vector<string>& Dialogue::get_text()
{
    return text;
}
bool Dialogue::next_line()
{
    currentLine++;
    if (currentLine >= text.size())
    {
        state = 0;
        currentLine = 0;
        text.clear();
        return false;
    }
    state = 1;
    currentChar = 0;
    dialogueStartTime = clock();
    return true;
}
string Dialogue::get_current_line() const
{
    return text[currentLine];
}
bool Dialogue::next_char()
{
    currentChar++;
    if (currentChar >= text[currentLine].size())
    {
        state = 2;
        return false;
    }
    return true;
}
char Dialogue::get_current_char() const
{
    return text[currentLine][currentChar];
}
string Dialogue::get_name() const
{
    return name;
}
bool& Dialogue::show_name()
{
    return showName;
}
