#! /bin/sh -e

f="interface"

cp -v ../$f.* .

sed -i "/\/\/ sdl/,/\/\/ end sdl/d" $f.*
sed -i "/sdl/,/$/d" $f.*
sed -i "/SDL/,/$/d" $f.*
