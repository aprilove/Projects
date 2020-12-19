PROG = Main

CC = g++
INCLUDE_DIR = include
CLASS_DIR = class
OBJ_DIR = obj
LIB_DIR = lib

CPPFLAGS = -g -Wall -I$(INCLUDE_DIR)
LDFLAGS = -lm

SRC = $(wildcard $(CLASS_DIR)/*.cpp)
OBJS = $(patsubst $(CLASS_DIR)%.cpp,$(OBJ_DIR)/%.o,$(SRC))

$(OBJ_DIR)/%.o: $(CLASS_DIR)%.cpp
	$(CC) $(CPPFLAGS) -c -o $@ $<

$(PROG) : Main.o $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^


.PHONY: clean

clean:
	del /S *.o