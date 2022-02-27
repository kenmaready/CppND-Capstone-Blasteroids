#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#include "SDL.h"
#include "SDL2_gfxPrimitives.h"
#include "Polygon.h"

struct Line {
    Point A;
    Point B;
};


class Explosion {
    private:
        // starting point for ship explosion lines:
        Line line1{Point(-15, -20), Point(0, 20)};
        Line line2{Point(0, 20), Point(15, -20)};
        Line line3{Point(15, -20), Point(0, -14)};
        Line line4{Point(0, -14), Point(-15, -20)};

        // container for handles to lines for easy looping:
        Line *_lines[4] = {&line1, &line2, &line3, &line4};
        
        Point _center;
        int _rotation;
        int _counter{0};
        bool _complete{false};
        SDL_Color _color = {.r = 255, .g = 255, .b = 255, .a = 255 };

    public:
        Explosion(Point center, int rotation);

        void Update();
        void Draw(SDL_Renderer *ren);
        bool IsComplete() const { return _complete; }
};

#endif
