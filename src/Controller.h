#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <memory>
#include <vector>
#include "Ship.h"
#include "Shot.h"
#include "Game.h"

typedef std::vector<std::shared_ptr<Shot>> ShotVector;

class Controller {
 public:
  void HandleInput(Game::Status &status, std::shared_ptr<Ship> &ship, ShotVector &shots) const;

 private:
  void ChangeDirection(std::shared_ptr<Ship> &ship, Ship::Direction input) const;
  std::shared_ptr<Shot> FindFreeShot(ShotVector &shots) const;
};

#endif