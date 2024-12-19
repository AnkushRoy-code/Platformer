#ifndef INCLUDE_UTILS_PHYSICSMAP_H_
#define INCLUDE_UTILS_PHYSICSMAP_H_

#include "box2d/id.h"
#include "box2d/math_functions.h"
#include "utils/constants.h"
#include <SDL_video.h>
#include <array>
#include <cstdint>
#include <vector>
namespace Platformer
{

class PhysicsMap
{
public:
    static void init(
        const std::array<std::array<std::uint8_t, Platformer::TILESET_WIDTH>,
                         Platformer::TILESET_HEIGHT> &map);

private:
    static std::vector<b2Vec2>
        getSurroundingPoints(const std::vector<b2Vec2> &points);

    static std::vector<b2Vec2>
        getOddDuplicates(const std::vector<b2Vec2> &points);

    template<size_t WIDTH, size_t HEIGHT>
    static std::vector<std::vector<b2Vec2>> findClusters(
        const std::array<std::array<std::uint8_t, WIDTH>, HEIGHT> &grid);
    static void initPerimeterBodyId();

    static b2BodyId perimeterBodyId;
};

}  // namespace Platformer

#endif  // INCLUDE_UTILS_PHYSICSMAP_H_
