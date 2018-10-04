#include "chip8.hpp"
#include <string>

int main() 
{
    Chip8 c8 = Chip8();
    std::string romPath = "roms/";
    std::string name;
    while (std::cin >> name) 
    {
        c8.loadRom(romPath + name);
    }    
}
