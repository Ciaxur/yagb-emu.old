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

    unsigned short PC = 0x100; // Start at Cartridge Header
    unsigned short opcode;
    unsigned short param;
    unsigned short addr;

    while (ss >> opcode) {
        //ss >> param;
        out << setw(4) << setfill('0') << PC << '\t';
        out << setw(2) << setfill('0') << opcode << ' '; //<< setw(2) << setfill('0') << param << '\t';

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
            default:
                dataSectionFound = true;
                break;
            }
        }

        PC += 0x1;
        out << "\n";
    }
}
