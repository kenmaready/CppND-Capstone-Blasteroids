#include "Polygon.h"
#include "Settings.h"
#include <climits>

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

  this->boundaries.top = minY;
  this->boundaries.bottom = maxY;
  this->boundaries.left = minX;
  this->boundaries.right = maxX;

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
    // get bounding edges of this object
    // int myWidthHalf = (boundaries.right - boundaries.left) / 2;
    // int myHeightHalf = (boundaries.bottom - boundaries.top) / 2;
    // Point myCenter = this->GetCenter();

    // int myRightEdge = myCenter.x + myWidthHalf;
    // int myLeftEdge = myCenter.x - myWidthHalf;
    // int myTopEdge = myCenter.y - myHeightHalf;
    // int myBottomEdge = myCenter.y + myHeightHalf;


    // // get bounding edges of other object
    // int yourWidthHalf = (other.boundaries.right - other.boundaries.left) / 2;
    // int yourHeightHalf = (other.boundaries.bottom - other.boundaries.height) / 2;
    // Point yourCenter = other.GetCenter();

    // int yourRightEdge = yourCenter.x + yourWidthHalf;
    // int yourLeftEdge = yourCenter.x - yourWidthHalf;
    // int yourTopEdge = yourCenter.y - yourHeightHalf;
    // int yourBottomEdge = yourCenter.y + yourHeightHalf;

    // check horizontal (x-wise_ overlao):
    bool overlapsHorizontally = (this->boundaries.right > other.boundaries.left) && (this->boundaries.left < other.boundaries.right);
    bool overlapsVertically = (this->boundaries.top < other.boundaries.bottom) && (this->boundaries.bottom > other.boundaries.top);

    // if overlaps both ways, we have a collision:
    if (overlapsHorizontally & overlapsVertically) {
        this->_color = {.r = 255, .g = 0, .b = 0, .a = 255 };
        other._color = {.r = 0, .g = 0, .b = 255, .a = 255 };
        // std::cout << "This: " << this->boundaries.top << ", " << this->boundaries.bottom << ", " << this->boundaries.left << ", " << this->boundaries.right << std::endl;
        // std::cout << "Other: " << other.boundaries.top << ", " << other.boundaries.bottom << ", " << other.boundaries.left << ", " << other.boundaries.right << std::endl;
        return true;
    }
    return false;
}