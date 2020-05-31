#pragma once

#include "Memory.h"

class CPU {
    private:
        Memory *memory;             // Shared Memory
        u_int16_t PC;               // Program Counter
        
    
    public:
        CPU(Memory*);               // Initialize CPU with access to the Memory
        void run();                 // Runs one CPU Cycle
};