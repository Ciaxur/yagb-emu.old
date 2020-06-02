#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../include/CPU.h"


/**
 * Dummy Class to Open up Protected
 *  Members for Checking
 */
class CPU_Dummy : CPU {
    public:
        /**
         * Get the Address of Registers for Public Use
         */
        CPU_Dummy(Memory *mem): CPU(mem) {
            this->R = CPU::R;
        };


        /**
         * Resets CPU to Default
         */
        void reset() {
            // Reset the Register Values
            memset(R, 0x00, 8 * sizeof(uint8_t));
        }

    public: // Open Protected Members to the Public
        uint8_t *R;         // CPU Registers

        void ADD(uint8_t *r8) { CPU::ADD(r8); }
        void ADC(uint8_t *r8) { CPU::ADC(r8); }
};


// Global Variables
Memory mem;
CPU_Dummy cpu(&mem);



/**
 * Prints CPU Registers
 */
void printRegisters(CPU_Dummy *cpu) {
    for (int i = 0; i < 8; i++) {
        printf("REG[%d] = %X\n", i, cpu->R[i]);
    }
}



/**
 * Check Functionality and Flags
 * OPCODE: 0x80-0x87 | ADD A, r8
 */
TEST_CASE( "ADD A, r8 - Flags and Functions", "[0x80-0x87]" ) {
    // Initiate ONLY in this Scope
    uint8_t val = 0x00;
    cpu.reset();    // Make sure to Reset CPU to Default
    

    // Check for Zero Flag
    cpu.ADD(&val);                          // 0x00 + 0x00 = 0x00
    REQUIRE(cpu.R[REGISTER::A] == 0x00);    // Check R[A] = 0x00
    REQUIRE(cpu.R[REGISTER::F] &  0x80);    // Check Zero Flag
    

    // Change Value of R[A]
    // 0x00 + 0x0F = 0x0F
    val = 0x0F;
    cpu.ADD(&val);
    REQUIRE(cpu.R[REGISTER::A] == 0x0F);    // Check R[A] = 0x0F


    // Check Overflow Flags
    cpu.ADD(&val);
    REQUIRE((cpu.R[REGISTER::F] & 0x20));   // Nibble Overflow

    val = 0xFE;
    cpu.ADD(&val);
    REQUIRE((cpu.R[REGISTER::F] & 0x10));   // Byte Overflow
}


/**
 * Check Functionality and Flags
 * OPCODE: 0x88-0x8F | ADC A, r8
 */
TEST_CASE( "ADC A, r8 - Flags and Functions", "[0x88-0x8F]" ) {
    // Initiate ONLY in this Scope
    uint8_t val = 0x00;
    cpu.reset();

    // Check for Zero Flag
    cpu.ADC(&val);                          // 0x00 + 0x00 = 0x00
    REQUIRE(cpu.R[REGISTER::A] == 0x00);    // Check R[A] = 0x00
    REQUIRE(cpu.R[REGISTER::F] &  0x80);    // Check Zero Flag

    // Check Addition is Working
    val = 0x0F;
    cpu.ADC(&val);
    REQUIRE(cpu.R[REGISTER::A] == 0x0F);    // Check R[A] = 0x0F

    // Check Overflow Flags
    cpu.ADC(&val);
    REQUIRE((cpu.R[REGISTER::F] & 0x20));   // Nibble Overflow

    val = 0xFE;
    cpu.ADC(&val); // R[A] = 0x1C
    REQUIRE((cpu.R[REGISTER::F] & 0x10));   // Byte Overflow (Sets Carry Flag)

    // Check that the Carry Flag IS being added on
    val = 0x01;
    cpu.ADC(&val); // R[A] = 0x1E
    REQUIRE(cpu.R[REGISTER::A] == 0x1E);
}
