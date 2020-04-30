#include <SDL2/SDL.h>

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

// Window Default Dimensions
#define WIDTH 500
#define HEIGHT 500

using namespace std;

void hexDump(char *, std::ostream &);

static SDL_Window *window;
static SDL_Renderer *renderer;
static SDL_Texture *texture;


int main(int argc, char **argv) {
    // Argument Variables
    char *romPath = NULL;
    char *asmOutput = NULL;
    bool isDisassemble = false;
    stringstream opCodes;

    // Check Arguments
    for (int i = 0; i < argc; ++i) {
        string arg = argv[i];  // For Comparison

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
            isDisassemble = true;  // Disassemble and Output
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

    // Initialize Window, Renderer, & Texture
    //  Texture will be used to draw on
    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow(
        "yagb_emu",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        WIDTH,
        HEIGHT,
        SDL_WINDOW_OPENGL);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);


    SDL_Event windowEvent;
    while (true) {
        if (SDL_PollEvent(&windowEvent)) {
            // Check if close button was clicked
            if (windowEvent.type == SDL_QUIT) break;
        }

        // Clear Screen
        SDL_RenderClear(renderer);

        // Get Texture Pixels
        void *pixels_ptr;
        int pitch;

        SDL_LockTexture(texture, nullptr, &pixels_ptr, &pitch);
        uint32_t *pixels = static_cast<uint32_t *>(pixels_ptr);

        // Update Pixels DEBUG: Small Test to see it in action
        int sec = (WIDTH / 2) * (HEIGHT / 2);
        for (int i = 0; i < sec; i++)
            pixels[i] = 0xFF0000;  // RED

        for (int i = sec; i < sec * 2; i++)
            pixels[i] = 0x00FF00;  // GREEN

        for (int i = sec * 2; i < sec * 3; i++)
            pixels[i] = 0x0000FF;  // BLUE

        // Apply Updated Pixels & Refresh Rednerer
        SDL_UnlockTexture(texture);
        SDL_RenderCopy(renderer, texture, nullptr, nullptr);
        SDL_RenderPresent(renderer);
    }

    // SDL Clean up
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
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
