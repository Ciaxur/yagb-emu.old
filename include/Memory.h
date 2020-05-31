#pragma once

#include "Cartridge.h"
#include <cstring>

/**
 * Memory Map of GB
 *  - Shared between the CPU and PPU
 */
class Memory {
    private:
        std::unordered_map<uint16_t, Instruction> rom;         // 0x0000 - 0x7FFF | Cartridge ROM Banks (00 - NN)

        /** Memory Map (From Pandocs)
         * 
         * 8000-9FFF   8KB Video RAM (VRAM) (switchable bank 0-1 in CGB Mode)
         * A000-BFFF   8KB External RAM     (in cartridge, switchable bank, if any)
         * C000-CFFF   4KB Work RAM Bank 0 (WRAM)
         * D000-DFFF   4KB Work RAM Bank 1 (WRAM)  (switchable bank 1-7 in CGB Mode)
         * E000-FDFF   Same as C000-DDFF (ECHO)    (typically not used)
         * FE00-FE9F   Sprite Attribute Table (OAM)
         * FEA0-FEFF   Not Usable
         * FF00-FF7F   I/O Ports
         * FF80-FFFE   High RAM (HRAM)
         * FFFF        Interrupt Enable Register
         */
        uint8_t memory[0xFFFF - 0x8000];       // Entire Rest of Memory 32KB
        

    public:
        Memory();                                                   // Creates Empty Memory Object
        Memory(std::unordered_map<uint16_t, Instruction>&);         // Initializes Memory with Cartridge Data

        void load(std::unordered_map<uint16_t, Instruction>&);      // Loads in Cartridge Data into Memory
        std::string fullDump();                                     // Returns Dump of Entire Raw Memory
};