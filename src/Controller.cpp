#include "Controller.h"
#include <iostream>
#include "SDL.h"
#include "settings.h"

using namespace Settings;

void Controller::ChangeDirection(std::shared_ptr<Ship> &ship, Ship::Direction input) const {
  if (input == Ship::Direction::kLeft) ship->ChangeRotation(-1 * kShipRotationSpeed);
  if (input == Ship::Direction::kRight) ship->ChangeRotation(1 * kShipRotationSpeed);
}

void Controller::HandleInput(Game::Status &status, std::shared_ptr<Ship> &ship, ShotVector &shots) const {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      status = Game::Status::Terminated;
      } else {

      if (ship && keystates[SDL_SCANCODE_UP]) ship->Thrust();

      if (ship && keystates[SDL_SCANCODE_LEFT] && !keystates[SDL_SCANCODE_RIGHT]) {
          ship->ChangeRotation(-kShipRotationSpeed);
      }
      
      if (ship && keystates[SDL_SCANCODE_RIGHT] && !keystates[SDL_SCANCODE_LEFT]) {
          ship->ChangeRotation(kShipRotationSpeed);
      }

      if (ship && keystates[SDL_SCANCODE_SPACE]) {
          std::shared_ptr<Shot> shot = FindFreeShot(shots);
          if (shot) {
            shot->Activate(ship->GetCenter().x, ship->GetCenter().y, ship->GetRotation(), ship->GetSpeed());
          }
      }

      if (status == Game::Status::GameOver && keystates[SDL_SCANCODE_SPACE]) {
        status = Game::Status::NewGame;
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