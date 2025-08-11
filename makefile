LIBS_MAIN = -lallegro -lallegro_image -lallegro_primitives -lallegro_font -lallegro_audio -lallegro_acodec
OBJS = window.o scene.o audio.o resource.o dialogue.o event_queue.o game.o event_listener.o actor.o draw.o func.o
BUILD = build
OBJS_MAIN := $(addprefix $(BUILD)/,$(OBJS))

MAIN = g++ main.cpp $(OBJS_MAIN) -o between_the_trees.exe $(LIBS_MAIN) 

between_the_trees.exe: main.cpp $(OBJS_MAIN) | $(BUILD)
	$(MAIN)

test.exe: main.cpp $(OBJS_MAIN) | $(BUILD)
	$(MAIN) -g -DDEBUG

$(BUILD)/func.o: func.cpp func.h game.h scene.h actor.h | $(BUILD)
	g++ -c func.cpp -o $(BUILD)/func.o

$(BUILD)/actor.o: actor.cpp actor.h | $(BUILD)
	g++ -c actor.cpp -o $(BUILD)/actor.o -lallegro -lallegro_image

$(BUILD)/event_listener.o: event_listener.cpp event_listener.h game.h window.h scene.h dialogue.h | $(BUILD)
	g++ -c event_listener.cpp -o $(BUILD)/event_listener.o -lallegro -lallegro_primitives -lallegro_font -lallegro_audio

$(BUILD)/draw.o: draw.cpp draw.h game.h window.h scene.h dialogue.h resource.h | $(BUILD)
	g++ -c draw.cpp -o $(BUILD)/draw.o -lallegro -lallegro_primitives -lallegro_font -lallegro_audio

$(BUILD)/game.o: game.cpp game.h window.h resource.h scene.h dialogue.h | $(BUILD)
	g++ -c game.cpp -o $(BUILD)/game.o -lallegro -lallegro_primitives -lallegro_font -lallegro_audio

$(BUILD)/event_queue.o: event_queue.cpp event_queue.h game.h audio.h | $(BUILD)
	g++ -c event_queue.cpp -o $(BUILD)/event_queue.o -lallegro -lallegro_primitives -lallegro_font -lallegro_audio

$(BUILD)/dialogue.o: dialogue.cpp dialogue.h resource.h scene.h | $(BUILD)
	g++ -c dialogue.cpp -o $(BUILD)/dialogue.o -lallegro -lallegro_font

$(BUILD)/resource.o: resource.cpp resource.h scene.h | $(BUILD)
	g++ -c resource.cpp -o $(BUILD)/resource.o -lallegro -lallegro_font -lallegro_audio

$(BUILD)/audio.o: audio.cpp audio.h | $(BUILD)
	g++ -c audio.cpp -o $(BUILD)/audio.o -lallegro -lallegro_audio

$(BUILD)/scene.o: scene.cpp scene.h | $(BUILD)
	g++ -c scene.cpp -o $(BUILD)/scene.o -lallegro -lallegro_font

$(BUILD)/window.o: window.cpp window.h | $(BUILD)
	g++ -c window.cpp -o $(BUILD)/window.o -lallegro

$(BUILD):
	mkdir $(BUILD)

