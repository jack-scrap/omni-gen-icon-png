CXX=g++

BUILDDIR=build

STATIC=main.cpp disp.cpp prog.cpp util.cpp
OBJ_STATIC=$(STATIC:%.cpp=$(BUILDDIR)/%.o)

GL=-lGLEW -lGL
SDL=-lSDL2 -lSDL2_image
LDFLAGS+=$(SDL)
LDFLAGS+=$(GL)

.PHONY: all
all: mk_build make mk_o

$(BUILDDIR)/%.o: %.cpp %.h
	$(CXX) -c $< -o $@ $(LDFLAGS)

$(BUILDDIR)/main.o: main.cpp
	$(CXX) -c $< -o $@ $(LDFLAGS)

.PHONY: make
make: $(OBJ_STATIC) $(HDR)
	$(CXX) $^ $(LDFLAGS) -o a.out

.PHONY: mk_build
mk_build:
	mkdir -p $(BUILDDIR)

.PHONY: mk_o
mk_o:
	mkdir -p o

.PHONY: clean
clean:
	rm $(BUILDDIR)/*.o a.out
