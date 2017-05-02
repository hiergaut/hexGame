CC = gcc
CFLAGS = -W -Wall -std=c99 -Werror -DUNIX -lm -Wextra -Wfloat-equal -Wwrite-strings  \
-Wpointer-arith -Wcast-qual -Wcast-align -Wconversion -Wshadow -Wredundant-decls  \
-Wdouble-promotion -Winit-self -Wswitch-default -Wswitch-enum -Wundef -Wlogical-op -Winline
LDFLAGS = -lm
 
SRC = $(wildcard *.c)
OBJS = $(SRC:.c=.o)
BIN = a.out
 
all : a.out
 
a.out : $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

%.o : %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean :
	@rm -fv *.o $(BIN)

run:
	./$(BIN)

valgrind:
	valgrind ./$(BIN)

test: all valgrind clean
