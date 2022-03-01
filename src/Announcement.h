#ifndef _ANNOUNCEMENT_H_
#define _ANNOUNCEMENT_H_

#include <string>
#include <iostream>
#include "SDL.h"
#include <SDL2/SDL_ttf.h>
#include "Settings.h"

#define FONT_PATH "assets/OpenSans-Regular.ttf"

using namespace Settings;

class Announcement {
    private:
        std::string _text;
        int _timer {0};
        int _duration;
        int _fontSize = kAnnouncementFontSize;
        SDL_Surface* _surface;
        SDL_Rect _rectangle;
        SDL_Texture* _message;
        TTF_Font* Sans = TTF_OpenFont(FONT_PATH, _fontSize);

        std::string _subtitle;
        int _subfontSize;
        SDL_Surface* _subsurface;
        SDL_Rect _subrectangle;
        SDL_Texture* _submessage;
        TTF_Font* subSans = TTF_OpenFont(FONT_PATH, _fontSize / 2);

        SDL_Color White = {255, 255, 255, 255};
        bool _complete {false};

    public:        
        Announcement(std::string text, int duration);

        void AddSubtitle(std::string text);
        void Update();
        void Draw(SDL_Renderer *ren);
        bool IsComplete() const { return _complete; }
};


#endif