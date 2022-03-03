#include <climits>
#include "Polygon.h"
#include "Settings.h"
#include "utilities.h"

using namespace Settings;
using utilities::radians;

int Polygon::IdCounter = 0;

Polygon::Polygon(std::vector<Point> vertices): _id(IdCounter++), _vertices(vertices) {
    _center = Point(0,0);
}

Polygon::Polygon(std::vector<Point> vertices, Point center): _id(IdCounter++), _vertices(vertices), _center(center) {
}

Polygon::~Polygon() {
}

void Polygon::SetCenter(Point center) {
    this->_center = center;
}

void Polygon::SetBoundaries(int top, int bottom, int left, int right) {
    _boundaries.top = top;
    _boundaries.bottom = bottom;
    _boundaries.left = left;
    _boundaries.right = right;
}

void Polygon::Draw(SDL_Renderer *ren) {
  size_t num_vertices = _vertices.size();

  Sint16 vx[num_vertices];
  Sint16 vy[num_vertices];

  int minX = INT_MAX;
  int maxX = INT_MIN;
  int minY = INT_MAX;
  int maxY = INT_MIN;

  for (size_t i=0; i < num_vertices; i++) {

      int tempX = _vertices[i].x;
      int tempY = _vertices[i].y;

      int rotatedX = tempX * std::cos(radians(_rotation)) - tempY * std::sin(radians(_rotation));
      int rotatedY = tempX * std::sin(radians(_rotation)) + tempY * std::cos(radians(_rotation));

      int newX = _center.x - rotatedX;
      int newY = _center.y - rotatedY;


      vx[i] = newX;
      vy[i] = newY;

      if (newX > maxX) maxX = newX;
      if (newX < minX) minX = newX;
      if (newY > maxY) maxY = newY;
      if (newY < minY) minY = newY;
  }

//   this->_boundaries.top = minY;
//   this->_boundaries.bottom = maxY;
//   this->_boundaries.left = minX;
//   this->_boundaries.right = maxX;

  SetBoundaries(minY, maxY, minX, maxX);

  polygonRGBA(ren, vx, vy, 4, _color.r, _color.g, _color.b, _color.a);
}

void Polygon::Update() {
    double tempX = this->_speed * .1;
    double tempY = this->_speed * .1;

    double rotatedX = tempX * std::cos(radians(_direction)) - tempY * std::sin(radians(_direction));
    double rotatedY = tempX * std::sin(radians(_direction)) + tempY * std::cos(radians(_direction));

    this->_center.x += rotatedX;
    if (this->_center.x > kScreenWidth) this->_center.x -= kScreenWidth;
    if (this->_center.x < 0) this->_center.x += kScreenWidth;

    this->_center.y += rotatedY;
    if (this->_center.y > kScreenHeight) this->_center.y -= kScreenHeight;
    if (this->_center.y < 0) this->_center.y += kScreenHeight;
}

void Polygon::ChangeDirection(int change) {
    this->_direction += change;
    if (this->_direction > 360) this->_direction -= 360;
    if (this->_direction < 0) this ->_direction += 360;
}

void Polygon::ChangeRotation(int change) {
    this->_rotation += change;
    if (this->_rotation > 360) this->_rotation -= 360;
    if (this->_rotation < 0) this ->_rotation += 360;
}

bool Polygon::IsColliding(Polygon &other) {

    // check horizontal (x-wise_ overlao):
    bool overlapsHorizontally = (this->_boundaries.right > other._boundaries.left) && (this->_boundaries.left < other._boundaries.right);
    bool overlapsVertically = (this->_boundaries.top < other._boundaries.bottom) && (this->_boundaries.bottom > other._boundaries.top);

    // if overlaps both ways, we have a collision:
    if (overlapsHorizontally & overlapsVertically) {
        return true;
    }
    return false;
}