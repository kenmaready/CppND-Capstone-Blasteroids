#include "Polygon.h"
#include "Settings.h"

using namespace Settings;

double radians(double num) {
    return num * (M_PI / 180);
}

Polygon::Polygon(std::vector<Point> vertices): _vertices(vertices) {
    _center = Point(0,0);
}

Polygon::Polygon(std::vector<Point> vertices, Point center): _vertices(vertices), _center(center) {
}

Polygon::~Polygon() {
}

Point Polygon::GetCenter() const {
    return _center;
}

std::vector<Point> Polygon::GetVertices() const {
    return this->_vertices;
}

int Polygon::GetNumberOfVertices() const {
    return this->_length;
}

int Polygon::GetRotation() const {
    return this->_rotation;
}

int Polygon::GetDirection() const {
    return this->_direction;
}

void Polygon::SetCenter(Point center) {
    this->_center = center;
}

void Polygon::Draw(SDL_Renderer *ren) {
  size_t num_vertices = _vertices.size();

  Sint16 vx[num_vertices];
  Sint16 vy[num_vertices];

  for (size_t i=0; i < num_vertices; i++) {
      int tempX = _vertices[i].x;
      int tempY = _vertices[i].y;

      int rotatedX = tempX * std::cos(radians(_rotation)) - tempY * std::sin(radians(_rotation));
      int rotatedY = tempX * std::sin(radians(_rotation)) + tempY * std::cos(radians(_rotation));

      vx[i] = _center.x - rotatedX;
      vy[i] = _center.y - rotatedY;
  }

  polygonRGBA(ren, vx, vy, 4, _color.r, _color.g, _color.b, _color.a);
  // ======================================================================
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