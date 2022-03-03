#include "Ship.h"
#include "settings.h"

using namespace Settings;

Ship::Ship(Point center) {
    std::vector<Point> vertices;
    vertices.push_back(Point(-15, -20));
    vertices.push_back(Point(0, 20));
    vertices.push_back(Point(15, -20));
    vertices.push_back(Point(0, -14));
    this->_vertices = std::move(vertices);

    this->_center = center;
    this->_rotation = 0;
    this->_direction = 0;
    this->_speed = 0;
}

Ship::Ship(): Ship(Point(kScreenWidth/2, kScreenHeight/2)) {}