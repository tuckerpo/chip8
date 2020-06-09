#include <chrono>
#include <csignal>
#include <memory>
#include <string>
#include <thread>

#include "chip8.hpp"
#include "gui.hpp"

#if defined(_WIN32) || defined(WIN32)
#define SDL_MAIN_HANDLED
#include "SDL.h"
#else
#include <SDL2/SDL.h>
#endif

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/bind.h>
#endif  // __EMSCRIPTEN__

static bool romLoaded = false;

#ifdef __EMSCRIPTEN__
std::unique_ptr<Chip8> c8 = std::make_unique<Chip8>();
static std::string the_rom{};
#endif  // __EMSCRIPTEN__

static void print_usage(char **argv) {
  fprintf(stderr, "Usage: %s <ROM>\n", argv[0]);
  exit(1);
}

#ifdef __EMSCRIPTEN__
static void load_rom(std::string path) {
  the_rom = path;
  c8->loadRom(path);
  romLoaded = true;
}
#endif  // __EMSCRIPTEN__

int main(int argc, char **argv) {
#ifndef __EMSCRIPTEN__
  if (argc < 2) {
    print_usage(argv);
  }

  const std::string the_rom = std::string(argv[1]);

  /* GUI */
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
    c8gui::error("Error initializing SDL2: ", SDL_GetError());
  }

  SDL_Window *c8window = SDL_CreateWindow(
      c8gui::window_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
      c8gui::w, c8gui::h, SDL_WINDOW_OPENGL);
  if (c8window == nullptr) {
    c8gui::error("Window initialization error: ", SDL_GetError());
    exit(-1);
  }

  SDL_Renderer *rend = SDL_CreateRenderer(c8window, -1, 0);
  if (rend == nullptr) {
    c8gui::error("Renderer is null: ", SDL_GetError());
    exit(-1);
  }

  SDL_RenderSetLogicalSize(rend, c8gui::w, c8gui::h);
  SDL_Texture *texture = SDL_CreateTexture(rend, SDL_PIXELFORMAT_ARGB8888,
                                           SDL_TEXTUREACCESS_STREAMING, 64, 32);
  static constexpr int pixelArrSize = 0x800;
  std::array<uint32_t, pixelArrSize> pixels{};
  uint8_t keys[16] = {
      SDLK_x, SDLK_1, SDLK_2, SDLK_3, SDLK_q, SDLK_w, SDLK_e, SDLK_a,
      SDLK_s, SDLK_d, SDLK_z, SDLK_c, SDLK_4, SDLK_r, SDLK_f, SDLK_v,
  };

  std::unique_ptr<Chip8> c8 = std::make_unique<Chip8>();
  c8->loadRom(the_rom);
  while (c8->getGameState()) {
    auto instr = c8->fetchOpcode();
    c8->opCycle(instr);
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
      switch (e.type) {
        case SDL_KEYDOWN: {
          if (e.key.keysym.sym == SDLK_ESCAPE) c8->gamestate = false;

          for (int i = 0; i < 16; ++i) {
            if (e.key.keysym.sym == keys[i]) {
              c8->key[i] = 1;
            }
          }
          break;
        }
        case SDL_KEYUP: {
          for (int i = 0; i < 16; ++i) {
            if (e.key.keysym.sym == keys[i]) {
              c8->key[i] = 0;
            }
          }
          break;
        }
        case SDL_WINDOWEVENT: {
          switch (e.window.event) {
            case SDL_WINDOWEVENT_CLOSE: {
              c8->gamestate = false;
              break;
            }
            default: {
              break;
            }
          }
        }
        default: {
          break;
        }
      }  // switch
    }    //  while poll (SDLEvent)

    if (c8->draw) {
      c8->draw = !c8->draw;
      for (std::size_t i = 0; i < c8->vram.size(); ++i) {
        uint8_t pixel = c8->vram[i];
        pixels[i] = (0x00FFFFFF * pixel) | 0xFF000000;
      }
      SDL_UpdateTexture(texture, NULL, &pixels[0], 64 * sizeof(int32_t));
      SDL_RenderClear(rend);
      SDL_RenderCopy(rend, texture, NULL, NULL);
      SDL_RenderPresent(rend);
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(16));  // ~30fps
  }  // while (game running)

#else  // we're compiling with emscripting for wasm

  // prototype for set_main_loop takes func ptr of form void (*)()
  emscripten_set_main_loop(game, 30, 0);

#endif  // __EMSCRIPTEN__

  signal(SIGINT, [](int signum) {
    std::cout << "Received signal '" << signum << "'." << std::endl;
    exit(signum);
  });

}  // main

#ifdef __EMSCRIPTEN__
using namespace emscripten;
EMSCRIPTEN_BINDINGS(my_module) { function("load_rom", &load_rom); }
#endif  // __EMSCRIPTEN__
