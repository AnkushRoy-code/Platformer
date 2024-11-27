#ifndef INCLUDE_WINDOW_WINDOW_H_
#define INCLUDE_WINDOW_WINDOW_H_

#include <SDL.h>
#include <string>

namespace Platformer
{

class Window
{
public:
    static bool init(const std::string &Title,
                             SDL_Window *&Window,
                             SDL_GLContext &Context);

    static void close(SDL_Window *&Window, SDL_GLContext &Context);
};

}  // namespace Platformer

#endif  // INCLUDE_WINDOW_WINDOW_H_
