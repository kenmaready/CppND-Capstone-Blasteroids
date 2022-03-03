#ifndef _SHOT_H_
#define _SHOT_H_

#include <cmath>
#include "SDL.h"
#include "SDL2_gfxPrimitives.h"
#include "Polygon.h"
#include "settings.h"

using namespace Settings;

class Shot : public Polygon {
    private:
        double _x;
        double _y;
        int _direction;
        int _speed{kShotSpeed};
        bool _active;

    public:
        Shot(double x, double y, int direction, bool active=true);
        void Draw(SDL_Renderer *ren);
        void Update();

        int GetDirection() const { return _direction; }
        bool IsActive() const { return _active; }
        void Activate() { _active = true; }
        void Activate(double x, double y, int direction, double speed);
        void Deactivate();
        void Init();
};

#endif