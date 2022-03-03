#include "Game.h"
#include "Controller.h"
#include <iostream>
#include <thread>
#include <future>
#include <chrono>

using namespace Settings;

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : engine(dev()) {
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  status = Game::Status::NewGame;

  while (status != Game::Status::Terminated) {

    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(status, ship, shots);
    Update();
    renderer.Render(ship, asteroids, shots, explosion, announcement);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, shipsRemaining);
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

  if (status == Game::Status::NewGame) {
    // reset game:
    asteroids.clear();
    ship.reset();
    score = 0;
    round = 1;
    shipsRemaining = kNumShips;
    SetNoSpawnZone();
    status = Game::Status::StartingGame;

    // announce new game
    announcement = std::make_shared<Announcement>("Game Starting", 300);
    announcement->AddSubtitle("Get Ready...");
  }

  if (status == Game::Status::StartingGame) {
    announcement->Update();
    if (announcement->IsComplete()) {
      announcement.reset();
      InitializeShip();
      InitializeAsteroids();
      InitializeShotVector();
      status = Game::Status::Playing;
      return; // required to avoid ghost collision issue
    }
  }

  if (status == Game::Status::BetweenRounds) {
    announcement->Update();
    if (announcement->IsComplete()) {
      announcement.reset();
      InitializeShip();
      InitializeAsteroids();
      status = Game::Status::Playing;
      return; // required to avoid ghost collission issue
    }
  }

  // move asteroids
  for (auto &asteroid: asteroids) {
    asteroid->Update();
  }

  if (ship && status == Game::Status::Playing) {
    ship->Update();
  }

  if (status == Game::Status::Explosion) {
    // update the exdplosion:
    explosion->Update();

    // check to see if the explosion has been competed
    if (explosion->IsComplete()) {
      // if so, set explostion to nullptr
      explosion.reset();
      // if no ships remaining, go to Game Over Status
      if (shipsRemaining <= 0) {
        announcement = std::make_shared<Announcement>("Game Over");
        announcement->AddSubtitle("Press Spacebar to Play Again");
        status = Game::Status::GameOver;
      }
      // else got to BetweenShips Status
      else {
        std::string message = std::to_string(shipsRemaining) + " Ship";
        message.append((shipsRemaining > 1) ? "s" : "");
        message.append(" Remaining");
        announcement = (std::make_shared<Announcement>(message, 300));
        announcement->AddSubtitle("Get Ready...");
        status = Game::Status::BetweenShips;
      }
    }
  }

  if (status == Game::Status::BetweenShips) {
      announcement->Update();
      if (announcement->IsComplete()) {
        announcement.reset();
        // need to use new thread to allow ship creation to wait for
        // clear zone (among asteroids) while continuing to update
        // asteroids in background:
        std::thread t(&Game::InitializeShip, this);
        t.detach(); // otherwise will get exception
        status = Game::Status::Playing;
        return;
      }
  }

  if (status == Game::Status::GameOver) {
    announcement->Update();
    if (announcement->IsComplete()) {
      announcement.reset();
      status = Game::Status::Terminated;
    }
  }

  // update shots (in any status)
  for (auto &shot: shots) {
    if (shot->IsActive()) shot->Update();
  }

  // Collision checks:
  std::vector<int> blastedAsteroidIds;

  for (auto &asteroid : asteroids) {
    for (auto &shot: shots) {
      if (shot->IsActive() && shot->IsColliding(*asteroid)) {
        shot->Deactivate();
        blastedAsteroidIds.push_back(asteroid->GetId());
      }
    }

    
    if (ship && ship->IsColliding(*asteroid)) {
      // Debugging for Ghost Collission Issue:
      // std::cout << "Ship collided with asteroid " << asteroid->GetId() << std::endl;
      // asteroid->MarkRed();
      // Point aCenter = asteroid->GetCenter();
      // Boundaries aBounds = asteroid->GetBoundaries();
      // std::cout << "Asteroid has center at " << aCenter.x << ", " << aCenter.y;
      // std::cout << " and boundaries of " << aBounds.top << ", " << aBounds.bottom << ", " << aBounds.left << ", " << aBounds.right << std::endl;
      
      // Point sCenter = ship->GetCenter();
      // Boundaries sBounds = ship->GetBoundaries();
      // std::cout << "Ship has center at " << sCenter.x << ", " << sCenter.y;
      // std::cout << " and boundaries of " << sBounds.top << ", " << sBounds.bottom << ", " << sBounds.left << ", " << sBounds.right << std::endl;

      shipsRemaining--;
      status = Game::Status::Explosion;
      explosion = std::make_shared<Explosion>(ship->GetCenter(), ship->GetRotation());
      ship.reset();
    }
  }

  // remove hit asteroids from vector:
  for (const int asteroidId : blastedAsteroidIds) {
    HandleAsteroidBlast(asteroidId);
  }

  // check to see if all asteroids have been destroyed
  if (status == Game::Status::Playing && asteroids.size() <= 0) {
    status = Game::Status::BetweenRounds;
    round++;
    announcement = (std::make_shared<Announcement>("Round " + std::to_string(round) + " Starting", 300));
    announcement->AddSubtitle("Get Ready...");
  }
}

void Game::InitializeShip() {
  // std::cout << "InitializeShip() called...." << std::endl;
  // rcheck to see if NoSpawnZone is clear:
  auto ftrNoSpawnZoneClear = std::async(&Game::NoSpawnZoneClear, this);

  // wait until e NoSpawnZone is clear:
  ftrNoSpawnZoneClear.get();
  
  ship = std::make_shared<Ship>(Point(kScreenWidth/2, kScreenHeight/2));
}

void Game::SetNoSpawnZone() {
  Point NSZcenter(kScreenWidth / 2, kScreenHeight / 2);
  
  std::vector<Point> NSZvertices{};
  NSZvertices.push_back(Point(-(kNoSpawnZoneWidth/2), (kNoSpawnZoneHeight/2)));
  NSZvertices.push_back(Point((kNoSpawnZoneWidth/2), (kNoSpawnZoneHeight/2)));
  NSZvertices.push_back(Point((kNoSpawnZoneWidth/2), (-kNoSpawnZoneHeight/2)));
  NSZvertices.push_back(Point((-kNoSpawnZoneWidth/2), (-kNoSpawnZoneHeight/2)));

  noSpawnZone = Polygon{NSZvertices, NSZcenter};
  noSpawnZone.SetBoundaries(kScreenHeight/2 - kNoSpawnZoneHeight/2, 
                            kScreenHeight/2 + kNoSpawnZoneHeight/2,
                            kScreenWidth/2 - kNoSpawnZoneWidth/2,
                            kScreenWidth/2 + kNoSpawnZoneWidth/2);
}

bool Game::NoSpawnZoneClear() {
  bool areaClear = false;

  while(!areaClear) {
    // set flag to true (will remain if no asteroids in area)
    areaClear = true;

    // lock while running through asteroid vector:
    std::unique_lock<std::mutex> uLock(_mutex);
    for (auto &asteroid : asteroids) {
      if (asteroid->IsColliding(noSpawnZone)) {
        if (!announcement) {
          // if can't spawn immediately, set announcement
          // to let player know we're waiting on safe zone
          announcement = std::make_shared<Announcement>(" ");
          announcement->AddSubtitle("waiting for clear spot to spawn...");
        }
        areaClear = false; // if asteroid in field, set flag to false
        break; // don't need to check remaining asteroids;
      }
    }
    uLock.unlock();
    // sleep a little to avoid constant running of this loop
    std::this_thread::sleep_for(std::chrono::milliseconds(150));
  }
  announcement.reset();
  return true;
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

void Game::InitializeAsteroids() {
  // set up random generators:
  std::uniform_int_distribution<int> distrX(0, kScreenWidth - kNoSpawnZoneWidth);
  std::uniform_int_distribution<int> distrY(0, kScreenHeight - kNoSpawnZoneHeight);
  std::uniform_int_distribution<int> distrRotation(0, 360);
  std::uniform_int_distribution<int> distrDirection(0, 360);
  
  for (size_t i = 0; i < kNumAsteroids + (round - 1) ; i++) {

    
    // generate random center
    int centerX = distrX(engine);
    int centerY = distrY(engine);

    // adjustmen to create "No Spawn Zone" around ship:
    if (centerX > (kScreenWidth/2 - kNoSpawnZoneWidth/2)) centerX += kNoSpawnZoneWidth;
    if (centerY > (kScreenHeight/2 - kNoSpawnZoneHeight/2)) centerY += kNoSpawnZoneHeight;


    Point center (centerX, centerY);

    // generate random Direction:
    int direction = distrDirection(engine);

    // generate random Rotation (orientation):
    int rotation = distrRotation(engine);

    std::shared_ptr<Asteroid> asteroid = std::make_shared<Asteroid>(center, direction, rotation, Asteroid::Size::kLarge);
    asteroids.emplace_back(std::move(asteroid));
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
    // generate rnadom orientation for child asteroid:
    std::uniform_int_distribution<int> distrRotation(0, 360);
    int rotation = distrRotation(engine);

    // initialize new Asteroid object and add to AsteroidVector:
    std::shared_ptr<Asteroid> childAsteroid = std::make_shared<Asteroid>(center, startingDirection + (i * directionChange), rotation, size);
    asteroids.emplace_back(std::move(childAsteroid));
  }
}

void Game::RemoveAsteroid(const int &asteroidId) {
  auto isDestroyed = [asteroidId](std::shared_ptr<Asteroid> ast){ return ast->GetId() == asteroidId; };
  asteroids.erase(std::remove_if(asteroids.begin(), asteroids.end(), isDestroyed));
}