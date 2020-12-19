EXECUTABLE=DialogHello.exe

CC=gcc.exe
C++=g++

LDFLAGS=-lgdi32

src = $(wildcard *.c)
obj = $(src:.c=.o)

all: myprog

myprog: $(obj)
	$(CC) -o $(EXECUTABLE) $^ $(LDFLAGS)

.PHONY: clean
clean:
	del $(obj) $(EXECUTABLE)