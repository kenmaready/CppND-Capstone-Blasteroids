#include "Shot.h"
#include "utilities.h"

using utilities::radians;

Shot::Shot(double x, double y, int direction, bool active): _x(x), _y(y), _direction(direction - 135), _active(active) {
        Init();
}


void Shot::Draw(SDL_Renderer *ren) {
    if (_active == true) {
        filledCircleRGBA(ren, this->_x, this->_y, kShotRadius, _color.r, _color.g, _color.b, _color.a);

        this->_boundaries.top = this->_y - kShotRadius;
        this->_boundaries.bottom = this->_y + kShotRadius;
        this->_boundaries.left = this->_x - kShotRadius;
        this->_boundaries.right = this->_x + kShotRadius;
    }
}

void Shot::Update() {

    double tempX = this->_speed * .1;
    double tempY = this->_speed * .1;

    double rotatedX = tempX * std::cos(radians(_direction)) - tempY * std::sin(radians(_direction));
    double rotatedY = tempX * std::sin(radians(_direction)) + tempY * std::cos(radians(_direction));

    this->_x += rotatedX;
    if ((this->_x > kScreenWidth) | (this->_x < 0)) Deactivate();

    this->_y += rotatedY;
    if ((this->_y > kScreenHeight) | (this->_y < 0)) Deactivate();
}

void Shot::Activate(double x, double y, int direction) {
    this->_x = x;
    this->_y = y;

    this->Init();
    this->_direction = direction - 135;
    this->_active = true;
}

void::Shot::Init() {
    this->_color = {.r = 255, .g = 255, .b = 255, .a = 255 };

    this->_boundaries.top = this->_y - kShotRadius;
    this->_boundaries.bottom = this->_y + kShotRadius;
    this->_boundaries.left = this->_x - kShotRadius;
    this->_boundaries.right = this->_x + kShotRadius;
}