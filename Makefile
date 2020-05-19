#Copyright Notice:
OBJS = nep.cpp

CC = g++

COMPILER_FLAGS = -no-pie -Wall -O3

LINKER_FLAGS = -lraylib

#INCLUDES = -I

OBJ_NAME = NepFetch

all: $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

clean:
	rm $(OBJ_NAME)

run: all
	./$(OBJ_NAME)

.PHONY: all clean run
