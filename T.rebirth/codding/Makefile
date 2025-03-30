CC = gcc
CFLAGS = -Wall -Wextra -std=c99 `sdl-config --cflags`
LDFLAGS = `sdl-config --libs`  # Removed -lSDL_ttf
SRC = main.c input.c background.c jumping.c gameover.c platform.c player.c
OBJ = $(SRC:.c=.o)
EXEC = game

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $(EXEC) $(OBJ) $(LDFLAGS)

%.o: %.c header.h
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -f $(OBJ) $(EXEC)
