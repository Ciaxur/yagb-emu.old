#pragma once

#include "Memory.h"

/* Easier Readability of Register */
enum REGISTER {
    A,  // Accumulator
    B,  // Upper of BC
    C,  // Lower of BC
    D,  // Upper of DE
    E,  // Lower of DE
    F,  // Flags
    H,  // High
    L   // Low
};

class CPU {
    protected:
        Memory *memory;             // Shared Memory
        uint16_t PC;                // Program Counter
        uint16_t SP;                // Stack Pointer

        // A,B,C,D,E,F,H,L Registers
        // F = Flag Register
        //  - Bit7   = ZF (Zero Flag)
        //  - Bit6   = N  (Add[0]/Sub Flag[1])
        //  - Bit5   = H  (half Carry Flag)
        //  - Bit4   = CY (Carry Flag)
        //  - Bit3-0 = Not Used (Zeros)
        uint8_t R[8];


      public:
        CPU(Memory*);               // Initialize CPU with access to the Memory
        void run();                 // Runs one CPU Cycle

    
    protected: // Instruction Set
        void ADD(uint8_t*);         // 0x80-0x87 | ADD A, r8
};