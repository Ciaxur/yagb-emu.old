#pragma once

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>


class Cartridge {
    private:
        const char* filePath;
    
    public:
        Cartridge(const char* path);
        void hexDump(std::ostream &);
};
