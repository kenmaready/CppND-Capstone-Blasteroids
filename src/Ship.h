#ifndef SHIP_H
#define SHIP_H

#include <vector>
#include <iostream>
#include "Polygon.h"

class Ship : public Polygon {
    public:
        enum class Direction { kUp, kDown, kLeft, kRight };
        
    private:
        bool _isHit{false};

    public:
        Ship();
        Ship(Point center);

        void MarkAsHit() { _isHit = true; }
        bool IsHit() const { return _isHit; }
};

#endif