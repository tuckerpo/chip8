#include "chip8.hpp"

int main(int argc, char** argv) 
{

    Chip8 c8 = Chip8();
    c8.loadRom("roms/PONG");
    return 0;

}
