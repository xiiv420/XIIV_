CC = gcc
CFLAGS = -Wall -g `sdl-config --cflags`
LDFLAGS = `sdl-config --libs`

OBJS = main.o fonctions.o

the_rebirth: $(OBJS)
	$(CC) -o run $(OBJS) $(LDFLAGS)

main.o: main.c constants.h
	$(CC) $(CFLAGS) -c main.c

fonctions.o: fonctions.c constants.h
	$(CC) $(CFLAGS) -c fonctions.c

clean:
	rm -f $(OBJS) run