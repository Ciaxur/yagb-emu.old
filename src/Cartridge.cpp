#include "../include/Cartridge.h"

/**
 * Initiate the Cartridge
 * 
 * @param path - File Path to ROM
 */
Cartridge::Cartridge(const char* path): filePath(path) {}


/**
 * Outputs a HexDump of Loaded ROM to
 *  given output stream
 * 
 * @param out - Output Stream to write to
 */
void Cartridge::hexDump(std::ostream &out, bool printLine) {
    u_char buffer[1000];
    int addr = 0;
    int n;
    int lineno = 0;
    std::ifstream infile;
    infile.open(filePath);

    // Check if file exists
    if (!infile) {
        std::cout << "File not found" << std::endl;
        return;
    }

    while (true) {
        infile.read((char *)buffer, 16);
        // Return buffer size up to 16
        n = infile.gcount();
        if (n <= 0) {
            break;
        }
        // Offset 16 bytes per line
        addr += 16;

        // Print Line Number (Uppercase ALL)
        if(printLine)
            out << std::hex << std::uppercase << std::setw(4) << std::setfill('0') << lineno << '\t';
        else
            out << std::uppercase;
        
        // Print line of n bytes
        for (int i = 0; i < 16; i++) {
            if (i + 1 <= n) {
                out << std::hex << std::setw(2) << std::setfill('0') << (int)buffer[i];
            }
            // Space each byte
            out << " ";
        }
        // New line after n bytes
        out << "\n";
        lineno += 16;
        
        // Break if end of file
        if (infile.eof()) {
            break;
        }
    }
}

/**
 * Disassembles given ROM Instructions, outputting
 *  to given Output Stream
 */
void Cartridge::disassemble(std::ostream &out) {
    std::stringstream ss;
    hexDump(ss, false);     // Hexdump without Line Numbers
    uint16_t data;
    uint16_t nextByte;
    int lineno = 0;

    while (ss >> data) {
        // Keep Track of Current Working Intruction
        Instruction *instr_p = new Instruction();
        char instr_str[64]{};           // Instruction String Buffer

        // Store the Opcode
        instr_p->opcode = data;


        // Parse Through
        // TODO: Store Execution Functions
        switch (data & 0xF0) {
        case 0x00:
            switch (data & 0x0F) {
            case 0x00:      // 0x00 NOP (1Byte | 1Cycle)
                // Apply Instruction String
                sprintf(instr_str, "0x%04X \t NOP", lineno);
                lineno += 1;  // 1 Byte

                break;
            case 0x01:      // 0x01 LD BC, d16 (3Bytes | 3Cycles)
                // Obtain the Two Operands
                ss >> nextByte;
                instr_p->op1 = nextByte;
                ss >> nextByte;
                instr_p->op2 = nextByte;

                sprintf(instr_str, "0x%04X \t LD BC, 0x%02X%02X", lineno, instr_p->op1, instr_p->op2);
                lineno += 3;
                break;
            case 0x02:      // 0x02 LD (BC), A (1Byte | 2Cycles)
                sprintf(instr_str, "0x%04X \t LD (BC), A", lineno);
                lineno += 1;
                break;
            case 0x03:      // 0x03 INC BC (1Byte | 2Cycles)
                sprintf(instr_str, "0x%04X \t INC BC", lineno);
                lineno += 1;
                break;
            case 0x04:      // 0x04 INC B (1Byte | 1Cycles)
                sprintf(instr_str, "0x%04X \t INC B", lineno);
                lineno += 1;
                break;
            case 0x05:      // 0x05 DEC B (1Byte | 1Cycles)
                sprintf(instr_str, "0x%04X \t DEC B", lineno);
                lineno += 1;
                break;
            case 0x06:      // 0x06 LD B, d8 (2Bytes | 2Cycles)
                ss >> nextByte;
                instr_p->op1 = nextByte;

                sprintf(instr_str, "0x%04X \t LD B, 0x%02X", lineno, instr_p->op1);
                lineno += 2;
                break;
            case 0x07:      // 0x07 RLCA (1Bytes | 1Cycles)
                sprintf(instr_str, "0x%04X \t RLCA", lineno);
                lineno += 1;
                break;
            case 0x08:      // 0x08 LD (a16), SP (3Bytes | 1Cycles)
                ss >> nextByte;
                instr_p->op1 = nextByte;
                ss >> nextByte;
                instr_p->op2 = nextByte;

                sprintf(instr_str, "0x%04X \t LD (0xFF00+0x%02X%02X), SP", lineno, instr_p->op1, instr_p->op2);
                lineno += 3;
                break;
            case 0x09:      // 0x09 ADD HL, BC  (1Byte | 2Cycles)
                sprintf(instr_str, "0x%04X \t ADD HL, BC", lineno);
                lineno += 1;
                break;
            case 0x0A:      // 0x0A LD A, (BC) (1Byte | 2Cycles)
                sprintf(instr_str, "0x%04X \t LD A, (BC)", lineno);
                lineno += 1;
                break;
            case 0x0B:      // 0x0B DEC BC (1Byte | 2Cycles)
                sprintf(instr_str, "0x%04X \t DEC BC", lineno);
                lineno += 1;
                break;
            case 0x0C:      // 0x0C INC C (1Byte | 1Cycles)
                sprintf(instr_str, "0x%04X \t INC C", lineno);
                lineno += 1;
                break;
            case 0x0D:      // 0x0D DEC C (1Byte | 1Cycles)
                sprintf(instr_str, "0x%04X \t DEC C", lineno);
                lineno += 1;
                break;
            case 0x0E:      // 0x0E LD C, d8 (2Bytes | 2Cycles)
                ss >> nextByte;
                instr_p->op1 = nextByte;

                sprintf(instr_str, "0x%04X \t LD C, 0x%02X", lineno, instr_p->op1);
                lineno += 2;
                break;
            case 0x0F:      // 0x0F RRCA (1Byte | 1Cycles)
                sprintf(instr_str, "0x%04X \t RRCA", lineno);
                lineno += 1;
                break;
            default: lineno += 1;
            }
            break;


        case 0x10:
            switch (data & 0x0F) {
            case 0x00:      // 0x10 STOP (1Byte | 1Cycle)
                // Store Opcode
                instr_p->opcode = data;

                // Apply Instruction String
                sprintf(instr_str, "0x%04X \t STOP", lineno);
                lineno += 1;
                break;
            case 0x01:      // 0x11 LD DE, d16 (3Bytes | 3Cycles)
                ss >> nextByte;
                instr_p->op1 = nextByte;
                ss >> nextByte;
                instr_p->op2 = nextByte;

                sprintf(instr_str, "0x%04X \t LD DE, 0x%02X%02X", lineno, instr_p->op1, instr_p->op2);
                lineno += 3;
                break;
            case 0x02:      // 0x12 LD (DE), A (1Byte | 2Cycles)
                sprintf(instr_str, "0x%04X \t LD (DE), A", lineno);
                lineno += 1;
                break;
            case 0x03:      // 0x13 INC DE (1Byte | 2Cycles)
                sprintf(instr_str, "0x%04X \t INC DE", lineno);
                lineno += 1;
                break;
            case 0x04:      // 0x14 INC D (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t INC D", lineno);
                lineno += 1;
                break;
            case 0x05:      // 0x15 DEC D (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t DEC D", lineno);
                lineno += 1;
                break;
            case 0x06:      // 0x16 LD D, d8 (2Bytes | 2Cycles)
                ss >> nextByte;
                instr_p->op1 = nextByte;

                sprintf(instr_str, "0x%04X \t LD D, 0x%02X", lineno, instr_p->op1);
                lineno += 2;
                break;
            case 0x07:      // 0x17 RLA (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t RLA", lineno);
                lineno += 1;
                break;
            case 0x08:      // 0x18 JR r8 (2Bytes | 3Cycles)
                ss >> nextByte;
                instr_p->op1 = nextByte & 0xF;

                sprintf(instr_str, "0x%04X \t JR R%01X", lineno, instr_p->op1);
                lineno += 2;
                break;
            case 0x09:      // 0x19 ADD HL, DE (1Byte | 2Cycles)
                sprintf(instr_str, "0x%04X \t ADD HL, DE", lineno);
                lineno += 1;
                break;
            case 0x0A:      // 0x1A LD A, (DE) (1Byte | 2Cycles)
                sprintf(instr_str, "0x%04X \t LD A, (DE)", lineno);
                lineno += 1;
                break;
            case 0x0B:      // 0x1B DEC DE (1Byte | 2Cycles)
                sprintf(instr_str, "0x%04X \t DEC DE", lineno);
                lineno += 1;
                break;
            case 0x0C:      // 0x1C INC E (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t INC E", lineno);
                lineno += 1;
                break;
            case 0x0D:      // 0x1D DEC E (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t DEC E", lineno);
                lineno += 1;
                break;
            case 0x0E:      // 0x1E LD E, d8 (2Bytes | 2Cycles)
                ss >> nextByte;
                instr_p->op1 = nextByte;

                sprintf(instr_str, "0x%04X \t LD E, 0x%02X", lineno, instr_p->op1);
                lineno += 2;
                break;
            case 0x0F:      // 0x1F RRA (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t RRA", lineno);
                lineno += 1;
                break;
            default: lineno += 1;
            }
            break;


        case 0x20:
            switch (data & 0x0F) {
            case 0x00:      // 0x20 JR NZ, r8 (2Bytes | 3/2Cycles)
                ss >> nextByte;
                instr_p->op1 = nextByte & 0xF;

                sprintf(instr_str, "0x%04X \t JR NZ, R%01X", lineno, instr_p->op1);
                lineno += 2;
                break;
            case 0x01:      // 0x21 LD HL, d16 (3Bytes | 3Cycles)
                ss >> nextByte;
                instr_p->op1 = nextByte;
                ss >> nextByte;
                instr_p->op2 = nextByte;

                sprintf(instr_str, "0x%04X \t LD HL, 0x%02X%02X", lineno, instr_p->op1, instr_p->op2);
                lineno += 3;
                break;
            case 0x02:      // 0x22 LD (HL+), A (1Byte | 2Cycles)
                sprintf(instr_str, "0x%04X \t LD (HL+), A", lineno);
                lineno += 1;
                break;
            case 0x03:      // 0x23 INC HL (1Byte | 2Cycles)
                sprintf(instr_str, "0x%04X \t INC HL", lineno);
                lineno += 1;
                break;
            case 0x04:      // 0x24 INC H (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t INC H", lineno);
                lineno += 1;
                break;
            case 0x05:      // 0x25 DEC H (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t DEC H", lineno);
                lineno += 1;
                break;
            case 0x06:      // 0x26 LD H, d8 (2Bytes | 2Cycles)
                ss >> nextByte;
                instr_p->op1 = nextByte;

                sprintf(instr_str, "0x%04X \t LD H, 0x%02X", lineno, instr_p->op1);
                lineno += 2;
                break;
            case 0x07:      // 0x27 DAA (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t DAA", lineno);
                lineno += 1;
                break;
            case 0x08:      // 0x28 JR Z, r8 (2Bytes | 3/2Cycles)
                ss >> nextByte;
                instr_p->op1 = nextByte & 0xF;

                sprintf(instr_str, "0x%04X \t JR Z, R%01X", lineno, instr_p->op1);
                lineno += 2;
                break;
            case 0x09:      // 0x29 ADD HL, HL (1Byte | 2Cycles)
                sprintf(instr_str, "0x%04X \t ADD HL, HL", lineno);
                lineno += 1;
                break;
            case 0x0A:      // 0x2A LD A, (HL+) (1Byte | 2Cycles)
                sprintf(instr_str, "0x%04X \t LD A, (HL+)", lineno);
                lineno += 1;
                break;
            case 0x0B:      // 0x2B DEC HL (1Byte | 2Cycles)
                sprintf(instr_str, "0x%04X \t DEC HL", lineno);
                lineno += 1;
                break;
            case 0x0C:      // 0x2C INC L (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t INC L", lineno);
                lineno += 1;
                break;
            case 0x0D:      // 0x2D DEC L (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t DEC L", lineno);
                lineno += 1;
                break;
            case 0x0E:      // 0x2E LD L, d8 (2Bytes | 2Cycles)
                ss >> nextByte;
                instr_p->op1 = nextByte;

                sprintf(instr_str, "0x%04X \t LD L, 0x%02X", lineno, instr_p->op1);
                lineno += 2;
                break;
            case 0x0F:      // 0x2F CPL (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t CPL", lineno);
                lineno += 1;
                break;
            default: lineno += 1;
            }
            break;


        case 0x30:
            switch (data & 0x0F) {
            case 0x00:      // 0x30 JR NC, r8 (2Bytes | 3/2Cycles)
                ss >> nextByte;
                instr_p->op1 = nextByte & 0xF;

                sprintf(instr_str, "0x%04X \t JR NC, R%01X", lineno, instr_p->op1);
                lineno += 2;
                break;
            case 0x01:      // 0x31 LD SP, d16 (3Bytes | 3Cycles)
                ss >> nextByte;
                instr_p->op1 = nextByte;
                ss >> nextByte;
                instr_p->op2 = nextByte;

                sprintf(instr_str, "0x%04X \t LD SP, 0x%02X%02X", lineno, instr_p->op1, instr_p->op2);
                lineno += 3;
                break;
            case 0x02:      // 0x32 LD (HL-), A (1Byte | 2Cycles)
                sprintf(instr_str, "0x%04X \t LD (HL-), A", lineno);
                lineno += 1;
                break;
            case 0x03:      // 0x33 INC SP (1Byte | 2Cycle)
                sprintf(instr_str, "0x%04X \t INC SP", lineno);
                lineno += 1;
                break;
            case 0x04:      // 0x34 INC (HL) (1Byte | 3Cycles)
                sprintf(instr_str, "0x%04X \t INC (HL)", lineno);
                lineno += 1;
                break;
            case 0x05:      // 0x35 DEC (HL) (1Byte | 3Cycles)
                sprintf(instr_str, "0x%04X \t DEC (HL)", lineno);
                lineno += 1;
                break;
            case 0x06:      // 0x36 LD (HL), d8 (2Bytes | 3Cycles)
                ss >> nextByte;
                instr_p->op1 = nextByte;

                sprintf(instr_str, "0x%04X \t LD (HL), 0x%02X", lineno, instr_p->op1);
                lineno += 2;
                break;
            case 0x07:      // 0x37 SCF (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t SCF", lineno);
                lineno += 1;
                break;
            case 0x08:      // 0x38 JR C, r8 (2Bytes | 3/2Cycles)
                ss >> nextByte;
                instr_p->op1 = nextByte & 0xF;

                sprintf(instr_str, "0x%04X \t JR C, R%01X", lineno, instr_p->op1);
                lineno += 2;
                break;
            case 0x09:      // 0x39 ADD HL, SP (1Byte | 2Cycles)
                sprintf(instr_str, "0x%04X \t ADD HL, SP", lineno);
                lineno += 1;
                break;
            case 0x0A:      // 0x3A LD A, (HL-) (1Byte | 2Cycles)
                sprintf(instr_str, "0x%04X \t LD A, (HL-)", lineno);
                lineno += 1;
                break;
            case 0x0B:      // 0x3B DEC SP (1Byte | 2Cycles)
                sprintf(instr_str, "0x%04X \t DEC SP", lineno);
                lineno += 1;
                break;
            case 0x0C:      // 0x3C INC A (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t INC A", lineno);
                lineno += 1;
                break;
            case 0x0D:      // 0x3D DEC A (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t DEC A", lineno);
                lineno += 1;
                break;
            case 0x0E:      // 0x3E LD A, d8 (2Bytes | 2Cycles)
                ss >> nextByte;
                instr_p->op1 = nextByte;

                sprintf(instr_str, "0x%04X \t LD A, 0x%02X", lineno, instr_p->op1);
                lineno += 2;
                break;
            case 0x0F:      // 0x3F CCF (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t CCF", lineno);
                lineno += 1;
                break;
            default: lineno += 1;
            }
            break;


        case 0x40:
            switch (data & 0x0F) {
            case 0x00:      // 0x40 LD B, B (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t LD B, B", lineno);
                lineno += 1;
                break;
            case 0x01:      // 0x41 LD B, C (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t LD B, C", lineno);
                lineno += 1;
                break;
            case 0x02:      // 0x42 LD B, D (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t LD B, D", lineno);
                lineno += 1;
                break;
            case 0x03:      // 0x43 LD B, E (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t LD B, E", lineno);
                lineno += 1;
                break;
            case 0x04:      // 0x44 LD B, H (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t LD B, H", lineno);
                lineno += 1;
                break;
            case 0x05:      // 0x45 LD B, L (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t LD B, L", lineno);
                lineno += 1;
                break;
            case 0x06:      // 0x46 LD B, (HL) (1Byte | 2Cycles)
                sprintf(instr_str, "0x%04X \t LD B, (HL)", lineno);
                lineno += 1;
                break;
            case 0x07:      // 0x47 LD B, A (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t LD B, A", lineno);
                lineno += 1;
                break;
            case 0x08:      // 0x48 LD C, B (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t LD C, B", lineno);
                lineno += 1;
                break;
            case 0x09:      // 0x49 LD C, C (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t LD C, C", lineno);
                lineno += 1;
                break;
            case 0x0A:      // 0x4A LD C, D (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t LD C, D", lineno);
                lineno += 1;
                break;
            case 0x0B:      // 0x4B LD C, E (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t LD C, E", lineno);
                lineno += 1;
                break;
            case 0x0C:      // 0x4C LD C, H (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t LD C, H", lineno);
                lineno += 1;
                break;
            case 0x0D:      // 0x4D LD C, L (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t LD C, L", lineno);
                lineno += 1;
                break;
            case 0x0E:      // 0x4E LD C, (HL) (1Byte | 2Cycles)
                sprintf(instr_str, "0x%04X \t LD C, (HL)", lineno);
                lineno +=1 ;
                break;
            case 0x0F:      // 0x4F LD C, A (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t LD C, A", lineno);
                lineno += 1;
                break;
            default: lineno += 1;
            }
            break;


        case 0x50:
            switch (data & 0x0F) {
            case 0x00:      // 0x50 LD D, B (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t LD D, B", lineno);
                lineno += 1;
                break;
            case 0x01:      // 0x51 LD D, C (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t LD D, C", lineno);
                lineno += 1;
                break;
            case 0x02:      // 0x52 LD D, D (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t LD D, D", lineno);
                lineno += 1;
                break;
            case 0x03:      // 0x53 LD D, E (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t LD D, E", lineno);
                lineno += 1;
                break;
            case 0x04:      // 0x54 LD D, H (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t LD D, H", lineno);
                lineno += 1;
                break;
            case 0x05:      // 0x55 LD D, L (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t LD D, L", lineno);
                lineno += 1;
                break;
            case 0x06:      // 0x56 LD D, (HL) (1Byte | 2Cycles)
                sprintf(instr_str, "0x%04X \t LD D, (HL)", lineno);
                lineno += 1;
                break;
            case 0x07:      // 0x57 LD D, A (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t LD D, A", lineno);
                lineno += 1;
                break;
            case 0x08:      // 0x58 LD E, B (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t LD E, B", lineno);
                lineno += 1;
                break;
            case 0x09:      // 0x59 LD E, C (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t LD E, C", lineno);
                lineno += 1;
                break;
            case 0x0A:      // 0x5A LD E, D (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t LD E, D", lineno);
                lineno += 1;
                break;
            case 0x0B:      // 0x5B LD E, E (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t LD E, E", lineno);
                lineno += 1;
                break;
            case 0x0C:      // 0x5C LD E, H (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t LD E, H", lineno);
                lineno += 1;
                break;
            case 0x0D:      // 0x5D LD E, L (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t LD E, L", lineno);
                lineno += 1;
                break;
            case 0x0E:      // 0x5E LD C, (HL) (1Byte | 2Cycles)
                sprintf(instr_str, "0x%04X \t LD E, (HL)", lineno);
                lineno += 1;
                break;
            case 0x0F:      // 0x5F LD E, A (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t LD E, A", lineno);
                lineno += 1;
                break;
            default: lineno += 1;
            }
            break;


        case 0x60:
            switch (data & 0x0F) {
            case 0x00:      // 0x60 LD H, B (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t LD H, B", lineno);
                lineno += 1;
                break;
            case 0x01:      // 0x61 LD H, C (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t LD H, C", lineno);
                lineno += 1;
                break;
            case 0x02:      // 0x62 LD H, D (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t LD H, D", lineno);
                lineno += 1;
                break;
            case 0x03:      // 0x63 LD H, E (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t LD H, E", lineno);
                lineno += 1;
                break;
            case 0x04:      // 0x64 LD H, H (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t LD H, H", lineno);
                lineno += 1;
                break;
            case 0x05:      // 0x65 LD H, L (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t LD H, L", lineno);
                lineno += 1;
                break;
            case 0x06:      // 0x66 LD H, (HL) (1Byte | 2Cycles)
                sprintf(instr_str, "0x%04X \t LD H, (HL)", lineno);
                lineno += 1;
                break;
            case 0x07:      // 0x67 LD H, A (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t LD H, A", lineno);
                lineno += 1;
                break;
            case 0x08:      // 0x68 LD L, B (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t LD L, B", lineno);
                lineno += 1;
                break;
            case 0x09:      // 0x69 LD L, C (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t LD L, C", lineno);
                lineno += 1;
                break;
            case 0x0A:      // 0x6A LD L, D (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t LD L, D", lineno);
                lineno += 1;
                break;
            case 0x0B:      // 0x6B LD L, E (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t LD L, E", lineno);
                lineno += 1;
                break;
            case 0x0C:      // 0x6C LD L, H (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t LD L, H", lineno);
                lineno += 1;
                break;
            case 0x0D:      // 0x6D LD L, L (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t LD L, L", lineno);
                lineno += 1;
                break;
            case 0x0E:      // 0x6E LD L, (HL) (1Byte | 2Cycles)
                sprintf(instr_str, "0x%04X \t LD L, (HL)", lineno);
                lineno += 1;
                break;
            case 0x0F:      // 0x6F LD L, A (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t LD L, A", lineno);
                lineno += 1;
                break;
            default: lineno += 1;
            }
            break;


        case 0x70:
            switch (data & 0x0F) {
            case 0x00:      // 0x70 LD (HL), B (1Byte | 2Cycles)
                sprintf(instr_str, "0x%04X \t LD (HL), B", lineno);
                lineno += 1;
                break;
            case 0x01:      // 0x71 LD (HL), C (1Byte | 2Cycles)
                sprintf(instr_str, "0x%04X \t LD (HL), C", lineno);
                lineno += 1;
                break;
            case 0x02:      // 0x72 LD (HL), D (1Byte | 2Cycles)
                sprintf(instr_str, "0x%04X \t LD (HL), D", lineno);
                lineno += 1;
                break;
            case 0x03:      // 0x73 LD (HL), E (1Byte | 2Cycles)
                sprintf(instr_str, "0x%04X \t LD (HL), E", lineno);
                lineno += 1;
                break;
            case 0x04:      // 0x70 LD (HL), H (1Byte | 2Cycles)
                sprintf(instr_str, "0x%04X \t LD (HL), H", lineno);
                lineno += 1;
                break;
            case 0x05:      // 0x71 LD (HL), L (1Byte | 2Cycles)
                sprintf(instr_str, "0x%04X \t LD (HL), L", lineno);
                lineno += 1;
                break;
            case 0x06:      // 0x76 HALT (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t HALT", lineno);
                lineno += 1;
                break;
            case 0x07:      // 0x77 LD (HL), A (1Byte | 2Cycles)
                sprintf(instr_str, "0x%04X \t LD (HL), A", lineno);
                lineno += 1;
                break;
            case 0x08:      // 0x78 LD A, B (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t LD A, B", lineno);
                lineno += 1;
                break;
            case 0x09:      // 0x79 LD A, C (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t LD A, C", lineno);
                lineno += 1;
                break;
            case 0x0A:      // 0x7A LD A, D (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t LD A, D", lineno);
                lineno += 1;
                break;
            case 0x0B:      // 0x7B LD A, E (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t LD A, E", lineno);
                lineno += 1;
                break;
            case 0x0C:      // 0x7C LD A, H (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t LD A, H", lineno);
                lineno += 1;
                break;
            case 0x0D:      // 0x7D LD A, L (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t LD A, L", lineno);
                lineno += 1;
                break;
            case 0x0E:      // 0x7E LD A, (HL) (1Byte | 2Cycles)
                sprintf(instr_str, "0x%04X \t LD A, (HL)", lineno);
                lineno += 1;
                break;
            case 0x0F:      // 0x7F LD A, A (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t LD A, A", lineno);
                lineno += 1;
                break;
            default: lineno += 1;
            }
            break;


        case 0x80:
            switch (data & 0x0F) {
            case 0x00:      // 0x80 ADD B (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t ADD A, B", lineno);
                lineno += 1;
                break;
            case 0x01:      // 0x81 ADD C (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t ADD A, C", lineno);
                lineno += 1;
                break;
            case 0x02:      // 0x82 ADD D (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t ADD A, D", lineno);
                lineno += 1;
                break;
            case 0x03:      // 0x83 ADD E (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t ADD A, E", lineno);
                lineno += 1;
                break;
            case 0x04:      // 0x84 ADD H (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t ADD A, H", lineno);
                lineno += 1;
                break;
            case 0x05:      // 0x85 ADD L (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t ADD A, L", lineno);
                lineno += 1;
                break;
            case 0x06:      // 0x86 ADD (HL) (1Byte | 2Cycle)
                sprintf(instr_str, "0x%04X \t ADD A, (HL)", lineno);
                lineno += 1;
                break;
            case 0x07:      // 0x87 ADD A (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t ADD A, A", lineno);
                lineno += 1;
                break;
            case 0x08:      // 0x88 ADC B (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t ADC A, B", lineno);
                lineno += 1;
                break;
            case 0x09:      // 0x89 ADC C (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t ADC A, C", lineno);
                lineno += 1;
                break;
            case 0x0A:      // 0x8A ADC D (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t ADC A, D", lineno);
                lineno += 1;
                break;
            case 0x0B:      // 0x8B ADC E (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t ADC A, E", lineno);
                lineno += 1;
                break;
            case 0x0C:      // 0x8C ADC H (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t ADC A, H", lineno);
                lineno += 1;
                break;
            case 0x0D:      // 0x8D ADC L (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t ADC A, L", lineno);
                lineno += 1;
                break;
            case 0x0E:      // 0x8E ADC (HL) (1Byte | 2Cycle)
                sprintf(instr_str, "0x%04X \t ADC A, (HL)", lineno);
                lineno += 1;
                break;
            case 0x0F:      // 0x8F ADC A (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t ADC A, A", lineno);
                lineno += 1;
                break;
            default: lineno += 1;
            }
            break;


        case 0x90:
            switch (data & 0x0F) {
            case 0x00:      // 0x90 SUB B (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t SUB A, B", lineno);
                lineno += 1;
                break;
            case 0x01:      // 0x91 SUB C (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t SUB A, C", lineno);
                lineno += 1;
                break;
            case 0x02:      // 0x92 SUB D (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t SUB A, D", lineno);
                lineno += 1;
                break;
            case 0x03:      // 0x93 SUB E (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t SUB A, E", lineno);
                lineno += 1;
                break;
            case 0x04:      // 0x94 SUB H (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t SUB A, H", lineno);
                lineno += 1;
                break;
            case 0x05:      // 0x95 SUB L (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t SUB A, L", lineno);
                lineno += 1;
                break;
            case 0x06:      // 0x96 SUB (HL) (1Byte | 2Cycle)
                sprintf(instr_str, "0x%04X \t SUB A, (HL)", lineno);
                lineno += 1;
                break;
            case 0x07:      // 0x97 SUB A (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t SUB A, A", lineno);
                lineno += 1;
                break;
            case 0x08:      // 0x98 SBC B (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t SBC A, B", lineno);
                lineno += 1;
                break;
            case 0x09:      // 0x99 SBC C (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t SBC A, C", lineno);
                lineno += 1;
                break;
            case 0x0A:      // 0x9A SBC D (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t SBC A, D", lineno);
                lineno += 1;
                break;
            case 0x0B:      // 0x9B SBC E (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t SBC A, E", lineno);
                lineno += 1;
                break;
            case 0x0C:      // 0x9C SBC H (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t SBC A, H", lineno);
                lineno += 1;
                break;
            case 0x0D:      // 0x9D SBC L (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t SBC A, L", lineno);
                lineno += 1;
                break;
            case 0x0E:      // 0x9E SBC (HL) (1Byte | 2Cycle)
                sprintf(instr_str, "0x%04X \t SBC A, (HL)", lineno);
                lineno += 1;
                break;
            case 0x0F:      // 0x9F SBC A (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t SBC A, A", lineno);
                lineno += 1;
                break;
            default: lineno += 1;
            }
            break;


        case 0xA0:
            switch (data & 0x0F) {
            case 0x00:      // 0xA0 AND B (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t AND A, B", lineno);
                lineno += 1;
                break;
            case 0x01:      // 0xA1 AND C (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t AND A, C", lineno);
                lineno += 1;
                break;
            case 0x02:      // 0xA2 AND D (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t AND A, D", lineno);
                lineno += 1;
                break;
            case 0x03:      // 0xA3 AND E (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t AND A, E", lineno);
                lineno += 1;
                break;
            case 0x04:      // 0xA4 AND H (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t AND A, H", lineno);
                lineno += 1;
                break;
            case 0x05:      // 0xA5 AND L (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t AND A, L", lineno);
                lineno += 1;
                break;
            case 0x06:      // 0xA6 AND (HL) (1Byte | 2Cycle)
                sprintf(instr_str, "0x%04X \t AND A, (HL)", lineno);
                lineno += 1;
                break;
            case 0x07:      // 0xA7 AND A (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t AND A, A", lineno);
                lineno += 1;
                break;
            case 0x08:      // 0xA8 XOR B (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t XOR A, B", lineno);
                lineno += 1;
                break;
            case 0x09:      // 0xA9 XOR C (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t XOR A, C", lineno);
                lineno += 1;
                break;
            case 0x0A:      // 0xAA XOR D (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t XOR A, D", lineno);
                lineno += 1;
                break;
            case 0x0B:      // 0xAB XOR E (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t XOR A, E", lineno);
                lineno += 1;
                break;
            case 0x0C:      // 0xAC XOR H (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t XOR A, H", lineno);
                lineno += 1;
                break;
            case 0x0D:      // 0xAD XOR L (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t XOR A, L", lineno);
                lineno += 1;
                break;
            case 0x0E:      // 0xAE XOR (HL) (1Byte | 2Cycle)
                sprintf(instr_str, "0x%04X \t XOR A, (HL)", lineno);
                lineno += 1;
                break;
            case 0x0F:      // 0xAF XOR A (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t XOR A, A", lineno);
                lineno += 1;
                break;
            default: lineno += 1;
            }
            break;


        case 0xB0:
            switch (data & 0x0F) {
            case 0x00:      // 0xB0 OR B (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t OR A, B", lineno);
                lineno += 1;
                break;
            case 0x01:      // 0xB1 OR C (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t OR A, C", lineno);
                lineno += 1;
                break;
            case 0x02:      // 0xB2 OR D (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t OR A, D", lineno);
                lineno += 1;
                break;
            case 0x03:      // 0xB3 OR E (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t OR A, E", lineno);
                lineno += 1;
                break;
            case 0x04:      // 0xB4 OR H (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t OR A, H", lineno);
                lineno += 1;
                break;
            case 0x05:      // 0xB5 OR L (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t OR A, L", lineno);
                lineno += 1;
                break;
            case 0x06:      // 0xB6 OR (HL) (1Byte | 2Cycle)
                sprintf(instr_str, "0x%04X \t OR A, (HL)", lineno);
                lineno += 1;
                break;
            case 0x07:      // 0xB7 OR A (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t OR A, A", lineno);
                lineno += 1;
                break;
            case 0x08:      // 0xB8 CP B (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t CP A, B", lineno);
                lineno += 1;
                break;
            case 0x09:      // 0xB9 CP C (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t CP A, C", lineno);
                lineno += 1;
                break;
            case 0x0A:      // 0xBA CP D (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t CP A, D", lineno);
                lineno += 1;
                break;
            case 0x0B:      // 0xBB CP E (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t CP A, E", lineno);
                lineno += 1;
                break;
            case 0x0C:      // 0xBC CP H (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t CP A, H", lineno);
                lineno += 1;
                break;
            case 0x0D:      // 0xBD CP L (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t CP A, L", lineno);
                lineno += 1;
                break;
            case 0x0E:      // 0xBE CP (HL) (1Byte | 2Cycle)
                sprintf(instr_str, "0x%04X \t CP A, (HL)", lineno);
                lineno += 1;
                break;
            case 0x0F:      // 0xBF CP A (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t CP A, A", lineno);
                lineno += 1;
                break;
            default: lineno += 1;
            }
            break;


        case 0xC0:
            switch (data & 0x0F) {
            case 0x00:      // 0xC0 RET NZ (1Byte | 5/2Cycle)
                sprintf(instr_str, "0x%04X \t RET NZ", lineno);
                lineno += 1;
                break;
            case 0x01:      // 0xC1 POP BC (1Byte | 3Cycle)
                sprintf(instr_str, "0x%04X \t POP BC", lineno);
                lineno += 1;
                break;
            case 0x02:      // 0xC2 JP NZ, a16 (3Byte | 4/3Cycle)
                ss >> nextByte;
                instr_p->op1 = nextByte;
                ss >> nextByte;
                instr_p->op2 = nextByte;

                sprintf(instr_str, "0x%04X \t JP NZ, 0x%02X%02X", lineno, instr_p->op1, instr_p->op2);
                lineno += 3;
                break;
            case 0x03:      // 0xC3 JP a16 (3Byte | 4Cycle)
                ss >> nextByte;
                instr_p->op1 = nextByte;
                ss >> nextByte;
                instr_p->op2 = nextByte;
            
                sprintf(instr_str, "0x%04X \t JP 0x%02X%02X", lineno, instr_p->op1, instr_p->op2);
                lineno += 3;
                break;
            case 0x04:      // 0xC4 CALL NZ, a16 (3Byte | 6/3Cycle)
                ss >> nextByte;
                instr_p->op1 = nextByte;
                ss >> nextByte;
                instr_p->op2 = nextByte;

                sprintf(instr_str, "0x%04X \t CALL NZ, 0x%02X%02X", lineno, instr_p->op1, instr_p->op2);
                lineno += 3;
                break;
            case 0x05:      // 0xC5 PUSH BC (1Byte | 4Cycle)
                sprintf(instr_str, "0x%04X \t PUSH BC", lineno);
                lineno += 1;
                break;
            case 0x06:      // 0xC6 ADD A, d8 (2Byte | 2Cycle)
                ss >> nextByte;
                instr_p->op1 = nextByte;

                sprintf(instr_str, "0x%04X \t ADD A, 0x%02X", lineno, instr_p->op1);
                lineno += 2;
                break;
            case 0x07:      // 0xC7 RST 00H (1Byte | 4Cycle)
                sprintf(instr_str, "0x%04X \t RST 0x00", lineno);
                lineno += 1;
                break;
            case 0x08:      // 0xC8 RET Z (1Byte | 5/2Cycle)
                sprintf(instr_str, "0x%04X \t RET Z", lineno);
                lineno += 1;
                break;
            case 0x09:      // 0xC9 RET (1Byte | 4Cycle)
                sprintf(instr_str, "0x%04X \t RET", lineno);
                lineno += 1;
                break;
            case 0x0A:      // 0xCA JP Z, a16 (3Byte | 4/3Cycle)
                ss >> nextByte;
                instr_p->op1 = nextByte;
                ss >> nextByte;
                instr_p->op2 = nextByte;

                sprintf(instr_str, "0x%04X \t JP Z, 0x%02X%02X", lineno, instr_p->op1, instr_p->op2);
                lineno += 3;
                break;
            case 0x0B:      // 0xCB PREFIX (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t PREFIX", lineno);
                lineno += 1;
                break;
            case 0x0C:      // 0xCC CALL Z, a16 (3Byte | 6/3Cycle)
                ss >> nextByte;
                instr_p->op1 = nextByte;
                ss >> nextByte;
                instr_p->op2 = nextByte;

                sprintf(instr_str, "0x%04X \t CALL Z, 0x%02X%02X", lineno, instr_p->op1, instr_p->op2);
                lineno += 3;
                break;
            case 0x0D:      // 0xCD CALL a16 (3Byte | 6Cycle)
                ss >> nextByte;
                instr_p->op1 = nextByte;
                ss >> nextByte;
                instr_p->op2 = nextByte;

                sprintf(instr_str, "0x%04X \t CALL 0x%02X%02X", lineno, instr_p->op1, instr_p->op2);
                lineno += 3;
                break;
            case 0x0E:      // 0xCE ADC A, d8 (2Byte | 2Cycle)
                ss >> nextByte;
                instr_p->op1 = nextByte;

                sprintf(instr_str, "0x%04X \t ADC A, 0x%02X", lineno, instr_p->op1);
                lineno += 2;
                break;
            case 0x0F:      // 0xCF RST 08H (1Byte | 4Cycle)
                sprintf(instr_str, "0x%04X \t RST 0x08", lineno);
                lineno += 1;
                break;
            default: lineno += 1;
            }
            break;


        case 0xD0:
            switch (data & 0x0F) {
            case 0x00:      // 0xD0 RET NC (1Byte | 5/2Cycle)
                sprintf(instr_str, "0x%04X \t RET NC", lineno);
                lineno += 1;
                break;
            case 0x01:      // 0xD1 POP DE (1Byte | 3Cycle)
                sprintf(instr_str, "0x%04X \t POP DE", lineno);
                lineno += 1;
                break;
            case 0x02:      // 0xD2 JP NC, a16 (3Byte | 4/3Cycle)
                ss >> nextByte;
                instr_p->op1 = nextByte;
                ss >> nextByte;
                instr_p->op2 = nextByte;

                sprintf(instr_str, "0x%04X \t JP NC, 0x%02X%02X", lineno, instr_p->op1, instr_p->op2);
                lineno += 3;
                break;
            case 0x04:      // 0xD4 CALL NC, a16 (3Byte | 6/3Cycle)
                ss >> nextByte;
                instr_p->op1 = nextByte;
                ss >> nextByte;
                instr_p->op2 = nextByte;

                sprintf(instr_str, "0x%04X \t CALL NC, 0x%02X%02X", lineno, instr_p->op1, instr_p->op2);
                lineno += 3;
                break;
            case 0x05:      // 0xD5 PUSH DE (1Byte | 4Cycle)
                sprintf(instr_str, "0x%04X \t PUSH DE", lineno);
                lineno += 1;
                break;
            case 0x06:      // 0xD6 SUB d8 (2Byte | 2Cycle)
                ss >> nextByte;
                instr_p->op1 = nextByte;

                sprintf(instr_str, "0x%04X \t SUB 0x%02X", lineno, instr_p->op1);
                lineno += 2;
                break;
            case 0x07:      // 0xD7 RST 10H (1Byte | 4Cycle)
                sprintf(instr_str, "0x%04X \t RST 0x10", lineno);
                lineno += 1;
                break;
            case 0x08:      // 0xD8 RET C (1Byte | 4Cycle)
                sprintf(instr_str, "0x%04X \t RETI C", lineno);
                lineno += 1;
                break;
            case 0x09:      // 0xD9 RETI (1Byte | 4Cycle)
                sprintf(instr_str, "0x%04X \t RETI", lineno);
                lineno += 1;
                break;
            case 0x0A:      // 0xDA JP C, a16 (3Byte | 4/3Cycle)
                ss >> nextByte;
                instr_p->op1 = nextByte;
                ss >> nextByte;
                instr_p->op2 = nextByte;

                sprintf(instr_str, "0x%04X \t JP C, 0x%02X%02X", lineno, instr_p->op1, instr_p->op2);
                lineno += 3;
                break;
            case 0x0C:      // 0xDC CALL, a16 (3Byte | 3/6Cycle)
                ss >> nextByte;
                instr_p->op1 = nextByte;
                ss >> nextByte;
                instr_p->op2 = nextByte;

                sprintf(instr_str, "0x%04X \t CALL 0x%02X%02X", lineno, instr_p->op1, instr_p->op2);
                lineno += 3;
                break;
            case 0x0E:      // 0xDE SBC A, d8 (2Byte | 2Cycle)
                ss >> nextByte;
                instr_p->op1 = nextByte;

                sprintf(instr_str, "0x%04X \t SBC A, 0x%02X", lineno, instr_p->op1);
                lineno += 2;
                break;
            case 0x0F:      // 0xDF RST 18H (1Byte | 4Cycle)
                sprintf(instr_str, "0x%04X \t RST 0x18", lineno);
                lineno += 1;
                break;
            default: lineno += 1;
            }
            break;


        case 0xE0:
            switch (data & 0x0F) {
            case 0x00:      // 0xE0 LDH (a8), A (2Byte | 3Cycles)
                ss >> nextByte;
                instr_p->op1 = nextByte;

                sprintf(instr_str, "0x%04X \t LDH (0x%02X), A", lineno, instr_p->op1);
                lineno += 2;
                break;
            case 0x01:      // 0xE1 POP HL (1Byte | 3Cycles)
                sprintf(instr_str, "0x%04X \t POP HL", lineno);
                lineno += 1;
                break;
            case 0x02:      // 0xE2 LD (C), A (1Byte | 2Cycles)
                sprintf(instr_str, "0x%04X \t LD (C), A", lineno);
                lineno += 1;
                break;
            case 0x05:      // 0xE5 PUSH HL (1Byte | 4Cycles)
                sprintf(instr_str, "0x%04X \t PUSH HL", lineno);
                lineno += 1;
                break;
            case 0x06:      // 0xE6 AND d8 (2Bytes | 2Cycles)
                ss >> nextByte;
                instr_p->op1 = nextByte;

                sprintf(instr_str, "0x%04X \t AND A, 0x%02X", lineno, instr_p->op1);
                lineno += 2;
                break;
            case 0x07:      // 0xE7 RST 20H (1Byte | 4Cycle)
                sprintf(instr_str, "0x%04X \t RST 0x20", lineno);
                lineno += 1;
                break;
            case 0x08:      // 0xE8 ADD SP, r8 (2Bytes | 4Cycles)
                ss >> nextByte;
                instr_p->op1 = nextByte & 0xF;

                sprintf(instr_str, "0x%04X \t ADD SP, R%01X", lineno, instr_p->op1);
                lineno += 2;
                break;
            case 0x09:      // 0xE9 JP HL (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t JP HL", lineno);
                lineno += 1;
                break;
            case 0x0A:      // 0xEA LD (a16), A (3Bytes | 4Cycles)
                ss >> nextByte;
                instr_p->op1 = nextByte;
                ss >> nextByte;
                instr_p->op2 = nextByte;

                sprintf(instr_str, "0x%04X \t XOR 0x%02X%02X, A", lineno, instr_p->op1, instr_p->op2);
                lineno += 3;
                break;
            case 0x0E:      // 0xEE XOR d8 (2Bytes | 2Cycles)
                ss >> nextByte;
                instr_p->op1 = nextByte;
                sprintf(instr_str, "0x%04X \t XOR 0x%02X", lineno, instr_p->op1);
                lineno += 2;
                break;
            case 0x0F:      // 0xEF RST 28H (1Byte | 4Cycles)
                sprintf(instr_str, "0x%04X \t RST 0x28", lineno);
                lineno += 1;
                break;
            default: lineno += 1;
            }
            break;


        case 0xF0:
            switch (data & 0x0F) {
            case 0x00:      // 0xF0 LDH A, (a8) (2Bytes | 3Cycles)
                ss >> nextByte;
                instr_p->op1 = nextByte;
                sprintf(instr_str, "0x%04X \t LDH A, (0x%02X)", lineno, instr_p->op1);
                lineno += 2;
                break;
            case 0x01:      // 0xF1 POP AF (1Byte | 3Cycles)
                sprintf(instr_str, "0x%04X \t POP AF", lineno);
                lineno += 1;
                break;
            case 0x02:      // 0xF2 LD A, (C) (1Byte | 2Cycles)
                sprintf(instr_str, "0x%04X \t LD A, (C)", lineno);
                lineno += 1;
                break;
            case 0x03:      // 0xF3 DI (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t DI", lineno);
                lineno += 1;
                break;
            case 0x05:      // 0xF5 PUSH AF (1Byte | 4Cycles)
                sprintf(instr_str, "0x%04X \t PUSH AF", lineno);
                lineno += 1;
                break;
            case 0x06:      // 0xF6 RST 30H (1Byte | 4Cycles)
                sprintf(instr_str, "0x%04X \t RST 0x30", lineno);
                lineno += 1;
                break;
            case 0x07:
                break;
            case 0x08:      // 0xF8 LD, SP + r8 (2Bytes | 3Cycles)
                ss >> nextByte;
                instr_p->op1 = nextByte & 0xF; // Load in Register Index
                sprintf(instr_str, "0x%04X \t LD, SP + R%01X", lineno, instr_p->op1);
                lineno += 2;
                break;
            case 0x09:      // 0xF9 LD SP, HL (1Byte | 2Cycles)
                sprintf(instr_str, "0x%04X \t LD SP, HL", lineno);
                lineno += 1;
                break;
            case 0x0A:      // 0xFA LD A, (a16) (3Bytes | 4Cycles)
                ss >> nextByte;
                instr_p->op1 = nextByte;
                ss >> nextByte;
                instr_p->op2 = nextByte;
                sprintf(instr_str, "0x%04X \t LD A, (0x%02X%02X)", lineno, instr_p->op1, instr_p->op2);
                lineno += 3;
                break;
            case 0x0B:      // 0xFB EI (1Byte | 1Cycle)
                sprintf(instr_str, "0x%04X \t EI", lineno);
                lineno += 1;
                break;
            case 0x0E:      // 0xFE CP d8 (2Bytes | 2Cycles)
                ss >> nextByte;
                instr_p->op1 = nextByte;

                // (CP d8 assumes CP A, d8)
                sprintf(instr_str, "0x%04X \t CP A, 0x%02X", lineno, instr_p->op1);
                lineno += 2;
                break;
            case 0x0F:      // 0xFF RST 38H (1Bytes | 4Cycles)
                sprintf(instr_str, "0x%04X \t RST 0x38", lineno);
                lineno += 1;
                break;
            default: lineno += 1;
            }
            break;

        default: lineno += 1;
        }


        // General Properties
        instr_p->instruction = instr_str;      // Apply the Instruction Buffer

        // Output to Given Stream
        out << instr_p->instruction << '\n';

        // Clean up Data
        delete instr_p;
    }
}