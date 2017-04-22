#! /bin/sh -e

f="InterfaceAvecC"

javac $f.java
javah -jni $f


gcc -I/usr/lib/jvm/java-8-openjdk/include -I/usr/lib/jvm/java-8-openjdk/include/linux -c *.c -fPIC
gcc -shared -o lib$f.so *.o

javac *.java
java -Djava.library.path=. Main

rm *.o
rm *.class
