SH=/bin/bash

CXX=g++

BUILDDIR=build

PREFIX:=/usr/local

BINDIR:=$(PREFIX)/bin
LIBDIR:=$(PREFIX)/lib

STATIC=main.cpp disp.cpp prog.cpp util.cpp
OBJ_STATIC=$(STATIC:%.cpp=$(BUILDDIR)/%.o)

GLFLAGS=-lGLEW -lGL
SDLFLAGS=-lSDL2 -lSDL2_image
LDFLAGS+=$(SDLFLAGS)
LDFLAGS+=$(GLFLAGS)

.PHONY: all
all: mk_build omni_gen_icon mk_o

$(BUILDDIR)/%.o: %.cpp %.h
	$(CXX) -c $< -o $@ $(LDFLAGS)

$(BUILDDIR)/main.o: main.cpp
	$(CXX) -c $< -o $@ $(LDFLAGS)

.PHONY: make
omni_gen_icon: $(OBJ_STATIC) $(HDR)
	$(CXX) $^ $(LDFLAGS) -o $@

.PHONY: mk_build
mk_build:
	mkdir -p $(BUILDDIR)

.PHONY: mk_o
mk_o:
	mkdir -p o

.PHONY: install
install:
	sudo cp omni_gen_icon $(BINDIR)

.PHONY: clean
clean:
	rm $(BUILDDIR)/*.o omni_gen_icon
