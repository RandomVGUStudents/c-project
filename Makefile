SRC_PATH = src
HEADER_PATH = src/headers
PROJECTS = minesweeper tictactoe gameui
UTIL = myUtils

# Project header files
HDR_FILES = $(HEADER_PATH)/$(UTIL).h \
            $(foreach proj,$(PROJECTS),$(HEADER_PATH)/$(proj).h)

# Object files
OBJ_FILES = $(SRC_PATH)/$(UTIL).o \
            $(foreach proj,$(PROJECTS),$(SRC_PATH)/$(proj).o)

# Compiler flags
CFLAGS = -Wall -Wextra -std=c11 -lraylib -lm

all: $(PROJECTS)

# Rule to build each project executable
$(PROJECTS): %: $(SRC_PATH)/%.o $(SRC_PATH)/$(UTIL).o
	$(CC) $(CFLAGS) -g -o $@ $^

# Rule to build object files
$(SRC_PATH)/%.o: $(SRC_PATH)/%.c $(HDR_FILES)
	$(CC) $(CFLAGS) -g -c -o $@ $<

clean:
	rm -f $(PROJECTS) $(OBJ_FILES)

.PHONY: all clean
