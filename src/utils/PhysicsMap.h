#ifndef INCLUDE_UTILS_PHYSICSMAP_H_
#define INCLUDE_UTILS_PHYSICSMAP_H_

#include "utils/constants.h"
#include <array>
#include <cstdint>
namespace Platformer
{

class PhysicsMap
{
public:
    static void init(
        const std::array<std::array<std::uint8_t, Platformer::TILESET_WIDTH>,
                         Platformer::TILESET_HEIGHT> &map);

private:
};

}  // namespace Platformer

#endif  // INCLUDE_UTILS_PHYSICSMAP_H_
