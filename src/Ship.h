#ifndef SHIP_H
#define SHIP_H

#include <vector>
#include <chrono>
#include <memory>
#include "Polygon.h"
#include "Shot.h"

class Ship : public Polygon {
    public:
        enum class Direction { kUp, kDown, kLeft, kRight };
        
    private:
        Polygon thruster;
        SDL_Color thrusterColor;
        bool _thrusterEngaged{false};
        bool _isHit{false};
        std::chrono::steady_clock::time_point lastFire;

    public:
        Ship();
        Ship(Point center);

        void MarkAsHit() { _isHit = true; }
        bool IsHit() const { return _isHit; }
        void Thrust();
        void Unthrust() { _thrusterEngaged = false;}
        void Update() override;
        void Fire(std::shared_ptr<Shot> &shot);
        bool CanFire();
};

#endif