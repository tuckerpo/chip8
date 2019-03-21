#ifndef __CHIP8_FACTORY__
#define __CHIP8_FACTORY__

#include "chip8.hpp"
#include <memory>

class Chip8Factory {
	Chip8Factory() = default;
	virtual ~Chip8Factory() = delete;
	public:
	std::shared_ptr<Chip8> createChip8();
};

#endif
