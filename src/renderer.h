#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "SDL.h"
#include "SDL2_gfxPrimitives.h"
#include "snake.h"
#include "Polygon.h"

class Polygon;

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

  void Render(Snake const snake, SDL_Point const &food);
  void UpdateWindowTitle(int score, int fps);
  SDL_Renderer *getSDL_Renderer() { return sdl_renderer; }

 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;
  Polygon *_poly;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
};

#endif