CXX=g++

BUILDDIR=build

STATIC=main.cpp disp.cpp prog.cpp util.cpp
OBJ_STATIC=$(STATIC:%.cpp=$(BUILDDIR)/%.o)

GL=-lGLEW -lGL
SDL=-lSDL2 -lSDL2_image
LDFLAGS+=$(SDL)
LDFLAGS+=$(GL)

.PHONY: clean mk_build mk_o

all: mk_build make mk_o

$(BUILDDIR)/%.o: %.cpp %.h
	$(CXX) -c $< -o $@ $(LDFLAGS)

$(BUILDDIR)/main.o: main.cpp
	$(CXX) -c $< -o $@ $(LDFLAGS)

make: $(OBJ_STATIC) $(HDR)
	$(CXX) $^ $(LDFLAGS) -o a.out

mk_build:
	mkdir -p $(BUILDDIR)

mk_o:
	mkdir -p o

clean:
	rm $(BUILDDIR)/*.o a.out
