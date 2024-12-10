#ifndef INCLUDE_INPUT_EVENTHANDLER_H_
#define INCLUDE_INPUT_EVENTHANDLER_H_

#include "box2d/id.h"
namespace Platformer
{
class Input
{
public:
    static void handleInputs(bool &isRunning, b2BodyId playerId);
};

}  // namespace Platformer

#endif  // INCLUDE_INPUT_EVENTHANDLER_H_
