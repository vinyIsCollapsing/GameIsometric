#!/bin/bash

# Colors for output
GREEN="\033[1;32m"
YELLOW="\033[1;33m"
RED="\033[1;31m"
RESET="\033[0m"

echo -e "${YELLOW}Skip the menu and start the game directly? (y/n)${RESET}"
read -r SKIP_INPUT

# Define CMake flag
if [[ "$SKIP_INPUT" == "y" || "$SKIP_INPUT" == "Y" ]]; then
    SKIP_FLAG="-DSKIP_MENU=ON"
    echo -e "${GREEN}Menu will be skipped.${RESET}"
else
    SKIP_FLAG="-DSKIP_MENU=OFF"
    echo -e "${GREEN}Menu will be displayed normally.${RESET}"
fi

# If build/ exists, remove it (prevents invalid CMake cache issues)
if [[ -d build ]]; then
    echo -e "${YELLOW}Cleaning old build directory...${RESET}"
    rm -rf build
fi

# Create a fresh build directory
mkdir -p build

echo -e "${YELLOW}Configuring project with CMake...${RESET}"
cmake $SKIP_FLAG -Bbuild

# If CMake configuration failed, stop here
if [[ $? -ne 0 ]]; then
    echo -e "${RED}CMake configuration failed. Aborting.${RESET}"
    exit 1
fi

echo -e "${YELLOW}Building project...${RESET}"
cmake --build build

# Check if the executable exists
if [[ -f build/game ]]; then
    echo -e "${GREEN}Build succeeded!${RESET}"
    echo -e "${YELLOW}Running the game...${RESET}"
    ./build/game
else
    echo -e "${RED}Error: executable 'game' was not found.${RESET}"
    exit 1
fi
