#pragma once

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <functional>
#include <vector>

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

    // Pointer to Opcode's Specific Function
    std::function<void (Instruction&)> *exec;
};


class Cartridge {
    private:    // Private Variables
        const char*                 filePath;           // File Path to ROM
        std::vector<Instruction>    instructions;       // Vector Array of Instructions

    private:    // Private Methods
        void disassemble();                             // Disassembles ROM Instruction storing them into Instructions Vector
    
    public:     // Public Methods
        Cartridge(const char* path);                    // Constructs ROM
        void hexDump(std::ostream &, bool=true);        // Outputs a HexDump of Loaded ROM | Line Numbers Print by Default
};
