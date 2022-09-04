CXX=g++

STATIC=main disp prog util
OBJ_STATIC=$(patsubst %, %.o, $(STATIC))

GL=-lGLEW -lGL
SDL=-lSDL2 -lSDL2_image
LDFLAGS+=$(SDL)
LDFLAGS+=$(GL)

.PHONY: clean mk_o

all: make mk_o

%.o: %.cpp %.h
	$(CXX) -c $< -o $@ $(LDFLAGS)

main.o: main.cpp
	$(CXX) -c $< -o $@ $(LDFLAGS)

make: $(OBJ_STATIC) $(HDR)
	$(CXX) $^ $(LDFLAGS)

mk_o:
	mkdir -p o

clean:
	rm *.o a.out
