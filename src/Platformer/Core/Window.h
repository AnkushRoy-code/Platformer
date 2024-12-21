#ifndef INCLUDE_WINDOW_WINDOW_H_
#define INCLUDE_WINDOW_WINDOW_H_

#include <SDL.h>
#include <string>

namespace Platformer
{

class Window
{
public:
    /// Initialises SDL_OpenGL window.
    static bool init(const std::string &Title);
    static void close();

    static SDL_Window *window;
    static SDL_GLContext glContext;

    static double WindowScale;

private:
    /// @return Float returns the scale factor by which the window sshould
    /// be scaled so that the thing is at its maximum.
    static float getScaleFactor();
};

}  // namespace Platformer

#endif  // INCLUDE_WINDOW_WINDOW_H_
