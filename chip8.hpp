#pragma once
#include <cstdint>
#include <string>
#include <cstring>
#include <map>
#include <array>

/* Reference: mattmik's mastering chip8 */

class Chip8 {
    public:
        Chip8();
        void loadRom(const std::string&);
        void opCycle();
        void regReset();
    
    private:
        uint8_t ram[0x1000];
        uint8_t V[0xF];
        uint16_t I;
        uint8_t delayTimer;
        uint8_t soundTimer;
        uint16_t pc;
        uint8_t sp;
        uint16_t stack[16];
        uint8_t vram[0x800];
        //uint8_t fontMap[4*4*5];
        std::array<uint8_t, 4*4*5> fontMap;
};
