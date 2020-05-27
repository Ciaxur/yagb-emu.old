#pragma once

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <functional>
#include <vector>

struct Instruction {
    std::string instruction;
    u_char opcode;
    u_char op1 = 0x00;
    u_char op2 = 0x00;
    std::function<void (Instruction&)> *exec;
};

class Cartridge {
    private:
        void disassemble();
        const char* filePath;
        std::vector<Instruction> instructions;
    
    public:
        Cartridge(const char* path);
        void hexDump(std::ostream &);
};
