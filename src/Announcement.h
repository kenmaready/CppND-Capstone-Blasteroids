#ifndef _ANNOUNCEMENT_H_
#define _ANNOUNCEMENT_H_

#include <string>
#include <iostream>
#include "SDL.h"
#include <SDL2/SDL_ttf.h>

class Announcement {
    private:
        std::string _text;
        int _timer {0};
        int _duration;
        SDL_Surface* _surface;
        SDL_Rect _rectangle;
        SDL_Texture* _message;
        bool _complete {false};

        TTF_Font* Sans = TTF_OpenFont("assets/OpenSans-Regular.ttf", 24);
        SDL_Color White = {255, 255, 255, 255};

    public:
        Announcement(std::string text, int duration);

        void Update();
        void Draw(SDL_Renderer *ren);
        bool IsComplete() const { return _complete; }
};


#endif