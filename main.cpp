#include <allegro5/allegro.h>
#include "game.h"
#include "event.h"
#include "draw.h"

int main()
{
    al_init();
    al_install_keyboard();
    al_install_mouse();
    al_init_primitives_addon();
    al_init_image_addon();
    al_init_font_addon();
    
    al_set_new_display_flags(ALLEGRO_OPENGL | ALLEGRO_RESIZABLE);
    al_set_new_display_option(ALLEGRO_CAN_DRAW_INTO_BITMAP, 1, ALLEGRO_REQUIRE);
    al_set_new_bitmap_flags(ALLEGRO_VIDEO_BITMAP);
    
    Game* game = new Game(event_listener, drawer);
    
    while (true)
    {
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
