# Project name
PROJECT_NAME = games

# Source files (.c)
SRC_FILES = \
			src/main.c \
			src/utils/raylibUtils.c \
			src/minesweeper/minesweeper.c \

# Header files (.h)
INC_FILES = \
			src/utls/raylibUtils.h \
			src/minesweeper/minesweeper.h \

# Compiler flags
CFLAGS = -Wall -Wextra -std=c11 -lraylib -lm

# Object files (.o)
OBJ_FILES = $(SRC_FILES:.c=.o)

# Executable file
EXECUTABLE = $(PROJECT_NAME)

# Targets
all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ_FILES)
	$(CC) $(CFLAGS) -g -o $@ $^ $(LDLIBS)

%.o: %.c $(INC_FILES)
	$(CC) $(CFLAGS) -g -c -o $@ $<

clean:
	rm -f $(OBJ_FILES) $(EXECUTABLE)

.PHONY: all clean
