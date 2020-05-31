#include "../include/CPU.h"

/**
 * Initialize the CPU
 *  - Assign the Shared Memory
 * 
 * @param mem - Shared Memory
 */
CPU::CPU(Memory *mem) {
    this->memory = mem;
}
