#!/bin/sh

# remove 3rdparty dir first
rm -rf 3rdparty/

# Download SDL2
curl -O https://www.libsdl.org/release/SDL2-devel-2.0.5-mingw.tar.gz
curl -L -o glew-2.0.0.tgz https://sourceforge.net/projects/glew/files/glew/2.0.0/glew-2.0.0.tgz/download

mkdir temp
mv SDL2-devel-2.0.5-mingw.tar.gz temp/
mv glew-2.0.0.tgz temp/

cd temp/
tar -zxvf SDL2-devel-2.0.5-mingw.tar.gz
tar -zxvf glew-2.0.0.tgz

mkdir ../3rdparty

cp -R SDL2-2.0.5/i686-w64-mingw32/* ../3rdparty/

# install glew
cd glew-2.0.0
make glew.lib
cp -R include/* ../../3rdparty/include/
cp -R lib/* ../../3rdparty/lib/

cd ../..
rm -rf temp/