CC=gcc
SH=sh

3RDPARTY_INCLUDE_DIR=3rdparty/include
COPY=cp

3RDPARTY_LIB_DIR=3rdparty/lib
3RDPARTY_BIN_DIR=3rdparty/bin

CFLAGS=-flto -g -std=c11 -I$(3RDPARTY_INCLUDE_DIR)
LDFLAGS=-L$(3RDPARTY_LIB_DIR) -w -lmingw32 -lglew32 -lopengl32 -lSDL2main -lSDL2

BUILDDIR=build
SOURCEDIR=src

HEADERS=$(wildcard $(SOURCEDIR)/*.h)
SOURCES=$(wildcard $(SOURCEDIR)/*.c)
OBJECTS=$(patsubst $(SOURCEDIR)/%.c, $(BUILDDIR)/%.o, $(SOURCES))
DLLS=$(wildcard $(3RDPARTY_BIN_DIR)/*.dll)

BINARY = main.exe

.PHONY: all clean deps

all: $(BINARY)

$(BUILDDIR)/%.o: $(SOURCEDIR)/%.c ${HEADERS}
	$(CC) $(CFLAGS) -c -o $@ $<

$(BINARY): ${OBJECTS}
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

%.dll: $(3RDPARTY_BIN_DIR)/%.dll
	$(COPY) $< $@

deps:
	./deps.sh

print-%  : ; @echo $* = $($*)

clean:
	rm -f $(OBJECTS) $(BINARY)