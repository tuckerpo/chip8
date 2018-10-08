#pragma once
#include <cstdint>
#include <string>
#include <cstring>
#include <map>
#include <array>
#include <iostream>
#include <cassert>
static constexpr size_t MAXROMSIZE = (0x1000 - 0x0200);
/* Reference: mattmik's mastering chip8 */

class Chip8 {
    public:
        Chip8();
        void loadRom(const std::string&);
        void opCycle();
        void regReset();
        const uint16_t fetchOpcode();
    private:
        uint16_t opcode;
        std::array<uint8_t, 0x1000> ram;
        std::array<uint8_t, 0xF> V;
        uint16_t I;
        uint8_t delayTimer;
        uint8_t soundTimer;
        uint16_t pc;
        uint8_t sp;
        std::array<uint16_t, 16> stack;
        std::array<uint8_t, 0x800> vram;
        //uint8_t fontMap[4*4*5];
        std::array<uint8_t, 4*4*5> fontMap;
};
