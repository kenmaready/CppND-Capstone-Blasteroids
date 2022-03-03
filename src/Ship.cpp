#include "Ship.h"
#include <algorithm>
#include "settings.h"
#include "utilities.h"

using namespace Settings;
using utilities::radians;

Ship::Ship(Point center) {
    std::vector<Point> vertices;
    vertices.push_back(Point(-15, -20));
    vertices.push_back(Point(0, 20));
    vertices.push_back(Point(15, -20));
    vertices.push_back(Point(0, -14));
    this->_vertices = std::move(vertices);

    this->_center = center;
    this->_rotation = 0;
    this->_direction = -135;
    this->_speed = 0;
}

Ship::Ship(): Ship(Point(kScreenWidth/2, kScreenHeight/2)) {}

void Ship::Thrust() {
    // the physics of the ship I Just made up and experimented with
    // in a real game, I would use more tried and true game physics

    int deltaDirection = (_rotation - 135) - _direction;
    double thrustMomentumFactor = std::cos(radians(deltaDirection));

    _speed = std::max(0.0, std::min(_speed + (3.0 * thrustMomentumFactor), static_cast<double>(kShipMaxSpeed)));

    // calculate direction based on rotation with adjustment for momentum:
    double directionMomentumFactor = (1 / (_speed + 1));
    _direction += deltaDirection * directionMomentumFactor;
    _thrusterEngaged = true;
}

void Ship::Update() {
    if (_speed > 0) _speed = std::max(_speed - .1, 0.0);
    Polygon::Update();
}

void Ship::Fire(std::shared_ptr<Shot> &shot) {
    shot->Activate(_center.x, _center.y, _rotation, _speed);
    lastFire = std::chrono::steady_clock::now();
}

bool Ship::CanFire() {
    return std::chrono::steady_clock::now() > lastFire + std::chrono::milliseconds(kMsBetweenShots);
};