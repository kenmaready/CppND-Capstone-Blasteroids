#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <memory>
#include "SDL.h"
#include "SDL2_gfxPrimitives.h"
#include "Ship.h"
#include "Shot.h"
#include "Asteroid.h"
#include "Explosion.h"
#include "Announcement.h"

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

  void Render(const std::shared_ptr<Ship> &ship, const std::vector<std::shared_ptr<Asteroid>> &asteroids, const std::vector<std::shared_ptr<Shot>> &shots, const std::shared_ptr<Explosion> &explosion, const std::shared_ptr<Announcement> &announcement, Polygon &NoSpawnZone);
  void UpdateWindowTitle(int score, int fps);
  SDL_Renderer *getSDL_Renderer() { return sdl_renderer; }

 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
};

#endif