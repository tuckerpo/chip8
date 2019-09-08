#include "chip8factory.hpp"
#include "gui.hpp"
#include <SDL2/SDL.h>
#include <memory>
#include <csignal>

#ifdef _WIN32
#define SDL_MAIN_HANDLED
#endif

static void print_usage(char **argv) {
    printf("Usage: %s <ROM>\n", argv[0]);
    exit(1);
}

int main(int argc, char *argv[]) 
{
    if (argc < 2) {
        print_usage(argv);
    }

    std::string the_rom = (argv[1]);

    uint8_t keys[16] = {
        SDLK_x,
        SDLK_1,
        SDLK_2,
        SDLK_3,
        SDLK_q,
        SDLK_w,
        SDLK_e,
        SDLK_a,
        SDLK_s,
        SDLK_d,
        SDLK_z,
        SDLK_c,
        SDLK_4,
        SDLK_r,
        SDLK_f,
        SDLK_v,
    };

	signal(SIGINT, [](int signum) {std::cout << "Received signal '" << signum << "'." << std::endl; exit(signum); });
	/* GUI */
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) 
	{	
		c8gui::error("Error initializing SDL2:", SDL_GetError());
	}

	SDL_Window *c8window = SDL_CreateWindow(c8gui::window_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, c8gui::w, c8gui::h, SDL_WINDOW_OPENGL);
	if (c8window == nullptr) c8gui::error("Window initialization error: ", SDL_GetError());
    SDL_Renderer *rend = SDL_CreateRenderer(c8window, -1, 0);

    if (!rend) {
        printf("Renderer is null %s", SDL_GetError());
        exit(-1);
    }

    SDL_RenderSetLogicalSize(rend, c8gui::w, c8gui::h);

    SDL_Texture *texture = SDL_CreateTexture(rend, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, 64, 32);

    uint32_t pixels[0x800];


	std::shared_ptr<Chip8Factory> c8f;
	auto c8 = c8f->createChip8();
    c8->loadRom(the_rom);
    while (c8->getGameState()) 
    {
        c8->opCycle(c8->fetchOpcode());
        SDL_Event e;
        while(SDL_PollEvent(&e)) {
            switch (e.type)
            {

                case SDL_KEYDOWN:
                {
                    if (e.key.keysym.sym == SDLK_ESCAPE)
                        c8->gamestate = false;

                    for (int i = 0; i < 16; ++i) {
                        if (e.key.keysym.sym == keys[i]) {
                            c8->key[i] = 1;
                        }
                    }
                    break;
                }

                case SDL_KEYUP:
                {
                    for (int i = 0; i < 16; ++i) {
                        if (e.key.keysym.sym == keys[i]) {
                            c8->key[i] = 0;
                        }
                    }
                    break;
                }

                case SDL_WINDOWEVENT:
                {
                    switch (e.window.event)
                    {
                        case SDL_WINDOWEVENT_CLOSE:
                        {
                            c8->gamestate = false;
                            break;
                        }
                        default:
                        {
                            break;
                        }
                    }
                }

                default:
                {
                    break;
                }
            } // switch
        }

        if (c8->draw) {
            c8->draw &= ~c8->draw;
            
            for (int i = 0; i < 2048; ++i) {
                uint8_t pixel = c8->vram[i];
                pixels[i] = (0x00FFFFFF * pixel) | 0xFF000000;
            }
            SDL_UpdateTexture(texture, NULL, pixels, 64 * sizeof(int32_t));
            SDL_RenderClear(rend);
            SDL_RenderCopy(rend, texture, NULL, NULL);
            SDL_RenderPresent(rend);
        }

    } // while (SDL_PollEvent)

} // main

	
