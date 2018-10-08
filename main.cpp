#include "chip8.hpp"
#include "gui.hpp"
#include <SDL2/SDL.h>

int main(int argc, char** argv) 
{
	/* GUI */
	if (!SDL_Init(SDL_INIT_EVERYTHING)) 
	{
		std::cerr << "Error initializing SDL2: " << SDL_GetError() << std::endl;
	}

	SDL_Window* c8window = SDL_CreateWindow(c8gui::window_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, c8gui::w, c8gui::h, SDL_WINDOW_OPENGL);
	if (c8window == nullptr) c8gui::error("Window initialization error: ", SDL_GetError());
    Chip8 c8 = Chip8();
    while (c8.getGameState()) 
    {

    }
    c8.loadRom("roms/PONG");
    return 0;
}
