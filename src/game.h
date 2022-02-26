#ifndef GAME_H
#define GAME_H

#include <random>
#include <vector>
#include <memory>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "Ship.h"
#include "Shot.h"
#include "Asteroid.h"
#include "Settings.h"

// some conveneint aliases:
typedef std::vector<std::shared_ptr<Asteroid>> AsteroidVector;
typedef std::vector<std::shared_ptr<Shot>> ShotVector;


class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;

 private:
  SDL_Point food;
  std::shared_ptr<Ship> ship;
  ShotVector shots;
  AsteroidVector asteroids;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{0};

  void Update();
  void InitializeAsteroids();
  void InitializeShotVector();
  void HandleAsteroidBlast(std::shared_ptr<Asteroid> asteroid);
};

#endif