#ifndef INCLUDE_INPUT_EVENTHANDLER_H_
#define INCLUDE_INPUT_EVENTHANDLER_H_

#include <SDL_events.h>
#include <functional>

namespace Platformer
{
class Input
{
public:
    static void handleInputs(bool &isRunning);
private:
    static void changeKeyState(const std::function<void(int)> &function, const SDL_Event &event);
    static void changeCursorState(const std::function<void(int)> &function, const SDL_Event &event);
};

}  // namespace Platformer

#endif  // INCLUDE_INPUT_EVENTHANDLER_H_
