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
          if (ship) ChangeDirection(ship, Ship::Direction::kLeft);
          break;

        case SDLK_RIGHT:
          if (ship) ChangeDirection(ship, Ship::Direction::kRight);
          break;

        case SDLK_SPACE:
          if (ship) {
            std::shared_ptr<Shot> shot = FindFreeShot(shots);
            if (shot) {
              shot->Activate(ship->GetCenter().x, ship->GetCenter().y, ship->GetRotation());
            }
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