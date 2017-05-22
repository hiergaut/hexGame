CC =gcc
CFLAGS =-pedantic -W -Wall -g -std=c99 -Werror -DUNIX -lm -Wextra -Wfloat-equal \
		-Wwrite-strings -Wpointer-arith -Wcast-qual -Wcast-align -Wconversion -Wshadow \
		-Wredundant-decls -Wdouble-promotion -Winit-self -Wswitch-default -Wswitch-enum \
		-Wundef -Wlogical-op -Winline
SDL =-lSDL_ttf -lSDL_image `sdl-config --cflags --libs`
LIB =-I src/c/

# SRCDIR =src
# BINDIR =bin
# OBJDIR =obj
# FILEDIR =file

all: bin obj bin/tree bin/plateau bin/graph bin/catalog bin/backup bin/interfaceSDLV1 bin/interfaceSDLV2 bin/interfaceSDLV3 bin/interface bin/Game

bin:
	mkdir bin

obj:
	mkdir obj

bin/tree: obj/tree.o obj/list.o test/test_tree.c
	$(CC) -o $@ $^ $(CFLAGS) $(LIB)

bin/plateau: obj/plateau.o test/test_plateau.c
	$(CC) -o $@ $^ $(CFLAGS) $(LIB)

bin/graph: obj/graph.o obj/list.o test/test_graph.c
	$(CC) -o $@ $^ $(CFLAGS) $(LIB)

bin/catalog: obj/catalog.o test/test_catalog.c
	$(CC) -o $@ $^ $(CFLAGS) $(LIB)

bin/backup: obj/backup.o obj/list.o obj/plateau.o obj/catalog.o test/test_backup.c
	$(CC) -o $@ $^ $(CFLAGS) $(LIB)

bin/interfaceSDLV1: obj/sdl.o obj/graph.o obj/plateau.o obj/list.o obj/tree.o obj/catalog.o obj/backup.o test/test_interfaceSDLV1.c src/c/interface.c
	$(CC) -o $@ $^ $(CFLAGS) $(SDL) $(LIB)

bin/interfaceSDLV2: obj/sdl.o obj/graph.o obj/plateau.o obj/list.o obj/tree.o obj/catalog.o obj/backup.o test/test_interfaceSDLV2.c src/c/interface.c
	$(CC) -o $@ $^ $(CFLAGS) $(SDL) $(LIB)

bin/interfaceSDLV3: obj/sdl.o obj/graph.o obj/plateau.o obj/list.o obj/tree.o obj/catalog.o obj/backup.o test/test_interfaceSDLV3.c src/c/interface.c
	$(CC) -o $@ $^ $(CFLAGS) $(SDL) $(LIB)
	src/cToJava/mergeInterface.sh
	src/cToJava/makefileJava.sh

bin/interface: obj/graph.o obj/plateau.o obj/list.o obj/tree.o obj/catalog.o obj/backup.o obj/interface.o test/test_interface.c
	$(CC) -o $@ $^ $(CFLAGS) $(SDL) $(LIB)

bin/Game: obj/Game.class
	cp src/java/Game bin/Game



clean:
	rm -vf bin/*
	rm -vf obj/*

run:
	bin/Game

runAll:
	cp file/catalog.txt.default file/catalog.txt
	bin/backup
	bin/catalog
	bin/Game
	bin/graph
	bin/interface
	bin/interfaceSDLV1
	bin/interfaceSDLV2
	bin/interfaceSDLV3
	bin/plateau
	bin/tree


obj/Game.class:
	javac src/java/hexGame/*.java
	mv src/java/hexGame/*.class obj/

obj/interface.o: src/cToJava/interface.c
	$(CC) -o $@ -c $< $(CFLAGS) $(LIB)

obj/sdl.o: src/c/sdl.c
	$(CC) -o $@ -c $< $(CFLAGS) $(SDL) $(LIB)

obj/backup.o: src/c/backup.c
	$(CC) -o $@ -c $< $(CFLAGS) $(LIB)

obj/catalog.o: src/c/catalog.c
	$(CC) -o $@ -c $<

obj/tree.o: src/c/tree.c
	$(CC) -o $@ -c $< $(LIB)

obj/list.o: src/c/list.c
	$(CC) -o $@ -c $<

obj/plateau.o: src/c/plateau.c
	$(CC) -o $@ -c $<

obj/graph.o: src/c/graph.c
	$(CC) -o $@ -c $< $(CFLAGS) $(LIB)
