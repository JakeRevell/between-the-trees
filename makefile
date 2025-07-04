between_the_trees.exe: main.cpp window.o scene.o audio.o resource.o dialogue.o event_queue.o game.o event_listener.o draw.o func.o
	g++ main.cpp window.o scene.o audio.o resource.o dialogue.o event_queue.o game.o event_listener.o draw.o func.o -o between_the_trees.exe -lallegro -lallegro_image -lallegro_primitives -lallegro_font -lallegro_audio -lallegro_acodec

func.o: func.cpp func.h game.h
	g++ -c func.cpp -o func.o

event_listener.o: event_listener.cpp event_listener.h game.h window.h scene.h dialogue.h
	g++ -c event_listener.cpp -o event_listener.o -lallegro -lallegro_primitives -lallegro_font -lallegro_audio

draw.o: draw.cpp draw.h game.h window.h scene.h dialogue.h resource.h
	g++ -c draw.cpp -o draw.o -lallegro -lallegro_primitives -lallegro_font -lallegro_audio

game.o: game.cpp game.h window.h resource.h scene.h dialogue.h
	g++ -c game.cpp -o game.o -lallegro -lallegro_primitives -lallegro_font -lallegro_audio

event_queue.o: event_queue.cpp event_queue.h game.h audio.h
	g++ -c event_queue.cpp -o event_queue.o -lallegro -lallegro_primitives -lallegro_font -lallegro_audio

dialogue.o: dialogue.cpp dialogue.h resource.h scene.h
	g++ -c dialogue.cpp -o dialogue.o -lallegro -lallegro_font

resource.o: resource.cpp resource.h scene.h
	g++ -c resource.cpp -o resource.o -lallegro -lallegro_font -lallegro_audio

audio.o: audio.cpp audio.h
	g++ -c audio.cpp -o audio.o -lallegro -lallegro_audio

scene.o: scene.cpp scene.h
	g++ -c scene.cpp -o scene.o -lallegro -lallegro_font

window.o: window.cpp window.h
	g++ -c window.cpp -o window.o -lallegro

