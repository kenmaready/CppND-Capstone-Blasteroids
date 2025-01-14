#ifndef _SETTINGS_H_
#define _SETTINGS_H_

#include <cstddef>
  
namespace Settings {

    const std::size_t kFramesPerSecond{60};
    const std::size_t kMsPerFrame{1000 / kFramesPerSecond};
    const std::size_t kScreenWidth{800};
    const std::size_t kScreenHeight{800};
    const std::size_t kGridWidth{40};
    const std::size_t kGridHeight{40};


    const std::size_t kNumAsteroids{6};
    const std::size_t kAsteroidSpeed(4);
    const int kNoSpawnZoneWidth{200};
    const int kNoSpawnZoneHeight(200);

    const std::size_t kNumShips(3);
    const int kShipRotationSpeed(10);
    const int kShipMaxSpeed(20);

    const int kShotSpeed(10);
    const int kNumShots(128);
    const int kMsBetweenShots(75);
    const int kShotRadius(3);

    const std::size_t kExplosionDuration(300);
    const std::size_t kExplosionSpeed(20);

    const std::size_t kAnnouncementFontSize(36);
};

#endif