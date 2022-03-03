#include "Controller.h"
#include <iostream>
#include "SDL.h"
#include "settings.h"

using namespace Settings;

void Controller::HandleInput(Game::Status &status, std::shared_ptr<Ship> &ship, ShotVector &shots) const {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      status = Game::Status::Terminated;
      } else {

      if (ship) {
        if (keystates[SDL_SCANCODE_UP]) ship->Thrust();
        if (!keystates[SDL_SCANCODE_UP]) ship->Unthrust();
      
        if (keystates[SDL_SCANCODE_LEFT] && !keystates[SDL_SCANCODE_RIGHT]) {
            ship->ChangeRotation(-kShipRotationSpeed);
        }
     
        if (keystates[SDL_SCANCODE_RIGHT] && !keystates[SDL_SCANCODE_LEFT]) {
            ship->ChangeRotation(kShipRotationSpeed);
        }

        if (keystates[SDL_SCANCODE_SPACE] && ship->CanFire()) {
            std::shared_ptr<Shot> shot = FindFreeShot(shots);
            if (shot) ship->Fire(shot);
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