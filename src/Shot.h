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
        bool _active;

    public:
        Shot(double x, double y, int direction, bool active=true): _x(x), _y(y), _direction(direction - 135), _active(active) {}
        void Draw(SDL_Renderer *ren);
        void Update();

        int GetDirection() const { return _direction; }
        bool IsActive() const { return _active; }
        void Activate() { _active = true; }
        void Activate(double x, double y, int direction);
        void Deactivate() { _active = false; }
};

#endif