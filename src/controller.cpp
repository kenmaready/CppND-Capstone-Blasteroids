#include "controller.h"
#include <iostream>
#include "SDL.h"
#include "Settings.h"

using namespace Settings;

void Controller::ChangeDirection(std::shared_ptr<Ship> &ship, Ship::Direction input) const {
  if (input == Ship::Direction::kLeft) ship->ChangeRotation(-1 * kShipRotationSpeed);
  if (input == Ship::Direction::kRight) ship->ChangeRotation(1 * kShipRotationSpeed);
}

void Controller::HandleInput(bool &running, std::shared_ptr<Ship> &ship, std::vector<std::shared_ptr<Shot>> &shots) const {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
    } else if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
        case SDLK_UP:
          break;

        case SDLK_LEFT:
          ChangeDirection(ship, Ship::Direction::kLeft);
          break;

        case SDLK_RIGHT:
          ChangeDirection(ship, Ship::Direction::kRight);
          break;

        case SDLK_SPACE:
          shots.emplace_back(std::make_shared<Shot>(ship->GetCenter().x, ship->GetCenter().y, ship->GetRotation()));
          std::cout << "Ship rotation is: " << ship->GetRotation() << std::endl;
          std::cout << "Shot direction is: " << shots.back()->GetDirection() << std::endl;
          break;
      }
    }
  }
}