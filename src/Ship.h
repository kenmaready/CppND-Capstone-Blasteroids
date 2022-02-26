#ifndef SHIP_H
#define SHIP_H

#include <vector>
#include <iostream>
#include "Polygon.h"

class Ship : public Polygon {
    public:
        enum class Direction { kUp, kDown, kLeft, kRight };
        
        Ship();
};

#endif