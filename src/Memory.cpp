#include "../include/Memory.h"


/**
 * Initiates Memory
 *  Zeros out Rest of Memory
 */
Memory::Memory() {
    std::memset(memory, 0x00, 0xFFFF - 0x8000);
}

/**
 * Initiates Memory with Instructions
 *  Zeros out Rest of Memory
 * 
 * @param romData - Vector of Instructions for ROM
 */
Memory::Memory(std::unordered_map<uint16_t, Instruction> &romData) {
    std::memset(memory, 0x00, 0xFFFF - 0x8000);
    load(romData);
}

/**
 * Loads Rom Data into Memory with Instructions
 * 
 * @param romData - Vector of Instructions for ROM
 */
void Memory::load(std::unordered_map<uint16_t, Instruction> &romData) {
    rom = romData;
}

/**
 * Dumps raw memory into String with Labels
 */
std::string Memory::fullDump() {
    std::stringstream ss;

    // Setup SS Flags
    ss << std::uppercase << std::hex;

    // Dump ROM Bank 0
    ss << "\t [0x0000 - 0x3FFF] - 16KB ROM Bank 00\n";
    for(uint16_t i = 0; i <= 0x3FFF; i++) {
        if(rom[i].instruction.length())
            ss << rom[i].instruction << '\n';
    }

    // Dump ROM Bank 01-NN (0x4000 - 0x7FFF)
    ss << "\t [0x4000 - 0x7FFF] - 16KB ROM Bank 01-NN\n";
    for(uint16_t i = 0x4000; i <= 0x7FFF; i++) {
        if(rom[i].instruction.length())
            ss << rom[i].instruction << '\n';
        else
            ss << "0x" << i << '\n';
    }
    
    // Dump Rest of Memory (0x8000 - 0x9FFF)
    ss << "\t [0x8000 - 0xFFFF] - Rest of Memory\n";
    for(uint32_t i = 0x8000; i <= 0xFFFF; i++) {
        ss << "0x"
            << std::setfill('0') << std::setw(4)
            << i << "\t0x"
            << std::setfill('0') << std::setw(2)
            << int(memory[i - 0x8000]) << '\n';
    }


    return ss.str();
}