prog: main.o 
	gcc main.c enigme.c  -o prog -lSDL -g -lSDL_image -lSDL_ttf -lSDL_mixer -lSDL_gfx

main.o: main.c
	gcc -c main.c -g



