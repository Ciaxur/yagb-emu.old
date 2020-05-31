#include "../include/CPU.h"

/**
 * Initialize the CPU
 *  - Assign the Shared Memory
 * 
 * @param mem - Shared Memory
 */
CPU::CPU(Memory *mem) {
    this->memory = mem;
    PC = 0x0000;
}


/**
 * Run one CPU Cycle
 */
void CPU::run() {
    // Get the Opcode at PC's Address
    uint8_t opcode = memory->getData(PC);

    // Two Potential Operands
    uint8_t op1, op2;


    // Parse Through, Executing Opcode
    switch (opcode & 0xF0) {
    case 0x00:
        switch (opcode & 0x0F) {
        case 0x00:      // 0x00 NOP (1Byte | 1Cycle)
            PC += 1;  // 1 Byte
            break;
        case 0x01:      // 0x01 LD BC, d16 (3Bytes | 3Cycles)
            // Obtain the Two Operands
            op1 = memory->getData(PC + 1);
            op2 = memory->getData(PC + 2);

            // Increment PC to next Operand
            PC += 3;
            break;
        case 0x02:      // 0x02 LD (BC), A (1Byte | 2Cycles)
            PC += 1;
            break;
        case 0x03:      // 0x03 INC BC (1Byte | 2Cycles)
            PC += 1;
            break;
        case 0x04:      // 0x04 INC B (1Byte | 1Cycles)
            PC += 1;
            break;
        case 0x05:      // 0x05 DEC B (1Byte | 1Cycles)
            PC += 1;
            break;
        case 0x06:      // 0x06 LD B, d8 (2Bytes | 2Cycles)
            op1 = memory->getData(PC + 1);
            PC += 2;
            break;
        case 0x07:      // 0x07 RLCA (1Bytes | 1Cycles)
            break;
        case 0x08:      // 0x08 LD (a16), SP (3Bytes | 1Cycles)
            op1 = memory->getData(PC + 1);
            op2 = memory->getData(PC + 2);
            PC += 3;
            break;
        case 0x09:      // 0x09 ADD HL, BC  (1Byte | 2Cycles)
            PC += 1;
            break;
        case 0x0A:      // 0x0A LD A, (BC) (1Byte | 2Cycles)
            PC += 1;
            break;
        case 0x0B:      // 0x0B DEC BC (1Byte | 2Cycles)
            PC += 1;
            break;
        case 0x0C:      // 0x0C INC C (1Byte | 1Cycles)
            PC += 1;
            break;
        case 0x0D:      // 0x0D DEC C (1Byte | 1Cycles)
            PC += 1;
            break;
        case 0x0E:      // 0x0E LD C, d8 (2Bytes | 2Cycles)
            op1 = memory->getData(PC + 1);
            PC += 2;
            break;
        case 0x0F:      // 0x0F RRCA (1Byte | 1Cycles)
            PC += 1;
            break;
        default: PC += 1;
        }
        break;


    case 0x10:
        switch (opcode & 0x0F) {
        case 0x00:      // 0x10 STOP (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x01:      // 0x11 LD DE, d16 (3Bytes | 3Cycles)
            op1 = memory->getData(PC + 1);
            op2 = memory->getData(PC + 2);
            PC += 3;
            break;
        case 0x02:      // 0x12 LD (DE), A (1Byte | 2Cycles)
            PC += 1;
            break;
        case 0x03:      // 0x13 INC DE (1Byte | 2Cycles)
            PC += 1;
            break;
        case 0x04:      // 0x14 INC D (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x05:      // 0x15 DEC D (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x06:      // 0x16 LD D, d8 (2Bytes | 2Cycles)
            op1 = memory->getData(PC + 1);
            PC += 2;
            break;
        case 0x07:      // 0x17 RLA (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x08:      // 0x18 JR r8 (2Bytes | 3Cycles)
            op1 = memory->getData(PC + 1);
            PC += 2;
            break;
        case 0x09:      // 0x19 ADD HL, DE (1Byte | 2Cycles)
            PC += 1;
            break;
        case 0x0A:      // 0x1A LD A, (DE) (1Byte | 2Cycles)
            PC += 1;
            break;
        case 0x0B:      // 0x1B DEC DE (1Byte | 2Cycles)
            PC += 1;
            break;
        case 0x0C:      // 0x1C INC E (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x0D:      // 0x1D DEC E (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x0E:      // 0x1E LD E, d8 (2Bytes | 2Cycles)
            op1 = memory->getData(PC + 1);
            PC += 2;
            break;
        case 0x0F:      // 0x1F RRA (1Byte | 1Cycle)
            PC += 1;
            break;
        default: PC += 1;
        }
        break;


    case 0x20:
        switch (opcode & 0x0F) {
        case 0x00:      // 0x20 JR NZ, r8 (2Bytes | 3/2Cycles)
            op1 = memory->getData(PC + 1);
            PC += 2;
            break;
        case 0x01:      // 0x21 LD HL, d16 (3Bytes | 3Cycles)
            op1 = memory->getData(PC + 1);
            op2 = memory->getData(PC + 2);
            PC += 3;
            break;
        case 0x02:      // 0x22 LD (HL+), A (1Byte | 2Cycles)
            PC += 1;
            break;
        case 0x03:      // 0x23 INC HL (1Byte | 2Cycles)
            PC += 1;
            break;
        case 0x04:      // 0x24 INC H (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x05:      // 0x25 DEC H (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x06:      // 0x26 LD H, d8 (2Bytes | 2Cycles)
            op1 = memory->getData(PC + 1);
            PC += 2;
            break;
        case 0x07:      // 0x27 DAA (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x08:      // 0x28 JR Z, r8 (2Bytes | 3/2Cycles)
            op1 = memory->getData(PC + 1);
            PC += 2;
            break;
        case 0x09:      // 0x29 ADD HL, HL (1Byte | 2Cycles)
            PC += 1;
            break;
        case 0x0A:      // 0x2A LD A, (HL+) (1Byte | 2Cycles)
            PC += 1;
            break;
        case 0x0B:      // 0x2B DEC HL (1Byte | 2Cycles)
            PC += 1;
            break;
        case 0x0C:      // 0x2C INC L (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x0D:      // 0x2D DEC L (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x0E:      // 0x2E LD L, d8 (2Bytes | 2Cycles)
            op1 = memory->getData(PC + 1);
            PC += 2;
            break;
        case 0x0F:      // 0x2F CPL (1Byte | 1Cycle)
            PC += 1;
            break;
        default: PC += 1;
        }
        break;


    case 0x30:
        switch (opcode & 0x0F) {
        case 0x00:      // 0x30 JR NC, r8 (2Bytes | 3/2Cycles)
            op1 = memory->getData(PC + 1);
            PC += 2;
            break;
        case 0x01:      // 0x31 LD SP, d16 (3Bytes | 3Cycles)
            op1 = memory->getData(PC + 1);
            op2 = memory->getData(PC + 2);
            PC += 3;
            break;
        case 0x02:      // 0x32 LD (HL-), A (1Byte | 2Cycles)
            PC += 1;
            break;
        case 0x03:      // 0x33 INC SP (1Byte | 2Cycle)
            PC += 1;
            break;
        case 0x04:      // 0x34 INC (HL) (1Byte | 3Cycles)
            PC += 1;
            break;
        case 0x05:      // 0x35 DEC (HL) (1Byte | 3Cycles)
            PC += 1;
            break;
        case 0x06:      // 0x36 LD (HL), d8 (2Bytes | 3Cycles)
            op1 = memory->getData(PC + 1);
            PC += 2;
            break;
        case 0x07:      // 0x37 SCF (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x08:      // 0x38 JR C, r8 (2Bytes | 3/2Cycles)
            op1 = memory->getData(PC + 1);
            PC += 2;
            break;
        case 0x09:      // 0x39 ADD HL, SP (1Byte | 2Cycles)
            PC += 1;
            break;
        case 0x0A:      // 0x3A LD A, (HL-) (1Byte | 2Cycles)
            PC += 1;
            break;
        case 0x0B:      // 0x3B DEC SP (1Byte | 2Cycles)
            PC += 1;
            break;
        case 0x0C:      // 0x3C INC A (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x0D:      // 0x3D DEC A (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x0E:      // 0x3E LD A, d8 (2Bytes | 2Cycles)
            op1 = memory->getData(PC + 1);
            PC += 2;
            break;
        case 0x0F:      // 0x3F CCF (1Byte | 1Cycle)
            PC += 1;
            break;
        default: PC += 1;
        }
        break;


    case 0x40:
        switch (opcode & 0x0F) {
        case 0x00:      // 0x40 LD B, B (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x01:      // 0x41 LD B, C (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x02:      // 0x42 LD B, D (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x03:      // 0x43 LD B, E (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x04:      // 0x44 LD B, H (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x05:      // 0x45 LD B, L (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x06:      // 0x46 LD B, (HL) (1Byte | 2Cycles)
            PC += 1;
            break;
        case 0x07:      // 0x47 LD B, A (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x08:      // 0x48 LD C, B (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x09:      // 0x49 LD C, C (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x0A:      // 0x4A LD C, D (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x0B:      // 0x4B LD C, E (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x0C:      // 0x4C LD C, H (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x0D:      // 0x4D LD C, L (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x0E:      // 0x4E LD C, (HL) (1Byte | 2Cycles)
            PC +=1 ;
            break;
        case 0x0F:      // 0x4F LD C, A (1Byte | 1Cycle)
            PC += 1;
            break;
        default: PC += 1;
        }
        break;


    case 0x50:
        switch (opcode & 0x0F) {
        case 0x00:      // 0x50 LD D, B (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x01:      // 0x51 LD D, C (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x02:      // 0x52 LD D, D (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x03:      // 0x53 LD D, E (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x04:      // 0x54 LD D, H (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x05:      // 0x55 LD D, L (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x06:      // 0x56 LD D, (HL) (1Byte | 2Cycles)
            PC += 1;
            break;
        case 0x07:      // 0x57 LD D, A (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x08:      // 0x58 LD E, B (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x09:      // 0x59 LD E, C (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x0A:      // 0x5A LD E, D (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x0B:      // 0x5B LD E, E (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x0C:      // 0x5C LD E, H (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x0D:      // 0x5D LD E, L (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x0E:      // 0x5E LD C, (HL) (1Byte | 2Cycles)
            PC += 1;
            break;
        case 0x0F:      // 0x5F LD E, A (1Byte | 1Cycle)
            PC += 1;
            break;
        default: PC += 1;
        }
        break;


    case 0x60:
        switch (opcode & 0x0F) {
        case 0x00:      // 0x60 LD H, B (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x01:      // 0x61 LD H, C (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x02:      // 0x62 LD H, D (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x03:      // 0x63 LD H, E (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x04:      // 0x64 LD H, H (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x05:      // 0x65 LD H, L (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x06:      // 0x66 LD H, (HL) (1Byte | 2Cycles)
            PC += 1;
            break;
        case 0x07:      // 0x67 LD H, A (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x08:      // 0x68 LD L, B (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x09:      // 0x69 LD L, C (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x0A:      // 0x6A LD L, D (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x0B:      // 0x6B LD L, E (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x0C:      // 0x6C LD L, H (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x0D:      // 0x6D LD L, L (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x0E:      // 0x6E LD L, (HL) (1Byte | 2Cycles)
            PC += 1;
            break;
        case 0x0F:      // 0x6F LD L, A (1Byte | 1Cycle)
            PC += 1;
            break;
        default: PC += 1;
        }
        break;


    case 0x70:
        switch (opcode & 0x0F) {
        case 0x00:      // 0x70 LD (HL), B (1Byte | 2Cycles)
            PC += 1;
            break;
        case 0x01:      // 0x71 LD (HL), C (1Byte | 2Cycles)
            PC += 1;
            break;
        case 0x02:      // 0x72 LD (HL), D (1Byte | 2Cycles)
            PC += 1;
            break;
        case 0x03:      // 0x73 LD (HL), E (1Byte | 2Cycles)
            PC += 1;
            break;
        case 0x04:      // 0x70 LD (HL), H (1Byte | 2Cycles)
            PC += 1;
            break;
        case 0x05:      // 0x71 LD (HL), L (1Byte | 2Cycles)
            PC += 1;
            break;
        case 0x06:      // 0x76 HALT (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x07:      // 0x77 LD (HL), A (1Byte | 2Cycles)
            PC += 1;
            break;
        case 0x08:      // 0x78 LD A, B (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x09:      // 0x79 LD A, C (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x0A:      // 0x7A LD A, D (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x0B:      // 0x7B LD A, E (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x0C:      // 0x7C LD A, H (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x0D:      // 0x7D LD A, L (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x0E:      // 0x7E LD A, (HL) (1Byte | 2Cycles)
            PC += 1;
            break;
        case 0x0F:      // 0x7F LD A, A (1Byte | 1Cycle)
            PC += 1;
            break;
        default: PC += 1;
        }
        break;


    case 0x80:
        switch (opcode & 0x0F) {
        case 0x00:      // 0x80 ADD B (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x01:      // 0x81 ADD C (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x02:      // 0x82 ADD D (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x03:      // 0x83 ADD E (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x04:      // 0x84 ADD H (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x05:      // 0x85 ADD L (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x06:      // 0x86 ADD (HL) (1Byte | 2Cycle)
            PC += 1;
            break;
        case 0x07:      // 0x87 ADD A (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x08:      // 0x88 ADC B (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x09:      // 0x89 ADC C (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x0A:      // 0x8A ADC D (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x0B:      // 0x8B ADC E (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x0C:      // 0x8C ADC H (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x0D:      // 0x8D ADC L (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x0E:      // 0x8E ADC (HL) (1Byte | 2Cycle)
            PC += 1;
            break;
        case 0x0F:      // 0x8F ADC A (1Byte | 1Cycle)
            PC += 1;
            break;
        default: PC += 1;
        }
        break;


    case 0x90:
        switch (opcode & 0x0F) {
        case 0x00:      // 0x90 SUB B (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x01:      // 0x91 SUB C (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x02:      // 0x92 SUB D (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x03:      // 0x93 SUB E (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x04:      // 0x94 SUB H (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x05:      // 0x95 SUB L (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x06:      // 0x96 SUB (HL) (1Byte | 2Cycle)
            PC += 1;
            break;
        case 0x07:      // 0x97 SUB A (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x08:      // 0x98 SBC B (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x09:      // 0x99 SBC C (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x0A:      // 0x9A SBC D (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x0B:      // 0x9B SBC E (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x0C:      // 0x9C SBC H (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x0D:      // 0x9D SBC L (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x0E:      // 0x9E SBC (HL) (1Byte | 2Cycle)
            PC += 1;
            break;
        case 0x0F:      // 0x9F SBC A (1Byte | 1Cycle)
            PC += 1;
            break;
        default: PC += 1;
        }
        break;


    case 0xA0:
        switch (opcode & 0x0F) {
        case 0x00:      // 0xA0 AND B (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x01:      // 0xA1 AND C (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x02:      // 0xA2 AND D (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x03:      // 0xA3 AND E (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x04:      // 0xA4 AND H (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x05:      // 0xA5 AND L (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x06:      // 0xA6 AND (HL) (1Byte | 2Cycle)
            PC += 1;
            break;
        case 0x07:      // 0xA7 AND A (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x08:      // 0xA8 XOR B (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x09:      // 0xA9 XOR C (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x0A:      // 0xAA XOR D (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x0B:      // 0xAB XOR E (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x0C:      // 0xAC XOR H (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x0D:      // 0xAD XOR L (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x0E:      // 0xAE XOR (HL) (1Byte | 2Cycle)
            PC += 1;
            break;
        case 0x0F:      // 0xAF XOR A (1Byte | 1Cycle)
            PC += 1;
            break;
        default: PC += 1;
        }
        break;


    case 0xB0:
        switch (opcode & 0x0F) {
        case 0x00:      // 0xB0 OR B (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x01:      // 0xB1 OR C (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x02:      // 0xB2 OR D (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x03:      // 0xB3 OR E (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x04:      // 0xB4 OR H (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x05:      // 0xB5 OR L (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x06:      // 0xB6 OR (HL) (1Byte | 2Cycle)
            PC += 1;
            break;
        case 0x07:      // 0xB7 OR A (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x08:      // 0xB8 CP B (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x09:      // 0xB9 CP C (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x0A:      // 0xBA CP D (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x0B:      // 0xBB CP E (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x0C:      // 0xBC CP H (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x0D:      // 0xBD CP L (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x0E:      // 0xBE CP (HL) (1Byte | 2Cycle)
            PC += 1;
            break;
        case 0x0F:      // 0xBF CP A (1Byte | 1Cycle)
            PC += 1;
            break;
        default: PC += 1;
        }
        break;


    case 0xC0:
        switch (opcode & 0x0F) {
        case 0x00:      // 0xC0 RET NZ (1Byte | 5/2Cycle)
            PC += 1;
            break;
        case 0x01:      // 0xC1 POP BC (1Byte | 3Cycle)
            PC += 1;
            break;
        case 0x02:      // 0xC2 JP NZ, a16 (3Byte | 4/3Cycle)
            op1 = memory->getData(PC + 1);
            op2 = memory->getData(PC + 2);
            PC += 3;
            break;
        case 0x03:      // 0xC3 JP a16 (3Byte | 4Cycle)
            op1 = memory->getData(PC + 1);
            op2 = memory->getData(PC + 2);
            PC += 3;
            break;
        case 0x04:      // 0xC4 CALL NZ, a16 (3Byte | 6/3Cycle)
            op1 = memory->getData(PC + 1);
            op2 = memory->getData(PC + 2);
            PC += 3;
            break;
        case 0x05:      // 0xC5 PUSH BC (1Byte | 4Cycle)
            PC += 1;
            break;
        case 0x06:      // 0xC6 ADD A, d8 (2Byte | 2Cycle)
            op1 = memory->getData(PC + 1);
            PC += 2;
            break;
        case 0x07:      // 0xC7 RST 00H (1Byte | 4Cycle)
            PC += 1;
            break;
        case 0x08:      // 0xC8 RET Z (1Byte | 5/2Cycle)
            PC += 1;
            break;
        case 0x09:      // 0xC9 RET (1Byte | 4Cycle)
            PC += 1;
            break;
        case 0x0A:      // 0xCA JP Z, a16 (3Byte | 4/3Cycle)
            op1 = memory->getData(PC + 1);
            op2 = memory->getData(PC + 2);
            PC += 3;
            break;
        case 0x0B:      // 0xCB PREFIX (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x0C:      // 0xCC CALL Z, a16 (3Byte | 6/3Cycle)
            op1 = memory->getData(PC + 1);
            op2 = memory->getData(PC + 2);
            PC += 3;
            break;
        case 0x0D:      // 0xCD CALL a16 (3Byte | 6Cycle)
            op1 = memory->getData(PC + 1);
            op2 = memory->getData(PC + 2);
            PC += 3;
            break;
        case 0x0E:      // 0xCE ADC A, d8 (2Byte | 2Cycle)
            op1 = memory->getData(PC + 1);
            PC += 2;
            break;
        case 0x0F:      // 0xCF RST 08H (1Byte | 4Cycle)
            PC += 1;
            break;
        default: PC += 1;
        }
        break;


    case 0xD0:
        switch (opcode & 0x0F) {
        case 0x00:      // 0xD0 RET NC (1Byte | 5/2Cycle)
            PC += 1;
            break;
        case 0x01:      // 0xD1 POP DE (1Byte | 3Cycle)
            PC += 1;
            break;
        case 0x02:      // 0xD2 JP NC, a16 (3Byte | 4/3Cycle)
            op1 = memory->getData(PC + 1);
            op2 = memory->getData(PC + 2);
            PC += 3;
            break;
        case 0x04:      // 0xD4 CALL NC, a16 (3Byte | 6/3Cycle)
            op1 = memory->getData(PC + 1);
            op2 = memory->getData(PC + 2);
            PC += 3;
            break;
        case 0x05:      // 0xD5 PUSH DE (1Byte | 4Cycle)
            PC += 1;
            break;
        case 0x06:      // 0xD6 SUB d8 (2Byte | 2Cycle)
            op1 = memory->getData(PC + 1);
            PC += 2;
            break;
        case 0x07:      // 0xD7 RST 10H (1Byte | 4Cycle)
            PC += 1;
            break;
        case 0x08:      // 0xD8 RET C (1Byte | 4Cycle)
            PC += 1;
            break;
        case 0x09:      // 0xD9 RETI (1Byte | 4Cycle)
            PC += 1;
            break;
        case 0x0A:      // 0xDA JP C, a16 (3Byte | 4/3Cycle)
            op1 = memory->getData(PC + 1);
            op2 = memory->getData(PC + 2);
            PC += 3;
            break;
        case 0x0C:      // 0xDC CALL, a16 (3Byte | 3/6Cycle)
            op1 = memory->getData(PC + 1);
            op2 = memory->getData(PC + 2);
            PC += 3;
            break;
        case 0x0E:      // 0xDE SBC A, d8 (2Byte | 2Cycle)
            op1 = memory->getData(PC + 1);
            PC += 2;
            break;
        case 0x0F:      // 0xDF RST 18H (1Byte | 4Cycle)
            PC += 1;
            break;
        default: PC += 1;
        }
        break;


    case 0xE0:
        switch (opcode & 0x0F) {
        case 0x00:      // 0xE0 LDH (a8), A (2Byte | 3Cycles)
            op1 = memory->getData(PC + 1);
            PC += 2;
            break;
        case 0x01:      // 0xE1 POP HL (1Byte | 3Cycles)
            PC += 1;
            break;
        case 0x02:      // 0xE2 LD (C), A (1Byte | 2Cycles)
            PC += 1;
            break;
        case 0x05:      // 0xE5 PUSH HL (1Byte | 4Cycles)
            PC += 1;
            break;
        case 0x06:      // 0xE6 AND d8 (2Bytes | 2Cycles)
            op1 = memory->getData(PC + 1);
            PC += 2;
            break;
        case 0x07:      // 0xE7 RST 20H (1Byte | 4Cycle)
            PC += 1;
            break;
        case 0x08:      // 0xE8 ADD SP, r8 (2Bytes | 4Cycles)
            op1 = memory->getData(PC + 1);
            PC += 2;
            break;
        case 0x09:      // 0xE9 JP HL (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x0A:      // 0xEA LD (a16), A (3Bytes | 4Cycles)
            op1 = memory->getData(PC + 1);
            op2 = memory->getData(PC + 2);
            PC += 3;
            break;
        case 0x0E:      // 0xEE XOR d8 (2Bytes | 2Cycles)
            op1 = memory->getData(PC + 1);
            PC += 2;
            break;
        case 0x0F:      // 0xEF RST 28H (1Byte | 4Cycles)
            PC += 1;
            break;
        default: PC += 1;
        }
        break;


    case 0xF0:
        switch (opcode & 0x0F) {
        case 0x00:      // 0xF0 LDH A, (a8) (2Bytes | 3Cycles)
            op1 = memory->getData(PC + 1);
            PC += 2;
            break;
        case 0x01:      // 0xF1 POP AF (1Byte | 3Cycles)
            PC += 1;
            break;
        case 0x02:      // 0xF2 LD A, (C) (1Byte | 2Cycles)
            PC += 1;
            break;
        case 0x03:      // 0xF3 DI (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x05:      // 0xF5 PUSH AF (1Byte | 4Cycles)
            PC += 1;
            break;
        case 0x06:      // 0xF6 RST 30H (1Byte | 4Cycles)
            PC += 1;
            break;
        case 0x07:
            break;
        case 0x08:      // 0xF8 LD, SP + r8 (2Bytes | 3Cycles)
            op1 = memory->getData(PC + 1);
            PC += 2;
            break;
        case 0x09:      // 0xF9 LD SP, HL (1Byte | 2Cycles)
            PC += 1;
            break;
        case 0x0A:      // 0xFA LD A, (a16) (3Bytes | 4Cycles)
            op1 = memory->getData(PC + 1);
            op2 = memory->getData(PC + 2);
            PC += 3;
            break;
        case 0x0B:      // 0xFB EI (1Byte | 1Cycle)
            PC += 1;
            break;
        case 0x0E:      // 0xFE CP d8 (2Bytes | 2Cycles)
            op1 = memory->getData(PC + 1);
            // (CP d8 assumes CP A, d8)
            PC += 2;
            break;
        case 0x0F:      // 0xFF RST 38H (1Bytes | 4Cycles)
            PC += 1;
            break;
        default: PC += 1;
        }
        break;

    default: PC += 1;
    }
}