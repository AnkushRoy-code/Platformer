#ifndef INCLUDE_WINDOW_WINDOW_H_
#define INCLUDE_WINDOW_WINDOW_H_

#include <SDL.h>
#include <string>

namespace Platformer
{

class Window
{
public:
    static bool init(const std::string &title,
              SDL_Window *&Window);
    static void close(SDL_Window *&Window);
};

}  // namespace Platformer::Window

#endif  // INCLUDE_WINDOW_WINDOW_H_
