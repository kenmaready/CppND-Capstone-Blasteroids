#include "Explosion.h"
#include "Settings.h"
#include "utilities.h"

using utilities::radians;

Explosion::Explosion(Point center, int rotation): _center(center), _rotation(rotation) {

}

void Explosion::Update() {
    _counter++;
    double step = (Settings::kExplosionSpeed * 0.01);

    _lines[0]->A.x -= step;
    _lines[0]->A.y += step;
    _lines[0]->B.x -= step;
    _lines[0]->B.y += step;

    _lines[1]->A.x += step;
    _lines[1]->A.y += step;
    _lines[1]->B.x += step;
    _lines[1]->B.y += step;

    _lines[2]->A.x += step;
    _lines[2]->A.y -= step;
    _lines[2]->B.x += step;
    _lines[2]->B.y -+ step;

    _lines[3]->A.x -= step;
    _lines[3]->A.y -= step;
    _lines[3]->B.x -= step;
    _lines[3]->B.y -+ step;


    if (_counter > Settings::kExplosionDuration * .5) _color.a--;
    if (_counter > Settings::kExplosionDuration) _complete = true;
}

void Explosion::Draw(SDL_Renderer *ren) {
    for (Line *line : _lines) {
        std::cout << "Drawing Explosion Line..." << std::endl;

        int tempX1 = line->A.x;
        int tempY1 = line->A.y;
        int tempX2 = line->B.x;
        int tempY2 = line->B.y;

        int rotatedX1 = tempX1 * std::cos(radians(_rotation)) - tempY1 * std::sin(radians(_rotation));
        int rotatedY1 = tempX1 * std::sin(radians(_rotation)) + tempY1 * std::cos(radians(_rotation));

        int rotatedX2 = tempX2 * std::cos(radians(_rotation)) - tempY2 * std::sin(radians(_rotation));
        int rotatedY2 = tempX1 * std::sin(radians(_rotation)) + tempY2 * std::cos(radians(_rotation));

        int newX1 = _center.x - rotatedX1;
        int newY1 = _center.y - rotatedY1;
        int newX2 = _center.x - rotatedX2;
        int newY2 = _center.y - rotatedY2;

        lineRGBA(ren, newX1, newY1, newX2, newY2, _color.r, _color.g, _color.b, _color.a);
    }
}