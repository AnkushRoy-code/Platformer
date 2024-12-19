#include "utils/PhysicsMap.h"
#include "utils/TextureManager.h"
#include "utils/constants.h"
#include <iostream>
#include <utils/Map.h>

// clang-format off
std::array<std::array<std::uint8_t, Platformer::TILESET_WIDTH>, Platformer::TILESET_HEIGHT> lvl1 {{
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, },
    { 0, 0, 2, 2, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, },
    { 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, },
    { 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, },
    { 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 2, 2, 2, 2, },
    { 1, 1, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, },
    { 1, 1, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, },
    { 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, },
    { 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, },
    { 1, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, },
    { 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, },
    { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, },
    { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, },
    { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, }
}}
;

// clang-format on

namespace Platformer
{

void Map::init()
{
    dirt  = TextureManager::LoadTexture("res/images/dirt.png");
    grass = TextureManager::LoadTexture("res/images/grass.png");
    water = TextureManager::LoadTexture("res/images/water.png");

    if (!water || !grass || !dirt)
    {
        std::cerr << "Error: Failed to load one or more textures!\n";
    }

    // Temporary
    loadMap(lvl1);
    PhysicsMap::init(lvl1);
}

void Map::loadMap(const std::array<std::array<std::uint8_t, TILESET_WIDTH>,
                                   TILESET_HEIGHT> &arr)
{
    map = arr;
}

void Map::drawMap()
{
    // Co-ordinate system is different for this game is like this:
    //  (0, max)         (max, max)
    //      . _______________ .
    //      | \               |
    //      |    \            |
    //      |       \         |
    //      |          \      |
    //      |             \   |
    //      |               \ |
    //      . _______________ .
    //   (0, 0)           (max, 0)
    //
    // IDK this info might help

    int type {};
    for (int row = 0; row < TILESET_HEIGHT; row++)
    {
        for (int column = 0; column < TILESET_WIDTH; column++)
        {
            type = map[row][column];

            rect.x = column;
            rect.y =
                TILESET_HEIGHT - row
                - 1;  // Because co-ordinate system top is max and bottom is 0
            rect.w = 1;
            rect.h = 1;

            switch (type)
            {
                case 0:
                    TextureManager::Draw(water, rect);
                    break;
                case 1:
                    TextureManager::Draw(grass, rect);
                    break;
                case 2:
                    TextureManager::Draw(dirt, rect);
                    break;
                default:
                    break;
            }
        }
    }
}

}  // namespace Platformer
