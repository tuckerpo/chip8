#include "../chip8.hpp"
#include <string>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem::v1;
int main() 
{
    Chip8 c8 = Chip8();

// C++17 actually introduces something useful?!
    const std::string romDir("../roms/");

    for (auto& content : fs::directory_iterator(romDir))
    {
        c8.loadRom(content.path().string().c_str());
    }
}
