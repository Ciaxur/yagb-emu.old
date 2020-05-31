#include "../include/Memory.h"


/**
 * Initiates Memory
 *  Zeros out Rest of Memory
 */
Memory::Memory() {
    std::memset(memory, 0x00, 0xFFFF - 0x8000);
}

/**
 * Initiates Memory with Cartridge Data
 *  Zeros out Rest of Memory
 * 
 * @param romData - Vector of Instructions for ROM
 */
Memory::Memory(Cartridge &cartridge) {
    std::memset(memory, 0x00, 0xFFFF - 0x8000);
    load(cartridge);
}

/**
 * Loads Rom Data into Memory with Instructions
 * 
 * @param romData - Vector of Instructions for ROM
 */
void Memory::load(Cartridge &cartridge) {
    this->cartridge = &cartridge;
    this->cartridge->hexDump(this->rom, false); // Load in Hex Dump without Headers
}

/**
 * Dumps raw memory into String with Labels
 */
std::string Memory::dump() { // TODO: Write up Dump
    std::stringstream ss;

    // Setup SS Flags
    ss << std::uppercase << std::hex;

    // TODO: Write up Dump
    ss << "Dump: In the Works...\n";


    return ss.str();
}

/* Getters and Setters for Memory */

/**
 * Returns the Byte Data at given Address
 * 
 * @param addr - Address on Memory
 */
uint8_t Memory::getData(uint16_t addr) {} // TODO:

/**
 * Sets Byte Data at given Address
 *  Returns if write successful
 * 
 * @param addr - Address on Memory
 */
bool Memory::setData(uint16_t addr) {} // TODO: