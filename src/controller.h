#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <memory>
#include <vector>
#include "Ship.h"
#include "Shot.h"

class Controller {
 public:
  void HandleInput(bool &running, std::shared_ptr<Ship> &ship, std::vector<std::shared_ptr<Shot>> &shots) const;

 private:
  void ChangeDirection(std::shared_ptr<Ship> &ship, Ship::Direction input) const;
};

#endif