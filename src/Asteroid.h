#ifndef _ASTEROID_H_
#define _ASTEROID_H_

#include <vector>
#include "Polygon.h"

class Asteroid : public Polygon {
    public:
        enum class Size { kSmall, kMedium, kLarge };

        Asteroid(Asteroid::Size size);
        Asteroid(Point center, int direction, Asteroid::Size size);
        Asteroid::Size GetSize() const { return _size; }
        bool IsDestroyed() { return _destroyed; }
        void MarkDestroyed() { _destroyed = true; }

    private:
        Asteroid::Size _size;
        bool _destroyed {false};
};

#endif