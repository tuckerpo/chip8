#include "chip8factory.hpp"

std::shared_ptr<Chip8> Chip8Factory::createChip8() {
	return std::make_shared<Chip8>(Chip8());

}
