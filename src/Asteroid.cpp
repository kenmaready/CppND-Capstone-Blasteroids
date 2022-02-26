#include <random>
#include "Settings.h"
#include "Asteroid.h"

using namespace Settings;

#define ASTEROID_POINTS 6;

Asteroid::Asteroid() {
    // genrate the verteices for the asteroid object:
    std::vector<Point> vertices;
    vertices.push_back(Point(0, 20));
    vertices.push_back(Point(20, 0));
    vertices.push_back(Point(0, -20));
    vertices.push_back(Point(-20, 0));
    this->_vertices = std::move(vertices);

    // set up random generators:
    std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_int_distribution<int> distrX(0, kScreenWidth);
    std::uniform_int_distribution<int> distrY(0, kScreenHeight);
    std::uniform_int_distribution<int> distrRotation(0, 360);
    std::uniform_int_distribution<int> distrDirection(0, 360);
    
    // generate random center:
    int centerX = distrX(eng);
    int centerY = distrY(eng);
    this->_center = Point(centerX, centerY);

    // generate random Rotation (orientation):
    this->_rotation = distrRotation(eng);

    // generate random Direction:
    this->_direction = distrDirection(eng);

    // set speed:
    this->_speed = kAsteroidSpeed;


    std::cout << "New Asteroid will be centered at (" << centerX << ", " << centerY << ")..." << std::endl;
}

// void Asteroid::draw() {
//     std::cout << "Drawing Asteroid with center at (" << this->_center.x << ", " << this->_center.y << ")..." << std::endl;
// }