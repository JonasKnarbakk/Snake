# Wich compiler to use
NAME=Oppgave1

CXX=clang++

# Wich options to compile with
CXXFLAGS=-std=c++11 -Wall -Wextra

# Linking libraries
LDFLAGS=-L/Library/Frameworks -lSDL2 -lSDL2_ttf -lSDL2_mixer

SOURCES=Main.cpp GameManager.cpp InputManager.cpp Timer.cpp SDL/SDLBmp.cpp SDL/SDLError.cpp SDL/SDLManager.cpp
SRC_FILES=$(addprefix src/,$(SOURCES))

default: $(SRC_FILES)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o bin/$(NAME)
setup:
	@sh setup.sh
run:
	./bin/$(NAME)
clean:
	rm bin/$(NAME)
