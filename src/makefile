CXX=/usr/bin/g++
CXXFLAGS=-O3 -g3 -Wall
BIN_NAME=librarious
PUBLIC_HEADERS=
INTERNAL_HEADERS=
OBJECTS= \
	build/obj/main.o

build/obj/%.o: $(addsuffix .cc,$(basename $(notdir $@)))
	$(CXX) -c $(CXXFLAGS) -o $@ $(addsuffix .cc,$(basename $(notdir $@)))

all: build-dir $(BIN_NAME)

build-dir:
	@/usr/bin/mkdir -p build/bin build/obj

clean:
	@/usr/bin/rm -f build/bin/$(BIN_NAME) build/obj/* *~

full-clean: clean
	@/usr/bin/rm -rf build

$(BIN_NAME): build/bin/$(BIN_NAME)
build/bin/$(BIN_NAME): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o build/bin/$(BIN_NAME) $(OBJECTS)

test: all
	@build/bin/$(BIN_NAME)

