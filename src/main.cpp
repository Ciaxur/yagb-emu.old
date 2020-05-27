#include <iostream>
#include <string>

#include "../include/Cartridge.h"

// Window Dimensions (GB Res = 160x144)
#define RES_SCALE 4
#define WIDTH 160
#define HEIGHT 144

// 0  White
// 1  Light gray
// 2  Dark gray
// 3  Black
enum GB_COLORS {
    COLOR0 = 0xFFFFFF,
    COLOR1 = 0xAAAAAA,
    COLOR2 = 0x555555,
    COLOR3 = 0x000000
};

int main(int argc, char **argv) {
    // Argument Variables
    char *romPath{NULL};
    char *asmOutput{NULL};

    // Verify ROM Given
    if(argc < 2) {
        std::cerr << "No ROM Given!\n";
        return 1;
    }
        
    // Assume First Argument is the ROM Path
    romPath = argv[1];
    std::cout << "ROM GIVEN: " << romPath << '\n';

    // Create a Cartridge & Dump
    Cartridge rom(romPath);
    // rom.hexDump(out);

    return 0;
}
