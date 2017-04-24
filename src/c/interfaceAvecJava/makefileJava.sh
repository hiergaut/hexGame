#! /bin/sh -e

os=$(cat /etc/os-release | head -n1 | awk -F\" '{print $2}')
if [ "$os" != "Arch Linux" ]
then
    echo "Pas touche, Amine"
    exit 1
fi


f="InterfaceAvecC"

javac $f.java
javah -jni $f


gcc `sdl-config --cflags --libs` -lSDL_ttf -lSDL_image -I/usr/lib/jvm/java-8-openjdk/include -I/usr/lib/jvm/java-8-openjdk/include/linux -c *.c -fPIC
gcc `sdl-config --cflags --libs` -lSDL_ttf -lSDL_image -shared -o lib$f.so *.o 

javac *.java
java -Djava.library.path=. Main | sleep 0

rm *.o
rm *.class
rm *.log
