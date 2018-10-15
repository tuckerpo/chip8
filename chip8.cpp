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
    assert(fontMap.size() <= 0x200);
    for (unsigned i {0}; i < fontMap.size(); ++i) 
    {
        ram[i] = fontMap.at(i);
    }

    gamestate = true;
    rng.seed(std::random_device()());
}

void Chip8::opCycle(const uint16_t& op) 
{
    constexpr uint16_t msb_mask = 0xFF00;
    constexpr uint16_t lsb_mask = 0x00FF;

    switch (op & OPMASK) 
    {
        case 0x0000:
            switch(op & 0x000F) {
            /* Clear the screen. */
            case 0x0000:
                vram = {};
                pc += 2;
                break;
            /* Return from a subroutine. */
            case 0x000E:
                --sp;
                pc = stack[sp];
                pc += 2;
                break;
            }
        break; // case 0x0000
        /* 1NNN - Jump to address NNN */
        case 0x1000:
            pc = op & 0x0FFF;
            break;
        /* 2NNN - Call subroutine at 2NNN */
        case 0x2000:
            stack[sp] = pc;
            ++sp;
            pc = op & 0x0FFF;
            pc += 2;
            break;
        /* 3XNN - Skip next instr if VX == NN */
        case 0x3000:
            V[(op & 0x0F00)>>8] == (op & 0x00FF) ? pc += 4 : pc += 2;
            break;
        /* 4Xnn - Skip next instr if Vx != NN */
        case 0x4000:
            V[(op & 0x0F00) >> 8] != (op * 0x00FF) ? pc += 4 : pc += 2;
            break;
        /* 5XY0 - Skip next instr if Vx == Vy */
        case 0x5000:
            V[(op & 0x0F00) >> 8] == V[(op & 0x00F0) >> 4] ? pc += 4 : pc += 2;
            break;
        /* 6XNN - Store NN in reg VX */
        case 0x6000:
            V[(op & 0x0F00) >> 8] = (op & 0x00FF);
            pc += 2;
            break;
        /* 7xnn - add NN to reg VX */
        case 0x7000:
            V[(op & 0x0F00) >> 8] += (op & 0x00FF);
            pc += 2;
            break;
        /* 8XXX */
        case 0x8000:
            switch(op & 0x000F) {
                /* 8XY0 - Store VY in VX */
                case 0x0000:
                    V[(op & 0x0F00) >> 8] = V[(op & 0x00F0) >> 4];
                    pc += 2;
                    break;
                /* 8XY1 - Set VX to VX | VY */
                case 0x0001:
                    V[(op & 0x0F00) >> 8] |= V[(op & 0x00F0) >> 4];
                    pc += 2;
                    break;
                /* 8XY2 - VX &= VY */
                case 0x0002:
                    V[(op & 0x0F00) >> 8] &= V[(op & 0x00F0) >> 4];
                    pc += 2;
                    break;
                /* 8XY3 - VX ^= VY */
                case 0x0003:
                    V[(op & 0x0F00) >> 8] ^= V[(op & 0x00F0) >> 4];
                    pc += 2;
                    break;
                /* 8XY4 - Add VY to VX, set VF = 01 if a carry occurs, VF = 00 if not. */
                case 0x0004:
                    V[(op & 0x0F00) >> 8] += V[(op & 0x00F0) >> 4];
                    V[(op & 0x0F00) >> 8] += V[(op & 0x00F0) >> 4]
                    > std::numeric_limits<uint8_t>::max() ? V[0xF] = 0x01 : V[0xF] = 0x00;
                    pc += 2;
                    break; 
                /* 8XY5 - Subtract the value of VY from VX. VF = 00 if borrow, VF = 01 if not. */
                case 0x0005:
                    V[(op & 0x0F00) >> 8] -= V[(op & 0x00F0) >> 4];
                    V[(op & 0x00F0) >> 4] >  V[(op & 0x0F00) >> 8]
                    ? V[0xF] = 0x00 : V[0xF] = 0x01;
                    pc += 2;
                    break;
                /* 8XY6 - Store VY shifted right by one bit in VX. VF = LSB of VX prior to shift. */
                case 0x0006:
                    V[0xF] = V[(op & 0x0F00) >> 8] & 0x1;
                    V[(op & 0x0F00) >> 8] = (V[(op & 0x00F0) >> 4] >> 1); 
                    pc += 2;
                    break;
                /* 8XY7 - VX = VY - VX; VF = 00 if borrow, 01 if not.  */
                case 0x0007:
                    V[(op & 0x0F00) >> 8] -= (V[(op & 0x00F0) >> 4] - V[(op & 0x0F00) >> 8]);
                    V[(op & 0x0F00) >> 8] > V[(op & 0x00F0) >> 4] ? V[0xF] = 0x00 : V[0xF] = 0x01;
                    pc += 2;
                    break;
                /* 8XYE - Store VY left shifted one bit to VX. Set VF to the MSB of VY prior to the shift. */
                case 0x000E:
                    V[(op & 0x0F00) >> 8] = V[(op & 0x00F0) >> 4] >> 1;
                    V[0xF] = V[(op & 0x00F0) >> 4] & 0x1;
                    pc += 2;
                    break;  
            }
        break; // END 0x8000 case
        /* 9XY0 - Skip the next instruction if VX != VY */
        case 0x9000:
            V[(op & 0x0F00) >> 8] != V[(op & 0x00F0) >> 4] ? pc += 4 : pc += 2;
            break;
        /* ANNN - Store mem address NNN in register I */
        case 0xA000:
            I = op & 0xFFF;
            pc += 2;
            break;
        /* BNNN - Jump to address NNN + V0 */
        case 0xB000:
            pc = (op & 0xFFF) + V[0x00];
            break;
        /* CXNN - Set VX to a random number with mask NN */
        case 0xC000:
            { 
            std::uniform_int_distribution<std::mt19937::result_type> dist(0, (op & 0x00FF)); 
            V[(op & 0x0F00) >> 8] = dist(rng);
            pc += 2;
            break; 
            }
        /* DXYN - Draw a sprite at position VX, VY with N bytes of sprite data starting at the address
           stored in I. Set VF to 01 if any set pixels are changed to unset, 00 if not. */
        case 0xD000:
            //TODO yikes!
            
            break;
        /* EX _ _  */
        case 0xE000:
            switch (op & 0x00FF) 
            {
                /* EX9E - Skip following instr if the key being pressed == key hex code in VX */
                case 0x009E:
                    break;
                /* EXA1 - Skip following instr if the key being pressed != key hex code in VX */
                case 0x00A1:
                    break;
            }
        break; // END 0xEX _ _ case
        
    }
    
}

void Chip8::regReset() 
{
    ram = {};
    vram = {};
    V = {};
    stack = {};
    delayTimer = 0;
    soundTimer = 0;
    I = 0;
    pc = 0x200;
    sp = 0;
}

void Chip8::loadRom(const std::string& path) 
{
    std::FILE* rom = std::fopen(path.c_str(), "rb");
    rom == nullptr ? std::cerr << "\033[31m" << "Failed to open " << path << std::endl : std::cout << "\033[32m" << path << " loaded." << std::endl;
    std::fseek(rom, 0, SEEK_END);
    auto romSize = std::ftell(rom);
    std::fseek(rom, 0, SEEK_SET);
    if (romSize > MAXROMSIZE) 
    {
        std::cerr << "ROM is too large." << std::endl;
    }
    if (romSize != std::fread(ram.begin() + 0x200, 1, romSize, rom)) 
    {
        std::cerr << "Could not load ROM into memory." << "\n";
    }
    std::fclose(rom);  
}

const uint16_t Chip8::fetchOpcode() 
{
    return ram[pc] << 8 | ram[pc + 1];
}


const bool Chip8::getGameState() 
{
    return gamestate;
}
