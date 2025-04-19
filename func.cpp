/* Implementations of the scene functions */

#include <iostream>
#include "game.h"
#include "func.h"

using namespace std;

void scene0(void* gm_ptr)
{
    Game& game = *(Game*)gm_ptr;
    game.set_text("Hello world!", "Name");
    game.set_text("This is a test message.");
    game.set_text("...");
    game.set_text("Let's see how it works with multiple lines!\nThis is a new line.\nCrazy!");
    game.set_text("What about text that is really really really really really really really really really long?");
}
void scene0_end(void* gm_ptr)
{
    Game& game = *(Game*)gm_ptr;
    game.stop();
}
