#ifndef INCLUDE_PLATFORMER_PHYSICS_H_
#define INCLUDE_PLATFORMER_PHYSICS_H_

#include "box2d/box2d.h"

namespace Platformer
{

class Physics
{
public:
    static void init();
    static void close();
    static void update();

    static b2WorldId worldId;
};

}  // namespace Platformer

#endif  // INCLUDE_PLATFORMER_PHYSICS_H_
