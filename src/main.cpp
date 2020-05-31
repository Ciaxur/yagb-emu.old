#include <boost/program_options.hpp>
#include <iostream>
#include <string>

#include "../include/CPU.h"
#include "../include/Cartridge.h"
#include "../include/Memory.h"
#include "../include/PPU.h"

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
    const char *romPath{NULL};
    const char *asmOutput{NULL};

    // Construct Program Options (CMD Valid Arguments)
    using namespace boost::program_options;
    options_description desc("Allowed Options");
    desc.add_options()
        ("help,h",                                          "Print Usage Message")
        ("output,o",    value<std::string>(),               "ASM Output File")
        ("rom,r",       value<std::string>()->required(),   "ROM Path");
    

    // Map Command Line Inputs
    variables_map vm;
    try {
        store(parse_command_line(argc, argv, desc), vm);
    
        // Check Given Args
        if(vm.count("help") || vm.empty()) {  // Help Menu
            std::cout << desc << '\n';
            return 0;
        }

        if(vm.count("rom")) {       // Given ROM Path
            romPath = vm["rom"].as<std::string>().c_str();
            // std::cout << "ROM Path Given: " << romPath << '\n'; // DEBUG: Outputs
        }

        if(vm.count("output")) {    // Given Output File
            asmOutput = vm["output"].as<std::string>().c_str();
            // std::cout << "Output File Given: " << asmOutput << '\n'; // DEBUG: Outputs
        }


        // Verify Arguments (Required Args)
        notify(vm);
    }
    catch(invalid_command_line_syntax &e) {
        std::cerr << "Argument Error: " << e.what() << '\n';
        return 1;
    }
    catch(required_option &e) {
        std::cerr << "Required Argument not Given! " << e.what() << '\n';
        return 1;
    }


    
    // Load in Cartridge
    Cartridge rom(romPath);

    // Check for Hex Dump
    if(asmOutput != NULL) {
        std::cout << "Hex Dump written to: " << asmOutput << '\n';
        
        std::ofstream out(asmOutput, std::ios::out);    // Overwrite!
        rom.hexDump(out);
        out.close();
    }

    // Initiate Memory, loading Cartridge Data
    Memory sharedMemory(rom.getData());

    // Initiate CPU, sharing the Memory
    CPU cpu(&sharedMemory);

    // Initiate PPU, sharing the Memory
    PPU ppu(&sharedMemory);
    
    // DEBUG: Output Raw Memory Dump to File
    std::ofstream file("main.asm", std::ios::out);
    file << sharedMemory.fullDump();    
    file.close();

    return 0;
}
