#include "Announcement.h"
#include "Settings.h"


using namespace Settings;

Announcement::Announcement(std::string text, int duration): _text(text), _duration(duration) {    

    if (!Sans) std::cout << "Unable to load font:\n" << "SDL2_TTF Error: " << TTF_GetError() << std::endl;

    _rectangle.w = 18 * text.length();
    _rectangle.h = 24;

    _rectangle.x = (kScreenWidth / 2) - (_rectangle.w / 2);
    _rectangle.y = (kScreenHeight / 2) - (_rectangle.h / 2);

    std::cout << "Announcement Created. _rectangle defined." << std::endl;
}

void Announcement::Update() {
    _timer ++;
    if (_timer >= _duration) _complete = true;
}

void Announcement::Draw(SDL_Renderer *ren) {
    _surface = TTF_RenderText_Solid(Sans, _text.c_str(), White);
    if (!_surface) {
        std::cout << "Unable to render text surface:\n" << "SDL2_ttf Error: " << SDL_GetError() << std::endl;
    }

    _message = SDL_CreateTextureFromSurface(ren, _surface);
    if (!_message) {
        std::cout << "Unable to render texture from surface:\n" << "SDL2_ttf Error: " << SDL_GetError() << std::endl;
    }
    
    SDL_FreeSurface(_surface);
    SDL_RenderCopy(ren, _message, NULL, &_rectangle);
    SDL_DestroyTexture(_message);
}
