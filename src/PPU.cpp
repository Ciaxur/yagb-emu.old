#include "../include/PPU.h"

/**
 * Initialize the PPU
 *  - Assign the Shared Memory
 * 
 * @param mem - Shared Memory
 */
PPU::PPU(Memory *mem) {
    this->memory = mem;
}
