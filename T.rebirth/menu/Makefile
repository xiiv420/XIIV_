CC = gcc
CFLAGS = -Wall -Wextra `sdl-config --cflags` -Icore
LDFLAGS = `sdl-config --libs` -lSDL_mixer -lSDL_ttf -lSDL_image

# Source files
SRC = main.c menu.c \
      core/utilities.c core/main_menu.c core/options_menu.c \
      core/save_menu.c core/player_menu.c core/best_score.c

# Object files
OBJ = $(SRC:.c=.o)

# Output binary
TARGET = game

# Default rule
all: $(TARGET)

# Linking step
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LDFLAGS)

# Compile each .c file into .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -f $(OBJ) $(TARGET)
