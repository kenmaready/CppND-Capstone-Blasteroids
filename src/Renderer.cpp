#include "Renderer.h"
#include <iostream>
#include <string>
#include <thread>
#include <SDL2/SDL_ttf.h>


Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  TTF_Init();

  // Create Window
  sdl_window = SDL_CreateWindow("Blasteroids!", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

void Renderer::Render(const std::shared_ptr<Ship> &ship, const std::vector<std::shared_ptr<Asteroid>> &asteroids, const std::vector<std::shared_ptr<Shot>> &shots, const std::shared_ptr<Explosion> &explosion, const std::shared_ptr<Announcement> &announcement) {
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  // Render Asteroids
  for (const auto &asteroid : asteroids) asteroid->Draw(sdl_renderer);

  if (ship) ship->Draw(sdl_renderer);
  else if (explosion && !explosion->IsComplete()) explosion->Draw(sdl_renderer);

  for (const auto &shot : shots) {
    shot->Draw(sdl_renderer);
  }

  if (announcement)  announcement->Draw(sdl_renderer);


  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(int score, int shipsRemaining) {
  std::string title{"Blasteroids!   Score: " + std::to_string(score) + "  Ships: " + std::to_string(shipsRemaining)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}
