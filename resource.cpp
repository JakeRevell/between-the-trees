/* Implementation of the ResourceLoader class
 *
 * The load function is incomplete since we don't yet
 * have any resources to load.
*/

#include <iostream>

#include "resource.h"
#include "func.h"

using namespace std;

ResourceLoader::ResourceLoader(AudioManager* audio_mng_ptr)
{
    font = al_create_builtin_font();
    textContainer = al_create_bitmap(0, 0);
    nameContainer = al_create_bitmap(0, 0);
    numBackgrounds = 0;
    numScenes = 0;
    backgrounds = NULL;
    loadedScenes = NULL;
    audioManager = audio_mng_ptr;
}
ResourceLoader::~ResourceLoader()
{
    al_destroy_font(font);
    al_destroy_bitmap(textContainer);
    al_destroy_bitmap(nameContainer);
    for (int i = 0; i < numBackgrounds; i++)
        al_destroy_bitmap(backgrounds[i]);
    free(backgrounds);
    for (int i = 0; i < numScenes; i++)
    {
        delete loadedScenes[i];
    }
    free(loadedScenes);
}

void ResourceLoader::load(int bank, void* gm_ptr)
{
    //more coming soon!
    switch (bank)
    {
        case 0:
        {
            audioManager->load_sample("bg_music", "music.opus");
            audioManager->load_sample("short_clip" , "music_short.opus");
            textContainer = al_load_bitmap("./dialogue.png");
            nameContainer = al_load_bitmap("./name_container.png");
            numBackgrounds = 1;
            backgrounds = (ALLEGRO_BITMAP**)malloc(sizeof(void*));
            backgrounds[0] = al_load_bitmap("./background/test.png");
            numScenes = 1;
            loadedScenes = (Scene**)malloc(sizeof(void*));
            loadedScenes[0] = new Scene(gm_ptr, backgrounds[0], &scene0_start, NULL, NULL, &scene0_end);
            cout << "Loaded scenes: " << loadedScenes << endl << "[0]: " << loadedScenes[0] << endl;
            break;
        }
        default:
            break;
    }
}

ALLEGRO_FONT* ResourceLoader::get_font() const
{
    return font;
}
ALLEGRO_BITMAP* ResourceLoader::get_text_container() const
{
    return textContainer;
}
ALLEGRO_BITMAP* ResourceLoader::get_name_container() const
{
    return nameContainer;
}
ALLEGRO_BITMAP* ResourceLoader::get_background(int index) const
{
    return backgrounds[index];
}
Scene** ResourceLoader::get_scenes() const
{
    return loadedScenes;
}
int ResourceLoader::get_num_scenes() const
{
    return numScenes;
}
