# C GameDev (just for fun)

This is something I like to play with when I am bored, nothing serious here.

## Prerequisites

* SDL2
* Optionally, flex

## Compile and run

Windows and MINGW32/MSYS assumed.

```
chmod +x deps.sh    # make deps.sh executable
make deps           # download dependencies, see deps.sh for details
# make lex            this is optional, generates c source files from lex sources
make all            # make executable
make SDL2.dll       # copy SDL2.dll from 3rdparty bin dir
```

Execute the program:
```
./main.exe
```

