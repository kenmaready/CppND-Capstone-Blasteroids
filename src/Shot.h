#ifndef _SHOT_H_
#define _SHOT_H_

#include <cmath>
#include "SDL.h"
#include "SDL2_gfxPrimitives.h"
#include "Settings.h"

using namespace Settings;

class Shot {
    private:
        double _x;
        double _y;
        int _direction;
        int _speed{kShotSpeed};

    public:
        Shot(double x, double y, int direction): _x(x), _y(y), _direction(direction - 135) {}
        void Draw(SDL_Renderer *ren);
        void Update();

        int GetDirection() const { return _direction; }
};

#endif