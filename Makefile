# Project names
PROJECT_NAME_UI = ui
PROJECT_NAME_MINESWEEPER = minesweeper
PROJECT_NAME_TICTACTOE = tictactoe

# Source files
SRC_FILES_UI = \
			src/main.c

SRC_FILES_MINESWEEPER = \
			src/minesweeper/minesweeper.c

SRC_FILES_TICTACTOE = \
			src/tictactoe/tictactoe.c

# Utility source files
UTIL_FILES = \
			src/utils/raylibUtils.c

# Header files
INC_FILES = \
			src/utils/raylibUtils.h \
			src/minesweeper/minesweeper.h \
			src/tictactoe/tictactoe.h

# Compiler flags
CFLAGS = -Wall -Wextra -std=c11 -lraylib -lm

# Object files
OBJ_FILES_UI = $(SRC_FILES_UI:.c=.o)
OBJ_FILES_MINESWEEPER = $(SRC_FILES_MINESWEEPER:.c=.o)
OBJ_FILES_TICTACTOE = $(SRC_FILES_TICTACTOE:.c=.o)
OBJ_FILES_UTIL = $(UTIL_FILES:.c=.o)

# Executable files
EXECUTABLE_UI = $(PROJECT_NAME_UI)
EXECUTABLE_MINESWEEPER = $(PROJECT_NAME_MINESWEEPER)
EXECUTABLE_TICTACTOE = $(PROJECT_NAME_TICTACTOE)

# Targets
all: $(EXECUTABLE_UI) $(EXECUTABLE_MINESWEEPER) $(EXECUTABLE_TICTACTOE)

$(EXECUTABLE_UI): $(OBJ_FILES_UI) $(OBJ_FILES_UTIL)
	$(CC) $(CFLAGS) -g -o $@ $^ $(LDLIBS)

$(EXECUTABLE_MINESWEEPER): $(OBJ_FILES_MINESWEEPER) $(OBJ_FILES_UTIL)
	$(CC) $(CFLAGS) -g -o $@ $^ $(LDLIBS)

$(EXECUTABLE_TICTACTOE): $(OBJ_FILES_TICTACTOE) $(OBJ_FILES_UTIL)
	$(CC) $(CFLAGS) -g -o $@ $^ $(LDLIBS)

%.o: %.c $(INC_FILES)
	$(CC) $(CFLAGS) -g -c -o $@ $<

clean:
	rm -f $(OBJ_FILES_UI) $(OBJ_FILES_MINESWEEPER) $(OBJ_FILES_TICTACTOE) \
	$(OBJ_FILES_UTIL) $(EXECUTABLE_UI) $(EXECUTABLE_MINESWEEPER) $(EXECUTABLE_TICTACTOE)

.PHONY: all clean

