#pragma once

#include "Cartridge.h"
#include <cstring>

/**
 * Memory Map of GB
 *  - Shared between the CPU and PPU
 */
class Memory {
    private:
        // 0x0000 - 0x7FFF | Cartridge ROM Banks (00 - NN)
        std::stringstream rom;          // ROM Hex Dump
        Cartridge *cartridge;           // Pointer to Given Cartride Object

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
        Memory(Cartridge&);                                         // Initializes Memory with Cartridge Data

        void                load(Cartridge&);                       // Loads in Cartridge Data into Memory
        uint8_t             getData(uint16_t addr);                 // TODO: Return the Data at given Address
        bool                setData(uint16_t addr);                 // TODO: Sets the Data at given Address | Returning if Successful
        std::stringstream&  getRomData();                           // Returns ROM Hex Dump String Stream
        std::string         dump();                                 // Returns Dump of Entire Raw Memory Map
};