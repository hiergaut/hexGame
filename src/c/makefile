CC = gcc
CFLAGS = -pedantic -W -Wall -g -std=c99 -Werror -DUNIX -lm -Wextra -Wfloat-equal \
		 -Wwrite-strings -Wpointer-arith -Wcast-qual -Wcast-align -Wconversion -Wshadow \
		 -Wredundant-decls -Wdouble-promotion -Winit-self -Wswitch-default -Wswitch-enum \
		 -Wundef -Wlogical-op -Winline \
		 -lSDL_ttf -lSDL_image `sdl-config --cflags --libs` \
		 # -DNDEBUG

 
SRC = $(wildcard *.c)
OBJS = $(SRC:.c=.o)
BIN = a.out
 
all : a.out
	cp $(BIN) ../../bin/debugC
 
a.out : $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o : %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean :
	@rm -fv *.o $(BIN)

run:
	./$(BIN)

valgrind:
	valgrind ./$(BIN)

test: all run clean
