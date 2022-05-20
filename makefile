ifndef VERBOSE
.SILENT:
endif

CC = g++
LD = g++
CXXFLAGS = -std=c++20  -Werror #-Wpedantic -Wall
LDFLAGS = 
DEBUG_FLAGS = -DDEBUG -g
RELEASE_FLAGS = -O3

SRC = $(wildcard *.cpp)
OBJ = $(SRC:%.cpp=build/%.o)
DEPENDS = $(SRC:%.cpp=build/%.d)

.PHONY: debug
debug: CXXFLAGS += $(DEBUG_FLAGS)
debug: executable

.PHONY: all
all: CXXFLAGS += $(RELEASE_FLAGS)
all: executable



executable: build_dir widerstand

build_dir:
	mkdir -p build
	mkdir -p build/debug
	mkdir -p build/release

widerstand: $(OBJ)
	echo linking: $(OBJ)
	$(LD) $(CXXFLAGS) -o widerstand  $(OBJ) $(LDFLAGS)

-include $(DEPENDS)
build/%.o: %.cpp 
	echo Compiling $<
	$(CC) $(CXXFLAGS) -MMD -MD -c $< -o $@


.PHONY: clean
clean:
	rm -r build
	rm widerstand