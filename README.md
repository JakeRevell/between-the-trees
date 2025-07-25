## Changes and Additions in the Latest Commit
It is a very small commit, but it added:
- A test build; you can now run `make test` to make a debug build of the game, and use something like gdb for debugging.
  - Later on, this seperate build could be useful for having a debugger embedded in the game itself, giving useful info and perhaps modification
- Changed how actors are created; instead of a three line instantion, you can simply call `create_actor(string name)` on a scene, and it will create it for you.

## Changes and additions from the Previous Commits

### Dialogue options!
- Finally implemented the ability to choose options from the dialogue
  - Use the command `set_option(string text, void (*func)(void*))` to add a new option.
  - This must be called for each option (if you want to have three different choices, this must be called three times).
  - These commands should be called at the end of the current function.
  - You can use the mouse or arrow keys to choose between or select the options.



### Actors!
- Implemented Actors from the "actors", with a few commands themselves:
  - `get_name()`
  - `get_emotion()`
  - `load_emotion(string name)` will load the given image
  - `show()` and `hide()` functions to show and hide the actor
  - `set_position()` to set the x and y position of the actor
  - a `draw()` function that gets called by the scene
- The scene has the following new functions:
  - `add_actor(Actor* actor)`, which adds the given actor to the scene
  - `get_actor(string actor_name)`, which gets the actor if found, or returns `NULL`

### Audio System
- Implemented the audio system from the "audio" branch, with some modifications:
  - Audio can now be stopped.
  - `set_bg_music` has been removed, as the `play` function should be used instead.
  - `loop`, `gain`, `pan`, and `speed` are all optional arguments in the `play` function (samples can also have their own gain, pan, and speed values, which the `play` function arguments are added to, except for speed, which is multiplied).
  - Samples are now properly destroyed when the destructor is called.

### Event Queue System
- The game now runs on an event queue system.
- Possible commands:
  - `clear_event_queue()`
  - `set_text(string str, string name = "")`
  - `play_audio(string name, bool loop = false, float gain = 1.0, float pan = 0.0, float speed = 1.0)`
  - `stop_audio(string name)`
  - `play_func(void (*func)(void*))` : technical event for playing a separate function
  - `after(float secs, void (*func)(void*))` : plays a function after a specified amount of time (does not pause the current function)

### Dialogue Changes
- New smooth animation for the dialogue box entering and leaving the screen.
- The dialogue box no longer has its own queue system.
- Holding shift or tapping return shows the full text immediately, without printing each character one at a time.

### Other Changes
- Renamed `event.cpp` and `event.h` (which handles keyboard and mouse events) to `event_listener.cpp` and `event_listener.h` to avoid confusion with the event queue system (`event_queue.cpp` and `event_queue.h`).
- Quite possibly a few other things that I may have forgotten about.
- from macjja: made it so clicking advances scene for now (except when some other function is currently being used for clicks)

## Compiling (for Linux)
- Make sure you have gcc, make, and allegro installed
- Navigate to the directory that you installed these files to
- And simply run `make`

## On Windows
I've also included a pre-compiled Windows executable. If you're using Windows, the only files you should need are `between_the_trees.exe` (the main program), `dialogue.png` and `name_container.png` (the two placeholder textures for the dialogue box), `music.opus` and `music_short.opus` (the music tracks), and the `background` folder.
Make sure they're all downloaded into the same location.

## Other notes
All of the code for the actual scenes themselves will likely be in the `func.h` and `func.cpp` files. Anything else is the base engine that I put together, which shouldn't need to be changed too much except to add some new features (I haven't finished dialogue options, for example).
