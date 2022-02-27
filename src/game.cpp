#include "game.h"
#include <iostream>

using namespace Settings;

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : ship(std::make_shared<Ship>()),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)) {

  InitializeAsteroids();
  InitializeShotVector();
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;



  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, ship, shots);
    Update();
    renderer.Render(ship, asteroids, shots);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::Update() {
  for (auto &asteroid: asteroids) {
    asteroid->Update();
  }

  ship->Update();

  for (auto &shot: shots) {
    if (shot->IsActive()) shot->Update();
  }

  // check to see if any asteroids hit, and then handle

  std::vector<int> blastedAsteroidIds;

  for (auto &asteroid : asteroids) {
    for (auto &shot: shots) {
      if (shot->IsActive() && shot->IsColliding(*asteroid)) {
        shot->Deactivate();
        blastedAsteroidIds.push_back(asteroid->GetId());
      }
    }
  }

  for (const int asteroidId : blastedAsteroidIds) {
    HandleAsteroidBlast(asteroidId);
  }

}

void Game::InitializeAsteroids() {
  for (size_t i = 0; i < kNumAsteroids ; i++) {
    std::shared_ptr<Asteroid> asteroid = std::make_shared<Asteroid>(Asteroid::Size::kLarge);
    asteroids.emplace_back(std::move(asteroid));
  }
}

void Game::InitializeShotVector() {
  // Generating vector of Inactive shots
  // will be activated as needed

  // Based on "object pooling" concept as described in Daniel_1985's
  // answer to this gamedev.stackexchange post:
  // https://gamedev.stackexchange.com/questions/175651/c-object-management-deletion
  for (size_t i = 0; i < kNumShots; i++) {
    std::shared_ptr<Shot> shot = std::make_shared<Shot>(0, 0, 0, false);
    shots.emplace_back(std::move(shot));
  }
}

void Game::HandleAsteroidBlast(const int &asteroidId) {
    auto asteroidHandle = std::find_if(asteroids.begin(), asteroids.end(), [&](const std::shared_ptr<Asteroid> ast){ return ast->GetId() == asteroidId; });

    if ( asteroidHandle !=asteroids.end()) { 
      Asteroid::Size size = (*asteroidHandle)->GetSize();

      switch (size) {
        case (Asteroid::Size::kLarge):
          SpawnNewAsteroids((*asteroidHandle)->GetCenter(), (*asteroidHandle)->GetDirection(), Asteroid::Size::kMedium, 2);
          score += 10;
          break;
        case (Asteroid::Size::kMedium):
          SpawnNewAsteroids((*asteroidHandle)->GetCenter(), (*asteroidHandle)->GetDirection(), Asteroid::Size::kSmall, 2);
          score +=20;
          break;
        case (Asteroid::Size::kSmall):
          score += 40;
          break;
      }

      RemoveAsteroid(asteroidId);
    }
}

void Game::SpawnNewAsteroids(Point center, int direction, Asteroid::Size size, int number) {
  const int startingDirection = direction - 40;
  const int directionChange = 83; 
  
  for (size_t i = 0; i < number; i++) {
    std::shared_ptr<Asteroid> childAsteroid = std::make_shared<Asteroid>(center, startingDirection + (i * directionChange), size);
    asteroids.emplace_back(std::move(childAsteroid));
  }
}

void Game::RemoveAsteroid(const int &asteroidId) {
  auto isDestroyed = [asteroidId](std::shared_ptr<Asteroid> ast){ return ast->GetId() == asteroidId; };
  asteroids.erase(std::remove_if(asteroids.begin(), asteroids.end(), isDestroyed));
}