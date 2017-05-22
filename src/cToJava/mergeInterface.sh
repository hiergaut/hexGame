#! /bin/sh -e


fin="src/c/interface.*"
fout="src/cToJava/interface.*"

# cp -v ../c/$f.* .
cp -v $fin src/cToJava/

sed -i "/\/\/ sdl$/,/\/\/ end sdl$/d" $fout
# sed -i "/sdl/,/$/d" $f.*
# sed -i "/SDL/,/$/d" $f.*
sed -i 's/.*sdl.*//' $fout
sed -i 's/.*SDL.*//' $fout
