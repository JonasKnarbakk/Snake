#!bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color

UNAME=$(uname)

if [ -d "bin" ]
    then mkdir bin
fi
if [ "${UNAME}" == "Darwin" ]
    then echo "${GREEN}OS X detected, looking for SDL2 libs${NC}"
	if [ -d "/usr/local/Cellar/sdl2" ]
		then echo "${GREEN}SDL2 is already installed${NC}"
	else
		echo "${RED}SDL2 is not installed${NC}"
	fi
	
	if [ -d "/usr/local/Cellar/sdl2_ttf" ]
		then echo "${GREEN}SDL2_ttf is already installed${NC}"
	else 
		echo "${RED}SDL2_ttf is not installed${NC}"
	fi

	if [ -d "/usr/local/Cellar/sdl2_mixer" ]
		then echo "${GREEN}SDL2_mixer is already installed${NC}"
	else 
		echo "${RED}SDL2_mixer is not installed${NC}"
	fi
	
	if [ -d "/usr/local/Cellar/sdl2_mixer" -a -d "/usr/local/Cellar/sdl2_ttf" ]
		then true
	elif [ -a "/usr/local/bin/brew" ]
	    then echo "${GREEN}Brew detected, attempting to install missing libs${NC}"
        if [ ! -d "/usr/local/Cellar/sdl2" ]
            then echo "${GREEN}Installing SDL2${NC}" && brew install sdl2
            if [ -d "/usr/local/Cellar/sdl2" ]
                then echo "${GREEN}SDL2 installed successfully${NC}"
            fi
        fi
        if [ ! -d "/usr/local/Cellar/sdl2_ttf" ]
            then echo "${GREEN}Installing SDL2_ttf${NC}" && brew install sdl2_ttf
            if [ -d "/usr/local/Cellar/sdl2_ttf" ]
                then echo "${GREEN}SDL2_ttf installed successfully${NC}"
            fi
        fi
        if [ ! -d "/usr/local/Cellar/sdl2_mixer" ]
            then echo "${GREEN}Installing SDL2_mixer${NC}" && brew install sdl2_mixer
            if [ -d "/usr/local/Cellar/sdl2_mixer" ]
                then echo "${GREEN}SDL2_mixer installed successfully${NC}"
            fi
        fi
            else echo "${RED}Brew is not installed, install brew first or get the missing SDL2 libs manually${NC}"
    fi
fi
	
if [ "${UNAME}" == "Linux" ]
    then echo -e "${GREEN}Linux detected, looking for SDL2${NC}"
    if [ -f "/usr/include/SDL2/SDL.h" ]
        then echo -e -e "${GREEN}SDL2 is already installed${NC}"
    else
        echo -e "${RED}SDL2 is not installed, installing...${NC}" && sudo pacman -S sdl2
    fi
fi
