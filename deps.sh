#!/bin/sh

# Download SDL2
curl -O https://www.libsdl.org/release/SDL2-devel-2.0.5-mingw.tar.gz
mkdir temp
mv SDL2-devel-2.0.5-mingw.tar.gz temp/
cd temp/
tar -zxvf SDL2-devel-2.0.5-mingw.tar.gz
mkdir ../3rdparty
cp -R SDL2-2.0.5/i686-w64-mingw32/* ../3rdparty/
cd ..
rm -rf temp/