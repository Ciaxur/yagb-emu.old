#pragma once

#include "Memory.h"

class CPU {
    private:
        Memory *memory;             // Shared Memory
    
    public:
        CPU(Memory*);               // Initialize CPU with access to the Memory
};