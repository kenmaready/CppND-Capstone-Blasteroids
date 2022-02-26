#include "Shot.h"

double radians2(double num) {
    return num * (M_PI / 180);
}

void Shot::Draw(SDL_Renderer *ren) {
    if (_active == true) {
        filledCircleRGBA(ren, this->_x, this->_y, 3, 255, 255, 255, 255);
    }
}

void Shot::Update() {

    double tempX = this->_speed * .1;
    double tempY = this->_speed * .1;

    double rotatedX = tempX * std::cos(radians2(_direction)) - tempY * std::sin(radians2(_direction));
    double rotatedY = tempX * std::sin(radians2(_direction)) + tempY * std::cos(radians2(_direction));

    this->_x += rotatedX;
    if ((this->_x > kScreenWidth) | (this->_x < 0)) Deactivate();

    this->_y += rotatedY;
    if ((this->_y > kScreenHeight) | (this->_y < 0)) Deactivate();
}

void Shot::Activate(double x, double y, int direction) {
    this->_x = x;
    this->_y = y;
    this->_direction = direction - 135;
    this->_active = true;
}