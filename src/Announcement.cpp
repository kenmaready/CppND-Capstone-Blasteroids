#include "Announcement.h"
#include "Settings.h"


using namespace Settings;

Announcement::Announcement(std::string text, int duration): _text(text), _duration(duration) {    

    if (!Sans) std::cout << "Unable to load font:\n" << "SDL2_TTF Error: " << TTF_GetError() << std::endl;

    _rectangle.w = (_fontSize * .75) * text.length();
    _rectangle.h = _fontSize;

    _rectangle.x = (kScreenWidth / 2) - (_rectangle.w / 2);
    _rectangle.y = (kScreenHeight / 2) - (_rectangle.h / 2);

}

void Announcement::AddSubtitle(std::string text) {
    _subtitle = text;
    _subfontSize = _fontSize / 2;

    _subrectangle.w = (_subfontSize * .75) * text.length();
    _subrectangle.h = _subfontSize + 5;
    _subrectangle.x = (kScreenWidth / 2) - (_subrectangle.w / 2);
    _subrectangle.y = (kScreenHeight / 2) + ( _subfontSize / 2);

    // move  main title up a little:
    _rectangle.y -= _fontSize / 2;
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

    if (!_subtitle.empty()) {
        _subsurface = TTF_RenderText_Solid(subSans, _subtitle.c_str(), White);
        if (!_surface) {
            std::cout << "Unable to render subtitle surface:\n" << "SDL2_ttf Error: " << SDL_GetError() << std::endl;
        }

        _submessage = SDL_CreateTextureFromSurface(ren, _subsurface);
        if (!_submessage) {
            std::cout << "Unable to render subtitle texture from surface:\n" << "SDL2_ttf Error: " << SDL_GetError() << std::endl;
        }
        
        SDL_FreeSurface(_subsurface);
        SDL_RenderCopy(ren, _submessage, NULL, &_subrectangle);
        SDL_DestroyTexture(_submessage);
    }
}
