#ifndef _POLYGON_H_
#define _POLYGON_H_

#include <iostream>
#include <vector>
#include <cmath>
#include "SDL.h"
#include "SDL2_gfxPrimitives.h"
// #include "renderer.h"

class Point {
    public:
        Point() {};
        Point(double x, double y) { this->x = x; this->y = y; };
        double x, y;
};

struct Boundaries {
    int top;
    int bottom;
    int left;
    int right;
};

class Polygon {
    protected:
        std::vector<Point> _vertices;
        Point _center;
        int _length;
        int _rotation;
        int _direction;
        int _speed;
        Boundaries boundaries;
        SDL_Color _color = {.r = 255, .g = 255, .b = 255, .a = 255 };

    public:
        Polygon() {};
        Polygon(std::vector<Point> vertices);
        Polygon(std::vector<Point> vertices, Point center);
        ~Polygon();
        Point GetCenter() const;
        std::vector<Point> GetVertices() const;
        int GetNumberOfVertices() const;
        int GetRotation() const;
        int GetDirection() const;

        void SetCenter(Point center);
        void Draw(SDL_Renderer *ren);
        void Update();
        void rotate();
        void ChangeDirection(int change);
        void ChangeRotation(int change);
        bool IsColliding(Polygon &other);
};


#endif