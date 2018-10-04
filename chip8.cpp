#include "chip8.hpp"



Chip8::Chip8() 
{
    regReset();
    fontMap =  {0xF0, 0x90, 0x90, 0x90, 0xF0,
                0x20, 0x60, 0x20, 0x20, 0x70,
                0xF0, 0x10, 0xF0, 0x80, 0xF0, 
                0xF0, 0x10, 0xF0, 0x10, 0xF0,
                0x90, 0x90, 0xF0, 0x10, 0x10,
                0xF0, 0x80, 0xF0, 0x10, 0xF0, 
                0xF0, 0x80, 0xF0, 0x90, 0xF0,
                0xF0, 0x10, 0x20, 0x40, 0x40,
                0xF0, 0x90, 0xF0, 0x90, 0xF0,
                0xF0, 0x90, 0xF0, 0x10, 0xF0,
                0xF0, 0x90, 0xF0, 0x90, 0x90,
                0xE0, 0x90, 0xE0, 0x90, 0xE0,
                0xF0, 0x80, 0x80, 0x80, 0xF0,
                0xE0, 0x90, 0x90, 0x90, 0xE0,
                0xF0, 0x80, 0xF0, 0x80, 0xF0,
                0xF0, 0x80, 0xF0, 0x80, 0x80};
}

void Chip8::opCycle() 
{
    opcode = ram[pc] << 8 | memory[pc + 1];
    uint16_t msb_mask = 0xFF00;
    uint16_t lsb_mask = 0x00FF;
}

void Chip8::regReset() 
{
    std::memset(ram, 0, sizeof(ram));
    std::memset(vram, 0, sizeof(vram));
    std::memset(V, 0, sizeof(V));
    std::memset(stack, 0, sizeof(stack));
    delayTimer = 0;
    soundTimer = 0;
    I = 0;
    pc = 0x200;
    sp = 0;
}

void Chip8::loadRom(const std::string& path) 
{
    std::FILE* rom = std::fopen(path.c_str(), "rb");
    rom == nullptr ? std::cerr << "Failed to open " << path : std::cout << path << " loaded." << std::endl;
    std::fseek(rom, 0, SEEK_END);
    auto romSize = std::ftell(rom);
    std::fseek(rom, 0, SEEK_SET);
    if (romSize > MAXROMSIZE) 
    {
        std::cerr << "ROM is too large." << std::endl;
    }
    if (romSize != std::fread(ram + 0x200, 1, romSize, rom)) 
    {
        std::cerr << "Could not load ROM into memory." << "\n";
    }
    std::fclose(rom);  
    std::cout << "Rom loaded" << std::endl;
}

