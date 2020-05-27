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


        // Parse Through
        // TODO: Store Execution Functions
        switch (data & 0xF0) {
        case 0x00:
            switch (data & 0x0F) {
            case 0x00:      // 0x00 NOP (1Byte | 1Cycle)
                // Store the Opcode
                instr.opcode = data;

                // Apply Instruction String
                sprintf(instr_str, "NOP");
                break;
            case 0x01:      // 0x01 LD BC, d16 (3Bytes | 3Cycles)
                // Store the Opcode
                instr.opcode = data;
            
                // Obtain the Two Operands
                ss >> instr.op1;
                ss >> instr.op2;
                
                // Apply Instruction String
                sprintf(instr_str, "LD BC, 0x%X%X", instr.op1, instr.op2);
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


        case 0x90:
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


        case 0xA0:
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


        case 0xB0:
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


        case 0xC0:
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


        case 0xD0:
            switch (data & 0x0F) {
            case 0x00:
                break;
            case 0x01:
                break;
            case 0x02:
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
            case 0x0C:
                break;
            case 0x0E:
                break;
            case 0x0F:
                break;
            default: ;
            }
            break;


        case 0xE0:
            switch (data & 0x0F) {
            case 0x00:
                break;
            case 0x01:
                break;
            case 0x02:
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
            case 0x0E:
                break;
            case 0x0F:
                break;
            default: ;
            }
            break;


        case 0xF0:
            switch (data & 0x0F) {
            case 0x00:
                break;
            case 0x01:
                break;
            case 0x02:
                break;
            case 0x03:      // 0xF3 DI (1Byte | 1Cycle)
                // Store Opcode
                instr.opcode = data;

                // Apply Instruction String
                sprintf(instr_str, "DI");
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
            case 0x0B:      // 0xFB EI (1Byte | 1Cycle)
                // Store Opcode
                instr.opcode = data;

                // Apply Instruction String
                sprintf(instr_str, "EI");
                break;
            case 0x0E:
                break;
            case 0x0F:
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
