#include "chip8factory.hpp"
#include "gui.hpp"
#include <SDL2/SDL.h>
#include <memory>
#include <csignal>

#ifdef _WIN32
#define SDL_MAIN_HANDLED
#endif

int main(int argc, char *argv[]) 
{
	signal(SIGINT, [](int signum) {std::cout << "Received signal '" << signum << "'." << std::endl; exit(signum); });
	/* GUI */
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) 
	{	
		c8gui::error("Error initializing SDL2:", SDL_GetError());
	}

	SDL_Window *c8window = SDL_CreateWindow(c8gui::window_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, c8gui::w, c8gui::h, SDL_WINDOW_OPENGL);
	if (c8window == nullptr) c8gui::error("Window initialization error: ", SDL_GetError());

	std::shared_ptr<Chip8Factory> c8f;
	auto c8 = c8f->createChip8();

    while (c8->getGameState()) 
    {
        c8->opCycle(c8->fetchOpcode());
    }
	
    c8->loadRom("roms/PONG");
    return 0;
}
