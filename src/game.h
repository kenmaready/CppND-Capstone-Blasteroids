#ifndef GAME_H
#define GAME_H

#include <random>
#include <vector>
#include <algorithm>
#include <memory>
#include <string>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "Announcement.h"
#include "Ship.h"
#include "Shot.h"
#include "Asteroid.h"
#include "Explosion.h"
#include "Settings.h"

// some conveneint aliases:
typedef std::vector<std::shared_ptr<Asteroid>> AsteroidVector;
typedef std::vector<std::shared_ptr<Shot>> ShotVector;



class Game {
 public:
  enum class Status { Playing, Explosion, BetweenShips, BetweenRounds, GameOver, Terminated };

  Game(std::size_t grid_width, std::size_t grid_height);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;

 private:
  std::shared_ptr<Ship> ship {nullptr};
  ShotVector shots {};
  AsteroidVector asteroids {};
  std::shared_ptr<Explosion> explosion {nullptr};
  std::shared_ptr<Announcement> announcement {nullptr};

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{0};
  int round{1};
  Game::Status status;
  int shipsRemaining {kNumShips};
  bool shipExploding {false};

  void Update();
  void InitializeShip();
  void InitializeAsteroids();
  void InitializeShotVector();
  void HandleAsteroidBlast(const int &asteroidId);
  void SpawnNewAsteroids(Point center, int direction, Asteroid::Size size, int number);
  void RemoveAsteroid(const int &asteroidId);
};

#endif