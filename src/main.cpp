#include <iostream>
#include <string>

using namespace std;

int main(int argc, char **argv) {

    // Argument Variables
    char *romPath = NULL;
    char *asmOutput = NULL;
    bool isDisassemble = false;

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

    return 0;
}
