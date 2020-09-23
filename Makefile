all:
	gcc ./src/*.c -lSDL2 -lSDL2_image -o game

clean:
	rm game 
