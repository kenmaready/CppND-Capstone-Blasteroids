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
    private:
        // tried to avoid using Ids, but discovered in eliminating and
        // adding asteroids in the gam's asteroids vector, it was 
        // needed to avoid much more complicated solutions to avoid
        // issued caused by  of manipulating a vector while acucling 
        // through it.
        static int IdCounter;
        int _id;

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
        Polygon(): _id(IdCounter++) {}; // give object an _id and then advance static counter;
        Polygon(std::vector<Point> vertices);
        Polygon(std::vector<Point> vertices, Point center);
        ~Polygon();

        // getters
        int GetId() const { return _id; }
        Point GetCenter() const { return _center; }
        std::vector<Point> GetVertices() const { return _vertices; }
        int GetNumberOfVertices() const { return _length; }
        int GetRotation() const { return _rotation; }
        int GetDirection() const { return _direction; }

        // setters
        void SetCenter(Point center);
        
        // nehaviora methods:
        void Draw(SDL_Renderer *ren);
        void Update();
        void rotate();
        void ChangeDirection(int change);
        void ChangeRotation(int change);
        bool IsColliding(Polygon &other);
};


#endif