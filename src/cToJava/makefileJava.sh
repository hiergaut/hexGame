#! /bin/sh -e

# ./mergeInterface.sh

f="InterfaceAvecC"

javac $f.java
javah -jni $f


gcc -I/usr/lib/jvm/java-8-openjdk/include -I/usr/lib/jvm/java-8-openjdk/include/linux -c *.c -fpic
echo fuck
gcc -shared -o lib$f.so *.o
echo you

# gcc `sdl-config --cflags --libs` -lSDL_ttf -lSDL_image -I/usr/lib/jvm/java-8-openjdk/include -I/usr/lib/jvm/java-8-openjdk/include/linux -c *.c -fPIC
# gcc `sdl-config --cflags --libs` -lSDL_ttf -lSDL_image -shared -o lib$f.so *.o 

javac *.java
java -Djava.library.path=. Main

rm *.o
rm *.class
