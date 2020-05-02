#include "../include/Utilities.h"

using namespace std;

void Utilities::hexDump(char *filePath, std::ostream &out) {
    u_char buffer[1000];
    int addr = 0;
    int n;
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
        // Print line of n bytes
        for (int i = 0; i < 16; i++) {
            if (i + 1 <= n) {
                out << hex << setw(2) << setfill('0') << (int)buffer[i];
            }
            // Space each byte
            out << " ";
        }
        // New line after n bytes
        out << "\n";
        // Break if end of file
        if (infile.eof()) {
            break;
        }
    }
}

void Utilities::disassemble(char *filePath, std::ostream &out) {
    bool dataSectionFound = false;
    stringstream ss;
    Utilities::hexDump(filePath, ss);

    // Format cout Flags
    ios_base::fmtflags prevFlags(out.flags());  // To restore cout Output Style
    out << hex << uppercase << setw(2) << setfill('0');

    ss.seekg(0x100);

    u_int16_t PC = 0x100;  // Start at Cartridge Header
    u_int16_t opcode;      // 16-bit Opcode
    u_int8_t param8;       // 8-bit Data
    u_int16_t param16;     // 16-bit Data
    u_int16_t addr;        // 16-bit Address

    while (ss >> opcode) {
        //ss >> param;
        out << setw(4) << setfill('0') << PC << '\t';
        out << setw(2) << setfill('0') << opcode << ' ';  //<< setw(2) << setfill('0') << param << '\t';

        if (!dataSectionFound) {
            switch (opcode & 0xF0) {
            case 0x00:
                switch (opcode & 0x0F) {
                case 0x00:
                    out << "NOP";
                    break;
                }
                break;
            case 0x10:
                switch (opcode & 0x0F) {
                case 0x00:
                    out << "STOP";
                    break;
                }
                break;



            case 0xA0:
                switch (opcode & 0x0F) {
                case 0x00:                // LD A,[r16]
                    out << "LD A, (BC)";  // Obtain r16 from 16-bit Register BC
                    break;

                case 0x01:
                    out << "LD A, (DE)";  // Obtain r16 from 16-bit Register DE
                    break;
                case 0x02:
                    // HL+ -> Load value into Register 'A'
                    //  pointed by HL and increment HL Afterwards
                    out << "LD A, (HL+)";  // Obtain r16 from 16-bit Register HL
                    break;
                case 0x03:
                    // HL+ -> Load value into Register 'A'
                    //  pointed by HL and decrement HL Afterwards
                    out << "LD A, (HL-)";  // Obtain r16 from 16-bit Register HL
                    break;
                case 0x04:
                    out << "LD C, D";
                    break;
                case 0x05:
                    out << "LD E, D";
                    break;
                case 0x06:
                    out << "LD L, D";
                    break;
                case 0x07:
                    out << "LD A, D";
                    break;
                case 0x08:
                    out << "ADC A, D";
                    break;
                case 0x09:
                    out << "SBC A, D";
                    break;
                case 0x0A:
                    out << "XOR D";
                    break;
                case 0x0B:
                    out << "CP D";
                    break;
                case 0x0C:
                    out << "JP Z, ";

                    // Obtain 16bit Address
                    ss >> addr;
                    out << addr;
                    break;
                    break;
                case 0x0D:
                    out << "JP C, ";

                    // Obtain 16bit Address
                    ss >> addr;
                    out << addr;
                    break;
                case 0x0E:
                    // Obtain 16bit Address
                    ss >> addr;
                    out << "JP " << addr << ", A";
                    break;
                case 0x0F:
                    // Obtain 16bit Address
                    ss >> addr;
                    out << "JP A, " << addr;
                    break;


                default:
                    break;
                }
                break;

            case 0xB0:
                switch (opcode & 0x0F) {
                case 0x00:
                    out << "DEC BC";
                    break;
                case 0x01:
                    out << "DEC DE";
                    break;
                case 0x02:
                    out << "DEC HL";
                    break;
                case 0x03:
                    out << "DEC SP";
                    break;
                case 0x04:
                    out << "LD C, E";
                    break;
                case 0x05:
                    out << "LD E, E";
                    break;
                case 0x06:
                    out << "LD L, E";
                    break;
                case 0x07:
                    out << "LD A, E";
                    break;
                case 0x08:
                    out << "ADC A, E";
                    break;
                case 0x09:
                    out << "SBC A, E";
                    break;
                case 0x0A:
                    out << "XOR E";
                    break;
                case 0x0B:
                    out << "CP E";
                    break;
                case 0x0C:
                    out << "PREFIX";
                    break;
                case 0x0F:
                    out << "EI";
                    break;

                default:
                    break;
                }
                break;

            case 0xC0:
                switch (opcode & 0x0F) {
                case 0x00:
                    out << "INC C";
                    break;
                case 0x01:
                    out << "INC E";
                    break;
                case 0x02:
                    out << "INC L";
                    break;
                case 0x03:
                    out << "INC A";
                    break;
                case 0x04:
                    out << "LD C, H";
                    break;
                case 0x05:
                    out << "LD E, H";
                    break;
                case 0x06:
                    out << "LD L, H";
                    break;
                case 0x07:
                    out << "LD A, H";
                    break;
                case 0x08:
                    out << "ADC A, H";
                    break;
                case 0x09:
                    out << "SBC A, H";
                    break;
                case 0x0A:
                    out << "XOR H";
                    break;
                case 0x0B:
                    out << "CP H";
                    break;
                case 0x0C:
                    // Obtain 16bit Address
                    ss >> addr;
                    out << "CALL Z, " << addr;
                    break;
                case 0x0D:
                    // Obtain 16bit Address
                    ss >> addr;
                    out << "CALL C, " << addr;
                    break;

                default:
                    break;
                }
                break;

            case 0xD0:
                switch (opcode & 0x0F) {
                case 0x00:
                    out << "DEC C";
                    break;
                case 0x01:
                    out << "DEC E";
                    break;
                case 0x02:
                    out << "DEC L";
                    break;
                case 0x03:
                    out << "DEC A";
                    break;
                case 0x04:
                    out << "LD C, L";
                    break;
                case 0x05:
                    out << "LD E, L";
                    break;
                case 0x06:
                    out << "LD L, L";
                    break;
                case 0x07:
                    out << "LD A, L";
                    break;
                case 0x08:
                    out << "ADC A, L";
                    break;
                case 0x09:
                    out << "SBC A, L";
                    break;
                case 0x0A:
                    out << "XOR L";
                    break;
                case 0x0B:
                    out << "CP L";
                    break;
                case 0x0C:
                    // Obtain 16bit Address
                    ss >> addr;
                    out << "CALL, " << addr;
                    break;

                default:
                    break;
                }
                break;

            case 0xE0:
                switch (opcode & 0x0F) {
                case 0x00:
                    // Obtain 8bit Param (Immediate Data)
                    ss >> param8;
                    out << "LD C, " << param8;
                    break;
                case 0x01:
                    // Obtain 8bit Param (Immediate Data)
                    ss >> param8;
                    out << "LD E, " << param8;
                    break;
                case 0x02:
                    // Obtain 8bit Param (Immediate Data)
                    ss >> param8;
                    out << "LD L, " << param8;
                    break;
                case 0x03:
                    // Obtain 8bit Param (Immediate Data)
                    ss >> param8;
                    out << "LD A, " << param8;
                    break;
                case 0x04:
                    out << "LD C, (HL)";
                    break;
                case 0x05:
                    out << "LD E, (HL)";
                    break;
                case 0x06:
                    out << "LD L, (HL)";
                    break;
                case 0x07:
                    out << "LD A, (HL)";
                    break;
                case 0x08:
                    out << "ADC A, (HL)";
                    break;
                case 0x09:
                    out << "SBC A, (HL)";
                    break;
                case 0x0A:
                    out << "XOR (HL)";
                    break;
                case 0x0B:
                    out << "CP (HL)";
                    break;
                case 0x0C:
                    // Obtain 8bit Param (Immediate Data)
                    ss >> param8;
                    out << "ADC A, " << param8;
                    break;
                case 0x0D:
                    // Obtain 8bit Param (Immediate Data)
                    ss >> param8;
                    out << "SBC A, " << param8;
                    break;
                case 0x0E:
                    // Obtain 8bit Param (Immediate Data)
                    ss >> param8;
                    out << "XOR " << param8;
                    break;
                case 0x0F:
                    // Obtain 8bit Param (Immediate Data)
                    ss >> param8;
                    out << "CP " << param8;
                    break;

                default:
                    break;
                }
                break;

            case 0xF0:
                switch (opcode & 0x0F) {
                case 0x00:
                    out << "RRCA";
                    break;
                case 0x01:
                    out << "RRA";
                    break;
                case 0x02:
                    out << "CPL";
                    break;
                case 0x03:
                    out << "CCF";
                    break;
                case 0x04:
                    out << "LD C, A";
                    break;
                case 0x05:
                    out << "LD E, A";
                    break;
                case 0x06:
                    out << "LD L, A";
                    break;
                case 0x07:
                    out << "LD A, A";
                    break;
                case 0x08:
                    out << "ADC A, A";
                    break;
                case 0x09:
                    out << "SBC A, A";
                    break;
                case 0x0A:
                    out << "XOR A";
                    break;
                case 0x0B:
                    out << "CP A";
                    break;
                case 0x0C:
                    out << "RST 08H";
                    break;
                case 0x0D:
                    out << "RST 18H";
                    break;
                case 0x0E:
                    out << "RST 28H";
                    break;
                case 0x0F:
                    out << "RST 38H";
                    break;

                default:
                    break;
                }
                break;

            default:
                // dataSectionFound = true;
                break;
            }
        }

        PC += 0x1;
        out << "\n";
    }
}
