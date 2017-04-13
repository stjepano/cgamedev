#!/bin/sh

# remove 3rdparty dir first
rm -rf 3rdparty/

# Download SDL2
curl -O https://www.libsdl.org/release/SDL2-devel-2.0.5-mingw.tar.gz
curl -L -o glew-2.0.0-win32.zip https://sourceforge.net/projects/glew/files/glew/2.0.0/glew-2.0.0-win32.zip/download
mkdir temp
mv SDL2-devel-2.0.5-mingw.tar.gz temp/
mv glew-2.0.0-win32.zip temp/
cd temp/
tar -zxvf SDL2-devel-2.0.5-mingw.tar.gz
unzip glew-2.0.0-win32.zip
mkdir ../3rdparty
cp -R SDL2-2.0.5/i686-w64-mingw32/* ../3rdparty/
cp -R glew-2.0.0/bin/Release/Win32/* ../3rdparty/bin/
cp -R glew-2.0.0/lib/Release/Win32/* ../3rdparty/lib/
cp -R glew-2.0.0/include/* ../3rdparty/include/
cd ..
rm -rf temp/