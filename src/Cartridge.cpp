#include "../include/Cartridge.h"



Cartridge::Cartridge(const char* path): filePath(path) {}

void Cartridge::hexDump(std::ostream &out) {
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
                out << std::hex << std::setw(2) << std::setfill('0') << (int)buffer[i];
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