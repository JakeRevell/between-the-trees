/* Implementation of the event listener thread */

#include <iostream>
#include <ctime>
#include "event_listener.h"

using namespace std;

void* event_listener(ALLEGRO_THREAD* thr, void* arg)
{
    Game& game = *(Game*)arg;
    Window* window = game.get_window();
    Dialogue& dialogueBox = game.get_dialogue_box();
    
    bool shiftKey = false, ctrlKey = false, altKey = false;
    
    ALLEGRO_MOUSE_STATE mouseState;
    
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    al_register_event_source(queue, al_get_display_event_source(window->get_display()));
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_mouse_event_source());
    ALLEGRO_EVENT event;
    
    al_set_target_bitmap(NULL);
    
    while (true)
    {
        al_get_mouse_state(&mouseState);
        game.set_mouse_coords(
            (mouseState.x - window->get_bitmap_x()) / window->get_pix_width(),
            (mouseState.y - window->get_bitmap_y()) / window->get_pix_height()
        );
        
        al_wait_for_event(queue, &event);
        
        if (event.type == ALLEGRO_EVENT_DISPLAY_RESIZE)
        {
            al_acknowledge_resize(window->get_display());
            window->fit_screen();
        }
        else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            game.stop();
        }
        else if (event.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            if (event.keyboard.keycode == ALLEGRO_KEY_LSHIFT || event.keyboard.keycode == ALLEGRO_KEY_RSHIFT)
            {
                if (dialogueBox.get_state() == 1)
                    dialogueBox.get_state() = 2;
                shiftKey = true;
            }
            else if (event.keyboard.keycode == ALLEGRO_KEY_LCTRL)
                ctrlKey = true;
            else if (event.keyboard.keycode == ALLEGRO_KEY_ALT)
                altKey = true;
            else if (event.keyboard.keycode == ALLEGRO_KEY_F11 || (altKey && event.keyboard.keycode == ALLEGRO_KEY_ENTER))
            {
                window->toggle_fullscreen();
                window->fit_screen();
            }
            else if (ctrlKey && altKey && event.keyboard.keycode == ALLEGRO_KEY_F)
            {
                window->set_fit_mode(window->get_fit_mode() + 1);
                window->fit_screen();
            }
            else if (event.keyboard.keycode == ALLEGRO_KEY_DOWN && dialogueBox.get_state() != 0)
            {
                //code here for choosing dialogue options
            }
            else if (event.keyboard.keycode == ALLEGRO_KEY_UP && dialogueBox.get_state() != 0)
            {
                //code here for choosing dialogue options
            }
            else if (event.keyboard.keycode == ALLEGRO_KEY_ENTER)
            {
                switch (dialogueBox.get_state())
                {
                    case 1:
                        dialogueBox.get_state() = 2;
                        break;
                    case 3:
                        dialogueBox.get_state() = 1;
                        break;
                    case 4:
                        dialogueBox.get_state() = 0;
                        break;
                    default:
                        game.next_event();
                        if (dialogueBox.get_state() == 1 && shiftKey)
                            dialogueBox.get_state() = 2;
                        break;
                }
            }
            else if (game.get_scene() != NULL)
                game.get_scene()->key_press_event(event.keyboard.keycode);
        }
        else if (event.type == ALLEGRO_EVENT_KEY_UP)
        {
            if (event.keyboard.keycode == ALLEGRO_KEY_LSHIFT || event.keyboard.keycode == ALLEGRO_KEY_RSHIFT)
                shiftKey = false;
            else if (event.keyboard.keycode == ALLEGRO_KEY_LCTRL)
                ctrlKey = false;
            else if (event.keyboard.keycode == ALLEGRO_KEY_ALT)
                altKey = false;
        }
        else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
        {
            if (game.get_scene() != NULL)
            {
                cout << "click!" << endl;
                game.get_scene()->click_event((mouseState.x - window->get_bitmap_x()) / window->get_pix_width(), (mouseState.y  - window->get_bitmap_y()) / window->get_pix_height());
            }
        }
        
        if (game.should_stop())
        {
            break;
        }
    }
    
    al_destroy_event_queue(queue);
    return NULL;
}
