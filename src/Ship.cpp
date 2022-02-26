#include "Ship.h"
#include "Settings.h"

using namespace Settings;

Ship::Ship() {
    std::vector<Point> vertices;
    vertices.push_back(Point(-15, -20));
    vertices.push_back(Point(0, 20));
    vertices.push_back(Point(15, -20));
    vertices.push_back(Point(0, -14));
    this->_vertices = std::move(vertices);


    this->_center = Point(kScreenWidth/2, kScreenHeight/2);
    std::cout << "Center of ship at (" << this->_center.x << ", " << this->_center.y << ")" << std::endl;
    this->_rotation = 0;
    this->_direction = 0;
    this->_speed = 0;
}