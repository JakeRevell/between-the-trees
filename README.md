## Breaking News: Now with sound!
I have added basic support for audio! Now you can set the background music.


## Compiling (for Linux)
- Make sure you have gcc, make, and allegro installed
- Navigate to the directory that you installed these files to
- And simply run `make`

## On Windows
I've also included a pre-compiled Windows executable. If you're using Windows, the only files you should need are "between_the_trees.exe" (the main program), "dialogue.png" and "name_container.png" (the two placeholder textures for the dialogue box), and the "background" folder.
Make sure they're all downloaded into the same location.

## Other notes
All of the code for the actual scenes themselves will likely be in the "func.h" and "func.cpp" files. Anything else is the base engine that I put together, which shouldn't need to be changed too much except to add some new features (I haven't finished dialogue options, for example).
