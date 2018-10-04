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
