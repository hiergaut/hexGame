#! /bin/sh -e

f="interface"

cp -v ../c/$f.* .

sed -i "/\/\/ sdl$/,/\/\/ end sdl$/d" $f.*
# sed -i "/sdl/,/$/d" $f.*
# sed -i "/SDL/,/$/d" $f.*
sed -i 's/.*sdl.*//' $f.*
sed -i 's/.*SDL.*//' $f.*
