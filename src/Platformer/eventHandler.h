#ifndef INCLUDE_INPUT_EVENTHANDLER_H_
#define INCLUDE_INPUT_EVENTHANDLER_H_

#include "box2d/id.h"
#include "entt/entity/fwd.hpp"
namespace Platformer
{
class Input
{
public:
    static void handleInputs(bool &isRunning, const b2BodyId &playerBody);
};

}  // namespace Platformer

#endif  // INCLUDE_INPUT_EVENTHANDLER_H_
