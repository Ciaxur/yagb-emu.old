#include "../include/Cartridge.h"

Cartridge::Cartridge(const char* path): filePath(path) {
    disassemble();
}

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
 * Disassembles given ROM Instructions, storing
 *  them in an Instructions Vector Array
 */
void Cartridge::disassemble() {
    std::stringstream ss;
    hexDump(ss, false);     // Hexdump without Line Numbers
    uint16_t data;

    while (ss >> data) {
        Instruction instr;              // Store each Instruction Object
        char instr_str[64]{};           // Instruction String Buffer

        instr.opcode = data;            // Store the Opcode

        // Parse Through
        // TODO: Store Execution Functions
        switch (data & 0xF0) {
        case 0x00:
            switch (data & 0x0F) {
            case 0x00:      // 0x00 NOP (1Byte | 1Cycle)
                // Apply Instruction String
                sprintf(instr_str, "NOP");
                break;
            case 0x01:      // 0x01 LD BC, d16 (3Bytes | 3Cycles)
                // Obtain the Two Operands
                ss >> instr.op1;
                ss >> instr.op2;

                sprintf(instr_str, "LD BC, 0x%X%X", instr.op1, instr.op2);
                break;
            case 0x02:      // 0x02 LD (BC), A (1Byte | 2Cycles)
                sprintf(instr_str, "LD (BC), A");
                break;
            case 0x03:      // 0x03 INC BC (1Byte | 2Cycles)
                sprintf(instr_str, "INC BC");
                break;
            case 0x04:      // 0x04 INC B (1Byte | 1Cycles)
                sprintf(instr_str, "INC B");
                break;
            case 0x05:      // 0x05 DEC B (1Byte | 1Cycles)
                sprintf(instr_str, "DEC B");
                break;
            case 0x06:      // 0x06 LD B, d8 (2Bytes | 2Cycles)
                ss >> instr.op1;

                sprintf(instr_str, "LD B, 0x%X", instr.op1);
                break;
            case 0x07:      // 0x07 RLCA (1Bytes | 1Cycles)
                sprintf(instr_str, "RLCA");
                break;
            case 0x08:      // 0x08 LD (a16), SP (3Bytes | 1Cycles)
                ss >> instr.op1;
                ss >> instr.op2;

                sprintf(instr_str, "LD ($FF00+0x%X%X), SP", instr.op1, instr.op2);
                break;
            case 0x09:      // 0x09 ADD HL, BC  (1Byte | 2Cycles)
                sprintf(instr_str, "ADD HL, BC");
                break;
            case 0x0A:      // 0x0A LD A, (BC) (1Byte | 2Cycles)
                sprintf(instr_str, "LD A, (BC)");
                break;
            case 0x0B:      // 0x0B DEC BC (1Byte | 2Cycles)
                sprintf(instr_str, "DEC BC");
                break;
            case 0x0C:      // 0x0C INC C (1Byte | 1Cycles)
                sprintf(instr_str, "INC C");
                break;
            case 0x0D:      // 0x0D DEC C (1Byte | 1Cycles)
                sprintf(instr_str, "DEC C");
                break;
            case 0x0E:      // 0x0E LD C, d8 (2Bytes | 2Cycles)
                ss >> instr.op1;

                sprintf(instr_str, "LD C, 0x%X", instr.op1);
                break;
            case 0x0F:      // 0x0F RRCA (1Byte | 1Cycles)
                sprintf(instr_str, "RRCA");
                break;
            default: ;
            }
            break;


        case 0x10:
            switch (data & 0x0F) {
            case 0x00:      // 0x10 STOP (1Byte | 1Cycle)
                // Store Opcode
                instr.opcode = data;

                // Apply Instruction String
                sprintf(instr_str, "STOP");
                break;
            case 0x01:
                break;
            case 0x02:
                break;
            case 0x03:
                break;
            case 0x04:
                break;
            case 0x05:
                break;
            case 0x06:
                break;
            case 0x07:
                break;
            case 0x08:
                break;
            case 0x09:
                break;
            case 0x0A:
                break;
            case 0x0B:
                break;
            case 0x0C:
                break;
            case 0x0D:
                break;
            case 0x0E:
                break;
            case 0x0F:
                break;
            default: ;
            }
            break;


        case 0x20:
            switch (data & 0x0F) {
            case 0x00:
                break;
            case 0x01:
                break;
            case 0x02:
                break;
            case 0x03:
                break;
            case 0x04:
                break;
            case 0x05:
                break;
            case 0x06:
                break;
            case 0x07:      // 0x27 DAA (1Byte | 1Cycle)
                // Store Opcode
                instr.opcode = data;

                // Apply Instruction String
                sprintf(instr_str, "DAA");
                break;
            case 0x08:
                break;
            case 0x09:
                break;
            case 0x0A:
                break;
            case 0x0B:
                break;
            case 0x0C:
                break;
            case 0x0D:
                break;
            case 0x0E:
                break;
            case 0x0F:      // 0x2F CPL (1Byte | 1Cycle)
                // Store Opcode
                instr.opcode = data;

                // Apply Instruction String
                sprintf(instr_str, "CPL");
                break;
            default: ;
            }
            break;


        case 0x30:
            switch (data & 0x0F) {
            case 0x00:
                break;
            case 0x01:
                break;
            case 0x02:
                break;
            case 0x03:
                break;
            case 0x04:
                break;
            case 0x05:
                break;
            case 0x06:
                break;
            case 0x07:      // 0x37 SCF (1Byte | 1Cycle)
                // Store Opcode
                instr.opcode = data;

                // Apply Instruction String
                sprintf(instr_str, "SCF");
                break;
            case 0x08:
                break;
            case 0x09:
                break;
            case 0x0A:
                break;
            case 0x0B:
                break;
            case 0x0C:
                break;
            case 0x0D:
                break;
            case 0x0E:
                break;
            case 0x0F:      // 0x3F CCF (1Byte | 1Cycle)
                // Store Opcode
                instr.opcode = data;

                // Apply Instruction String to Buffer
                sprintf(instr_str, "CCF");
                break;
            default: ;
            }
            break;


        case 0x40:
            switch (data & 0x0F) {
            case 0x00:
                break;
            case 0x01:
                break;
            case 0x02:
                break;
            case 0x03:
                break;
            case 0x04:
                break;
            case 0x05:
                break;
            case 0x06:
                break;
            case 0x07:
                break;
            case 0x08:
                break;
            case 0x09:
                break;
            case 0x0A:
                break;
            case 0x0B:
                break;
            case 0x0C:
                break;
            case 0x0D:
                break;
            case 0x0E:
                break;
            case 0x0F:
                break;
            default: ;
            }
            break;


        case 0x50:
            switch (data & 0x0F) {
            case 0x00:
                break;
            case 0x01:
                break;
            case 0x02:
                break;
            case 0x03:
                break;
            case 0x04:
                break;
            case 0x05:
                break;
            case 0x06:
                break;
            case 0x07:
                break;
            case 0x08:
                break;
            case 0x09:
                break;
            case 0x0A:
                break;
            case 0x0B:
                break;
            case 0x0C:
                break;
            case 0x0D:
                break;
            case 0x0E:
                break;
            case 0x0F:
                break;
            default: ;
            }
            break;


        case 0x60:
            switch (data & 0x0F) {
            case 0x00:
                break;
            case 0x01:
                break;
            case 0x02:
                break;
            case 0x03:
                break;
            case 0x04:
                break;
            case 0x05:
                break;
            case 0x06:
                break;
            case 0x07:
                break;
            case 0x08:
                break;
            case 0x09:
                break;
            case 0x0A:
                break;
            case 0x0B:
                break;
            case 0x0C:
                break;
            case 0x0D:
                break;
            case 0x0E:
                break;
            case 0x0F:
                break;
            default: ;
            }
            break;


        case 0x70:
            switch (data & 0x0F) {
            case 0x00:
                break;
            case 0x01:
                break;
            case 0x02:
                break;
            case 0x03:
                break;
            case 0x04:
                break;
            case 0x05:
                break;
            case 0x06:      // 0x76 HALT (1Byte | 1Cycle)
                // Store Opcode
                instr.opcode = data;

                // Apply Instruction String
                sprintf(instr_str, "HALT");
                break;
            case 0x07:
                break;
            case 0x08:
                break;
            case 0x09:
                break;
            case 0x0A:
                break;
            case 0x0B:
                break;
            case 0x0C:
                break;
            case 0x0D:
                break;
            case 0x0E:
                break;
            case 0x0F:
                break;
            default: ;
            }
            break;


        case 0x80:
            switch (data & 0x0F) {
            case 0x00:      // 0x80 ADD B (1Byte | 1Cycle)
                sprintf(instr_str, "ADD A, B");
                break;
            case 0x01:      // 0x81 ADD C (1Byte | 1Cycle)
                sprintf(instr_str, "ADD A, C");
                break;
            case 0x02:      // 0x82 ADD D (1Byte | 1Cycle)
                sprintf(instr_str, "ADD A, D");
                break;
            case 0x03:      // 0x83 ADD E (1Byte | 1Cycle)
                sprintf(instr_str, "ADD A, E");
                break;
            case 0x04:      // 0x84 ADD H (1Byte | 1Cycle)
                sprintf(instr_str, "ADD A, H");
                break;
            case 0x05:      // 0x85 ADD L (1Byte | 1Cycle)
                sprintf(instr_str, "ADD A, L");
                break;
            case 0x06:      // 0x86 ADD (HL) (1Byte | 2Cycle)
                sprintf(instr_str, "ADD A, (HL)");
                break;
            case 0x07:      // 0x87 ADD A (1Byte | 1Cycle)
                sprintf(instr_str, "ADD A, A");
                break;
            case 0x08:      // 0x88 ADC B (1Byte | 1Cycle)
                sprintf(instr_str, "ADC A, B");
                break;
            case 0x09:      // 0x89 ADC C (1Byte | 1Cycle)
                sprintf(instr_str, "ADC A, C");
                break;
            case 0x0A:      // 0x8A ADC D (1Byte | 1Cycle)
                sprintf(instr_str, "ADC A, D");
                break;
            case 0x0B:      // 0x8B ADC E (1Byte | 1Cycle)
                sprintf(instr_str, "ADC A, E");
                break;
            case 0x0C:      // 0x8C ADC H (1Byte | 1Cycle)
                sprintf(instr_str, "ADC A, H");
                break;
            case 0x0D:      // 0x8D ADC L (1Byte | 1Cycle)
                sprintf(instr_str, "ADC A, L");
                break;
            case 0x0E:      // 0x8E ADC (HL) (1Byte | 2Cycle)
                sprintf(instr_str, "ADC A, (HL)");
                break;
            case 0x0F:      // 0x8F ADC A (1Byte | 1Cycle)
                sprintf(instr_str, "ADC A, A");
                break;
            default: ;
            }
            break;


        case 0x90:
            switch (data & 0x0F) {
            case 0x00:      // 0x90 SUB B (1Byte | 1Cycle)
                sprintf(instr_str, "SUB A, B");
                break;
            case 0x01:      // 0x91 SUB C (1Byte | 1Cycle)
                sprintf(instr_str, "SUB A, C");
                break;
            case 0x02:      // 0x92 SUB D (1Byte | 1Cycle)
                sprintf(instr_str, "SUB A, D");
                break;
            case 0x03:      // 0x93 SUB E (1Byte | 1Cycle)
                sprintf(instr_str, "SUB A, E");
                break;
            case 0x04:      // 0x94 SUB H (1Byte | 1Cycle)
                sprintf(instr_str, "SUB A, H");
                break;
            case 0x05:      // 0x95 SUB L (1Byte | 1Cycle)
                sprintf(instr_str, "SUB A, L");
                break;
            case 0x06:      // 0x96 SUB (HL) (1Byte | 2Cycle)
                sprintf(instr_str, "SUB A, (HL)");
                break;
            case 0x07:      // 0x97 SUB A (1Byte | 1Cycle)
                sprintf(instr_str, "SUB A, A");
                break;
            case 0x08:      // 0x98 SBC B (1Byte | 1Cycle)
                sprintf(instr_str, "SBC A, B");
                break;
            case 0x09:      // 0x99 SBC C (1Byte | 1Cycle)
                sprintf(instr_str, "SBC A, C");
                break;
            case 0x0A:      // 0x9A SBC D (1Byte | 1Cycle)
                sprintf(instr_str, "SBC A, D");
                break;
            case 0x0B:      // 0x9B SBC E (1Byte | 1Cycle)
                sprintf(instr_str, "SBC A, E");
                break;
            case 0x0C:      // 0x9C SBC H (1Byte | 1Cycle)
                sprintf(instr_str, "SBC A, H");
                break;
            case 0x0D:      // 0x9D SBC L (1Byte | 1Cycle)
                sprintf(instr_str, "SBC A, L");
                break;
            case 0x0E:      // 0x9E SBC (HL) (1Byte | 2Cycle)
                sprintf(instr_str, "SBC A, (HL)");
                break;
            case 0x0F:      // 0x9F SBC A (1Byte | 1Cycle)
                sprintf(instr_str, "SBC A, A");
                break;
            default: ;
            }
            break;


        case 0xA0:
            switch (data & 0x0F) {
            case 0x00:      // 0xA0 AND B (1Byte | 1Cycle)
                sprintf(instr_str, "AND A, B");
                break;
            case 0x01:      // 0xA1 AND C (1Byte | 1Cycle)
                sprintf(instr_str, "AND A, C");
                break;
            case 0x02:      // 0xA2 AND D (1Byte | 1Cycle)
                sprintf(instr_str, "AND A, D");
                break;
            case 0x03:      // 0xA3 AND E (1Byte | 1Cycle)
                sprintf(instr_str, "AND A, E");
                break;
            case 0x04:      // 0xA4 AND H (1Byte | 1Cycle)
                sprintf(instr_str, "AND A, H");
                break;
            case 0x05:      // 0xA5 AND L (1Byte | 1Cycle)
                sprintf(instr_str, "AND A, L");
                break;
            case 0x06:      // 0xA6 AND (HL) (1Byte | 2Cycle)
                sprintf(instr_str, "AND A, (HL)");
                break;
            case 0x07:      // 0xA7 AND A (1Byte | 1Cycle)
                sprintf(instr_str, "AND A, A");
                break;
            case 0x08:      // 0xA8 XOR B (1Byte | 1Cycle)
                sprintf(instr_str, "XOR A, B");
                break;
            case 0x09:      // 0xA9 XOR C (1Byte | 1Cycle)
                sprintf(instr_str, "XOR A, C");
                break;
            case 0x0A:      // 0xAA XOR D (1Byte | 1Cycle)
                sprintf(instr_str, "XOR A, D");
                break;
            case 0x0B:      // 0xAB XOR E (1Byte | 1Cycle)
                sprintf(instr_str, "XOR A, E");
                break;
            case 0x0C:      // 0xAC XOR H (1Byte | 1Cycle)
                sprintf(instr_str, "XOR A, H");
                break;
            case 0x0D:      // 0xAD XOR L (1Byte | 1Cycle)
                sprintf(instr_str, "XOR A, L");
                break;
            case 0x0E:      // 0xAE XOR (HL) (1Byte | 2Cycle)
                sprintf(instr_str, "XOR A, (HL)");
                break;
            case 0x0F:      // 0xAF XOR A (1Byte | 1Cycle)
                sprintf(instr_str, "XOR A, A");
                break;
            default: ;
            }
            break;


        case 0xB0:
            switch (data & 0x0F) {
            case 0x00:      // 0xB0 OR B (1Byte | 1Cycle)
                sprintf(instr_str, "OR A, B");
                break;
            case 0x01:      // 0xB1 OR C (1Byte | 1Cycle)
                sprintf(instr_str, "OR A, C");
                break;
            case 0x02:      // 0xB2 OR D (1Byte | 1Cycle)
                sprintf(instr_str, "OR A, D");
                break;
            case 0x03:      // 0xB3 OR E (1Byte | 1Cycle)
                sprintf(instr_str, "OR A, E");
                break;
            case 0x04:      // 0xB4 OR H (1Byte | 1Cycle)
                sprintf(instr_str, "OR A, H");
                break;
            case 0x05:      // 0xB5 OR L (1Byte | 1Cycle)
                sprintf(instr_str, "OR A, L");
                break;
            case 0x06:      // 0xB6 OR (HL) (1Byte | 2Cycle)
                sprintf(instr_str, "OR A, (HL)");
                break;
            case 0x07:      // 0xB7 OR A (1Byte | 1Cycle)
                sprintf(instr_str, "OR A, A");
                break;
            case 0x08:      // 0xB8 CP B (1Byte | 1Cycle)
                sprintf(instr_str, "CP A, B");
                break;
            case 0x09:      // 0xB9 CP C (1Byte | 1Cycle)
                sprintf(instr_str, "CP A, C");
                break;
            case 0x0A:      // 0xBA CP D (1Byte | 1Cycle)
                sprintf(instr_str, "CP A, D");
                break;
            case 0x0B:      // 0xBB CP E (1Byte | 1Cycle)
                sprintf(instr_str, "CP A, E");
                break;
            case 0x0C:      // 0xBC CP H (1Byte | 1Cycle)
                sprintf(instr_str, "CP A, H");
                break;
            case 0x0D:      // 0xBD CP L (1Byte | 1Cycle)
                sprintf(instr_str, "CP A, L");
                break;
            case 0x0E:      // 0xBE CP (HL) (1Byte | 2Cycle)
                sprintf(instr_str, "CP A, (HL)");
                break;
            case 0x0F:      // 0xBF CP A (1Byte | 1Cycle)
                sprintf(instr_str, "CP A, A");
                break;
            default: ;
            }
            break;


        case 0xC0:
            switch (data & 0x0F) {
            case 0x00:      // 0xC0 RET NZ (1Byte | 5/2Cycle)
                sprintf(instr_str, "RET NZ");
                break;
            case 0x01:      // 0xC1 POP BC (1Byte | 3Cycle)
                sprintf(instr_str, "POP BC");
                break;
            case 0x02:      // 0xC2 JP NZ, a16 (3Byte | 4/3Cycle)
                ss >> instr.op1;
                ss >> instr.op2;
            
                sprintf(instr_str, "JP NZ, 0x%X%X", instr.op1, instr.op2);
                break;
            case 0x03:      // 0xC3 JP a16 (3Byte | 4Cycle)
                ss >> instr.op1;
                ss >> instr.op2;
            
                sprintf(instr_str, "JP 0x%X%X", instr.op1, instr.op2);
                break;
            case 0x04:      // 0xC4 CALL NZ, a16 (3Byte | 6/3Cycle)
                ss >> instr.op1;
                ss >> instr.op2;
            
                sprintf(instr_str, "CALL NZ, 0x%X%X", instr.op1, instr.op2);
                break;
            case 0x05:      // 0xC5 PUSH BC (1Byte | 4Cycle)
                sprintf(instr_str, "PUSH BC");
                break;
            case 0x06:      // 0xC6 ADD A, d8 (2Byte | 2Cycle)
                ss >> instr.op1;
            
                sprintf(instr_str, "ADD A, 0x%X", instr.op1);
                break;
            case 0x07:      // 0xC7 RST 00H (1Byte | 4Cycle)
                sprintf(instr_str, "RST 0x00");
                break;
            case 0x08:      // 0xC8 RET Z (1Byte | 5/2Cycle)
                sprintf(instr_str, "RET Z");
                break;
            case 0x09:      // 0xC9 RET (1Byte | 4Cycle)
                sprintf(instr_str, "RET");
                break;
            case 0x0A:      // 0xCA JP Z, a16 (3Byte | 4/3Cycle)
                ss >> instr.op1;
                ss >> instr.op2;
            
                sprintf(instr_str, "JP Z, 0x%X%X", instr.op1, instr.op2);
                break;
            case 0x0B:      // 0xCB PREFIX (1Byte | 1Cycle)
                sprintf(instr_str, "PREFIX");
                break;
            case 0x0C:      // 0xCC CALL Z, a16 (3Byte | 6/3Cycle)
                ss >> instr.op1;
                ss >> instr.op2;
            
                sprintf(instr_str, "CALL Z, 0x%X%X", instr.op1, instr.op2);
                break;
            case 0x0D:      // 0xCD CALL a16 (3Byte | 6Cycle)
                ss >> instr.op1;
                ss >> instr.op2;
            
                sprintf(instr_str, "CALL 0x%X%X", instr.op1, instr.op2);
                break;
            case 0x0E:      // 0xCE ADC A, d8 (2Byte | 2Cycle)
                ss >> instr.op1;
            
                sprintf(instr_str, "ADC A, 0x%X", instr.op1);
                break;
            case 0x0F:      // 0xCF RST 08H (1Byte | 4Cycle)
                sprintf(instr_str, "RST 0x08");
                break;
            default: ;
            }
            break;


        case 0xD0:
            switch (data & 0x0F) {
            case 0x00:      // 0xD0 RET NC (1Byte | 5/2Cycle)
                sprintf(instr_str, "RET NC");
                break;
            case 0x01:      // 0xD1 POP DE (1Byte | 3Cycle)
                sprintf(instr_str, "POP DE");
                break;
            case 0x02:      // 0xD2 JP NC, a16 (3Byte | 4/3Cycle)
                ss >> instr.op1;
                ss >> instr.op2;
            
                sprintf(instr_str, "JP NC, 0x%X%X", instr.op1, instr.op2);
                break;
            case 0x04:      // 0xD4 CALL NC, a16 (3Byte | 6/3Cycle)
                ss >> instr.op1;
                ss >> instr.op2;
            
                sprintf(instr_str, "CALL NC, 0x%X%X", instr.op1, instr.op2);
                break;
            case 0x05:      // 0xD5 PUSH DE (1Byte | 4Cycle)
                sprintf(instr_str, "PUSH DE");
                break;
            case 0x06:      // 0xD6 SUB d8 (2Byte | 2Cycle)
                ss >> instr.op1;
            
                sprintf(instr_str, "SUB 0x%X", instr.op1);
                break;
            case 0x07:      // 0xD7 RST 10H (1Byte | 4Cycle)
                sprintf(instr_str, "RST 0x10");
                break;
            case 0x08:      // 0xD8 RET C (1Byte | 4Cycle)
                sprintf(instr_str, "RETI C");
                break;
            case 0x09:      // 0xD9 RETI (1Byte | 4Cycle)
                sprintf(instr_str, "RETI");
                break;
            case 0x0A:      // 0xDA JP C, a16 (3Byte | 4/3Cycle)
                ss >> instr.op1;
                ss >> instr.op2;
                
                sprintf(instr_str, "JP C, 0x%X%X", instr.op1, instr.op2);
                break;
            case 0x0C:      // 0xDC CALL, a16 (3Byte | 3/6Cycle)
                ss >> instr.op1;
                ss >> instr.op2;
                
                sprintf(instr_str, "CALL 0x%X%X", instr.op1, instr.op2);
                break;
            case 0x0E:      // 0xDE SBC A, d8 (2Byte | 2Cycle)
                ss >> instr.op1;

                sprintf(instr_str, "SBC A, 0x%X", instr.op1);
                break;
            case 0x0F:      // 0xDF RST 18H (1Byte | 4Cycle)
                sprintf(instr_str, "RST 0x18");
                break;
            default: ;
            }
            break;


        case 0xE0:
            switch (data & 0x0F) {
            case 0x00:      // 0xE0 LDH (a8), A (2Byte | 3Cycles)
                ss >> instr.op1;
            
                sprintf(instr_str, "LDH (0x%X), A", instr.op1);
                break;
            case 0x01:      // 0xE1 POP HL (1Byte | 3Cycles)
                sprintf(instr_str, "POP HL");
                break;
            case 0x02:      // 0xE2 LD (C), A (1Byte | 2Cycles)
                sprintf(instr_str, "LD (C), A");
                break;
            case 0x05:      // 0xE5 PUSH HL (1Byte | 4Cycles)
                sprintf(instr_str, "PUSH HL");
                break;
            case 0x06:      // 0xE6 AND d8 (2Bytes | 2Cycles)
                ss >> instr.op1;
            
                sprintf(instr_str, "AND A, 0x%X", instr.op1);
                break;
            case 0x07:      // 0xE7 RST 20H (1Byte | 4Cycle)
                sprintf(instr_str, "RST 0x20");
                break;
            case 0x08:      // 0xE8 ADD SP, r8 (2Bytes | 4Cycles)
                ss >> instr.op1;
            
                sprintf(instr_str, "ADD SP, R%X", instr.op1);
                break;
            case 0x09:      // 0xE9 JP HL (1Byte | 1Cycle)
                sprintf(instr_str, "JP HL");
                break;
            case 0x0A:      // 0xEA LD (a16), A (3Bytes | 4Cycles)
                ss >> instr.op1;
                ss >> instr.op2;
                
                sprintf(instr_str, "XOR 0x%X%X, A", instr.op1, instr.op2);
                break;
            case 0x0E:      // 0xEE XOR d8 (2Bytes | 2Cycles)
                ss >> instr.op1;
                sprintf(instr_str, "XOR 0x%X", instr.op1);
                break;
            case 0x0F:      // 0xEF RST 28H (1Byte | 4Cycles)
                sprintf(instr_str, "RST 0x28");
                break;
            default: ;
            }
            break;


        case 0xF0:
            switch (data & 0x0F) {
            case 0x00:      // 0xF0 LDH A, (a8) (2Bytes | 3Cycles)
                ss >> instr.op1;
                sprintf(instr_str, "LDH A, (0x%X)", instr.op1);
                break;
            case 0x01:      // 0xF1 POP AF (1Byte | 3Cycles)
                sprintf(instr_str, "POP AF");
                break;
            case 0x02:      // 0xF2 LD A, (C) (1Byte | 2Cycles)
                sprintf(instr_str, "LD A, (C)");
                break;
            case 0x03:      // 0xF3 DI (1Byte | 1Cycle)
                sprintf(instr_str, "DI");
                break;
            case 0x05:      // 0xF5 PUSH AF (1Byte | 4Cycles)
                sprintf(instr_str, "PUSH AF");
                break;
            case 0x06:      // 0xF6 RST 30H (1Byte | 4Cycles)
                sprintf(instr_str, "RST 0x30");
                break;
            case 0x07:
                break;
            case 0x08:      // 0xF8 LD, SP + r8 (2Bytes | 3Cycles)
                ss >> instr.op1;    // Load in Register Index
                sprintf(instr_str, "LD, SP + R%X", instr.op1);
                break;
            case 0x09:      // 0xF9 LD SP, HL (1Byte | 2Cycles)
                sprintf(instr_str, "LD SP, HL");
                break;
            case 0x0A:      // 0xFA LD A, (a16) (3Bytes | 4Cycles)
                ss >> instr.op1;
                ss >> instr.op2;
                sprintf(instr_str, "LD A, (0x%X%X)", instr.op1, instr.op2);
                break;
            case 0x0B:      // 0xFB EI (1Byte | 1Cycle)
                sprintf(instr_str, "EI");
                break;
            case 0x0E:      // 0xFE CP d8 (2Bytes | 2Cycles)
                ss >> instr.op1;

                // (CP d8 assumes CP A, d8)
                sprintf(instr_str, "CP A, 0x%H", instr.op1);
                break;
            case 0x0F:      // 0xFF RST 38H (1Bytes | 4Cycles)

                sprintf(instr_str, "RST 0x38");
                break;
            default: ;
            }
            break;

        default: ;
        }


        // Genearl Properties
        instr.instruction = instr_str;      // Apply the Instruction Buffer

        // Append Instruction
        instructions.push_back(instr);
    }

    // DEBUG: Output Disassembly to File
    std::ofstream file("main.asm", std::ios::out);
    for(Instruction &i : instructions)
        file << i.instruction << '\n';
    file.close();
}
