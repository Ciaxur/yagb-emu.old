#pragma once

#include "Memory.h"

class CPU {
    private:
        Memory *memory;             // Shared Memory
        uint16_t PC;                // Program Counter
        uint16_t SP;                // Stack Pointer
        uint8_t R[8];               // A,B,C,D,E,F,H,L Registers | F = Flag Register


      public:
        CPU(Memory*);               // Initialize CPU with access to the Memory
        void run();                 // Runs one CPU Cycle
};