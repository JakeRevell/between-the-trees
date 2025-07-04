#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "game.h"
#include "event_listener.h"
#include "draw.h"

#include <iostream>

int main()
{
    al_init();
    al_install_keyboard();
    al_install_mouse();
    al_install_audio();
    al_init_primitives_addon();
    al_init_image_addon();
    al_init_font_addon();
    al_init_acodec_addon();
    al_reserve_samples(16);
    
    al_set_new_display_flags(ALLEGRO_OPENGL | ALLEGRO_RESIZABLE);
    al_set_new_display_option(ALLEGRO_VSYNC, 2, ALLEGRO_REQUIRE);
    al_set_new_display_option(ALLEGRO_CAN_DRAW_INTO_BITMAP, 1, ALLEGRO_REQUIRE);
    
    Game* game = new Game(event_listener, drawer);
    
    while (true)
    {
        if (game->get_scheduled_time() > 0 && clock() >= game->get_scheduled_time())
        {
            game->play_scheduled_func();
        }
        if (game->should_stop())
        {
            delete game;
            break;
        }
    }
    
    al_shutdown_font_addon();
    al_shutdown_image_addon();
    al_shutdown_primitives_addon();
    al_uninstall_keyboard();
    al_uninstall_mouse();
    al_uninstall_system();
    
    return 0;
}
