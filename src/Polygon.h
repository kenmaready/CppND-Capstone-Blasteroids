#ifndef _POLYGON_H_
#define _POLYGON_H_

#include <iostream>
#include <vector>
#include "SDL.h"
#include "SDL2_gfxPrimitives.h"
#include "renderer.h"

class Point {
    public:
        Point() {};
        Point(int x, int y) { this->x = x; this->y = y; };
        int x, y;
};

class Polygon {
    private:
        Point *_vertices;
        Point _center;
        int _length;
        SDL_Color _color = {.r = 255, .g = 255, .b = 255, .a = 255 };

    public:
        Polygon() {};
        Polygon(std::vector<Point> vertices);
        ~Polygon();
        Point GetCenter();
        Point *GetVertices();
        int GetNumberOfVertices();
        void draw(SDL_Renderer *ren);
};


#endif