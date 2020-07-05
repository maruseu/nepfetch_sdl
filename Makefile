OBJS = main.c

OBJ_NAME = NepFetch

CC = cc

COMPILER_FLAGS = -no-pie -Wall -O3

LINKER_FLAGS = -L/usr/lib/ -l"SDL2_ttf" -l"SDL2_image" -l"SDL2"

INCLUDES = -I/usr/include/SDL2/

all: $(OBJS) $(HEADERS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) $(INCLUDES) -o $(OBJ_NAME)

clean:
	rm $(OBJ_NAME)

run: all
	./$(OBJ_NAME)

.PHONY: all clean run
