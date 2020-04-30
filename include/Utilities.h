#ifndef YAGB_EMU_UTILITIES_H
#define YAGB_EMU_UTILITIES_H

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

namespace Utilities {
    void hexDump(char *, std::ostream &);
    void disassemble(char *, std::ostream &);
}

#endif //YAGB_EMU_UTILITIES_H