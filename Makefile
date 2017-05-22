CC =gcc
CFLAGS =-pedantic -W -Wall -g -std=c99 -Werror -DUNIX -lm -Wextra -Wfloat-equal \
		-Wwrite-strings -Wpointer-arith -Wcast-qual -Wcast-align -Wconversion -Wshadow \
		-Wredundant-decls -Wdouble-promotion -Winit-self -Wswitch-default -Wswitch-enum \
		-Wundef -Wlogical-op -Winline
SDL =-lSDL_ttf -lSDL_image `sdl-config --cflags --libs`

# SRCDIR =src
# BINDIR =bin
# OBJDIR =obj
# FILEDIR =file

all: bin/tree bin/plateau bin/graph bin/catalog bin/backup bin/interfaceSDL bin/Game



bin/tree: obj/tree.o obj/list.o
	$(CC) -o $@ $^ test/test_tree.c $(CFLAGS) -I src/c/

bin/plateau: obj/plateau.o
	$(CC) -o $@ $^ test/test_plateau.c $(CFLAGS) -I src/c/

bin/graph: obj/graph.o obj/list.o
	$(CC) -o $@ $^ test/test_graph.c $(CFLAGS) -I src/c/

bin/catalog: obj/catalog.o
	$(CC) -o $@ $^ test/test_catalog.c $(CFLAGS) -I src/c/

bin/backup: obj/backup.o obj/list.o obj/plateau.o obj/catalog.o
	$(CC) -o $@ $^ test/test_backup.c $(CFLAGS) -I src/c/

bin/interfaceSDL: obj/sdl.o obj/graph.o obj/plateau.o obj/list.o obj/tree.o obj/catalog.o obj/backup.o
	$(CC) -o $@ $^ test/test_interfaceSDL.c src/c/interface.c $(CFLAGS) $(SDL) -I src/c/

bin/Game: obj/Game.class
	cp src/java/Game bin/Game



clean:
	rm -vf bin/*
	rm -vf obj/*



obj/Game.class:
	javac src/java/hexGame/*.java
	mv src/java/hexGame/*.class obj/

obj/sdl.o: src/c/sdl.c
	$(CC) -o $@ -c $< $(CFLAGS) $(SDL) -I src/c/

obj/backup.o: src/c/backup.c
	$(CC) -o $@ -c $< $(CFLAGS) -I src/c/

obj/catalog.o: src/c/catalog.c
	$(CC) -o $@ -c $<

obj/tree.o: src/c/tree.c
	$(CC) -o $@ -c $< -I src/c/

obj/list.o: src/c/list.c
	$(CC) -o $@ -c $<

obj/plateau.o: src/c/plateau.c
	$(CC) -o $@ -c $<

obj/graph.o: src/c/graph.c
	$(CC) -o $@ -c $< $(CFLAGS) -I src/c/
