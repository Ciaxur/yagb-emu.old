#pragma once

#include "Memory.h"

class PPU {
    private:
        Memory *memory;             // Shared Memory
    
    public:
        PPU(Memory*);               // Initialize PPU with access to the Memory
};