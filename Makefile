# Project name
PROJECT_NAME = games

# Source files (.c)
SRC_FILES = \
	src/main.c \
    src/utils/SDLUtils.c \
    src/tictactoe/game.c \
    src/tictactoe/board.c \
    src/tictactoe/bot.c \
	src/tictactoe/tictactoe.c

# Header files (.h)
INC_FILES = \
    src/utils/SDLUtils.h \
	src/tictactoe/game.h \
    src/tictactoe/board.h \
	src/tictactoe/bot.h \
	src/tictactoe/tictactoe.h

# Compiler flags
CFLAGS = -Wall -Wextra -std=c11 `pkg-config --cflags --libs sdl2` -lm -lSDL2_ttf

# Object files (.o)
OBJ_FILES = $(SRC_FILES:.c=.o)

# Executable file
EXECUTABLE = $(PROJECT_NAME)

# Targets
all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

%.o: %.c $(INC_FILES)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ_FILES) $(EXECUTABLE)

.PHONY: all clean
