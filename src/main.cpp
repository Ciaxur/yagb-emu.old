#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>

using namespace std;

void hexDump(char*, std::ostream&);

int main(int argc, char **argv) {

    // Argument Variables
    char *romPath = NULL;
    char *asmOutput = NULL;
    bool isDisassemble = false;
    stringstream opCodes;

    // Check Arguments
    for (int i = 0; i < argc; ++i) {
        string arg = argv[i]; // For Comparison

        // Check for Help Argument
        if (arg == "-h") {
            cout << "Usage: yagb [romPath] {asmOutput} [OPTIONS]\n\n"
                 << "INFO:\n"
                 << "romPath \t Path to ROM that will be used\n"
                 << "asmOutput \t Optional Parameter for outputting ASM Code to File\n\n"

                 << "OPTIONS:\n"
                 << "-h \t\t Outputs Help Manual\n"
                 << "-d \t\t Disassemble Given Rom\n";
            exit(0);
        } else if (arg == "-d") {
            isDisassemble = true; // Disassemble and Output
        }

        // Check for Path Options
        else {
            if (i == 1)
                romPath = argv[i];
            else if (i == 2)
                asmOutput = argv[i];
        }
    }

    // Check if Rom was Given
    if (romPath == NULL) {
        cerr << "No ROM Path Given!\n";
        exit(1);
    }
    std::cout << romPath << std::endl;

    hexDump(romPath, opCodes);

    return 0;
}

void hexDump(char *filePath, std::ostream &out) {
    u_char buffer[1000];
    int addr = 0;
    int n;
    std::ifstream infile;
    infile.open(filePath);

    // Check if file exists
    if (!infile) {
        cout << "File not found" << endl;
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
                cout << hex << setw(2) << setfill('0') << (int)buffer[i];
            }
            // Space each byte
            cout << " ";
        }
        // New line after n bytes
        cout << "\n";
        // Break if end of file
        if (infile.eof()) {
            break;
        }
    }
}
