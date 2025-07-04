/* Declarations for the event thread */

#ifndef EVENT_LISTENER_H_INCLUDED
#define EVENT_LISTENER_H_INCLUDED

#include <allegro5/allegro.h>
#include "game.h"
#include "window.h"
#include "scene.h"
#include "dialogue.h"

void* event_listener(ALLEGRO_THREAD*, void*);

#endif