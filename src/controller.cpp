#include "controller.h"
#include <iostream>
#include "SDL.h"
#include "Settings.h"

using namespace Settings;

void Controller::ChangeDirection(std::shared_ptr<Ship> &ship, Ship::Direction input) const {
  if (input == Ship::Direction::kLeft) ship->ChangeRotation(-1 * kShipRotationSpeed);
  if (input == Ship::Direction::kRight) ship->ChangeRotation(1 * kShipRotationSpeed);
}

void Controller::HandleInput(bool &running, std::shared_ptr<Ship> &ship, ShotVector &shots) const {
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
          std::shared_ptr<Shot> shot = FindFreeShot(shots);
          if (shot) {
            shot->Activate(ship->GetCenter().x, ship->GetCenter().y, ship->GetRotation());
            std::cout << "Ship rotation is: " << ship->GetRotation() << std::endl;
            std::cout << "Shot direction is: " << shot->GetDirection() << std::endl;
          }


          break;
      }
    }
  }
}

std::shared_ptr<Shot> Controller::FindFreeShot(ShotVector &shots) const {
  ShotVector::const_iterator ItBeg = shots.begin();
  ShotVector::const_iterator ItEnd = shots.end();

  for (; ItBeg != ItEnd; ++ItBeg) {
    if ((*ItBeg)->IsActive()) continue;
    return (*ItBeg);
  }

  std::cout << "No Inactive Shots Found..." << std::endl;
  return nullptr;
}