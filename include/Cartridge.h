#pragma once

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <functional>
#include <unordered_map>

/**
 * Instruction Structure for Simplifying
 *  readability as well as keeping track
 *  of Instruction Data
 */
struct Instruction {
    std::string instruction;        // String of Disassembled Instruction (ex. CALL 0x100)
    u_char      opcode;             // Opcode of Instruction
    u_char      op1 = 0x00;         // First Operand of Instruction
    u_char      op2 = 0x00;         // Second Operand of Instruction
};


class Cartridge {
    private:    // Private Variables
        const char* filePath;                                       // File Path to ROM

    public:     // Public Methods
        Cartridge(const char* path);                                // Constructs ROM
        void hexDump(std::ostream &, bool=true);                    // Outputs a HexDump of Loaded ROM | Line Numbers Print by Default
        void disassemble(std::ostream&);                            // Disassembles ROM Instruction outputting to Output Stream
};
