#include "BackGround.h"
#include "Components/Component.h"
#include "Utils/PhysicsMap.h"
#include "Utils/TextureManager.h"
#include "Utils/Constants.h"
#include <iostream>
#include <memory>
#include "Utils/Map.h"

// clang-format off
std::array<std::array<std::uint8_t, Platformer::TILESET_WIDTH>, Platformer::TILESET_HEIGHT> lvl1 {{
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0, 1, 2, 2, 2, 2, 2, 2, 2,  2, 3, 0, 0, 0, 0, 0, 0, 0, },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0, 7, 8, 8, 8, 8, 8, 8, 8,  8, 9, 0, 0, 0, 0, 0, 1, 3, },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 7, 9, },
    { 1, 2, 2, 3, 0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, },
    { 7, 8, 8, 9, 0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 1, 2, 3, 0, 0, 0, 0,  0, 0, 0, 0, 1, 2, 3, 0, 0, },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 7, 8, 9, 0, 0, 0, 0,  0, 0, 0, 0, 7, 8, 9, 0, 0, },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, },
    { 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, },
    { 0, 0, 0, 0, 0, 0, 0, 0, 7, 8, 9, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, },
    { 0, 0, 1, 2, 3, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, },
    { 0, 0, 7, 8, 9, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 1,  2, 2, 2, 2, 2, 2, 2, 2, 3, },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,  2, 2, 2, 2, 2, 2, 2, 2, 11, 5, 5, 5, 5, 5, 5, 5, 5, 6, },
    { 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 11, 5, 5, 5, 5, 5, 5, 5, 5, 5,  5, 5, 5, 5, 5, 5, 5, 5, 6, },
    { 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,  8, 8, 8, 8, 8, 8, 8, 8, 8,  8, 8, 8, 8, 8, 8, 8, 8, 9, }
}}
;

// clang-format on

namespace Platformer
{

void Map::init()
{

    // clang-format off
    bottomLeft = TextureManager::LoadTexture("res/images/Tileset/BottomLeft.png");
    bottomMiddle = TextureManager::LoadTexture("res/images/Tileset/BottomMiddle.png");
    bottomRight = TextureManager::LoadTexture("res/images/Tileset/BottomRight.png");
    middleLeft = TextureManager::LoadTexture("res/images/Tileset/MiddleLeft.png");
    middleMiddle = TextureManager::LoadTexture("res/images/Tileset/MiddleMiddle.png");
    middleRight = TextureManager::LoadTexture("res/images/Tileset/MiddleRight.png");
    topLeft = TextureManager::LoadTexture("res/images/Tileset/TopLeft.png");
    topMiddle = TextureManager::LoadTexture("res/images/Tileset/TopMiddle.png");
    topRight = TextureManager::LoadTexture("res/images/Tileset/TopRight.png");

    otherThing = TextureManager::LoadTexture("res/images/Tileset/OtherThing.png");
    otherThing2 = TextureManager::LoadTexture("res/images/Tileset/OtherThing2.png");

    BackGroundImg = TextureManager::LoadTexture("res/images/BackGround/BackGround.png");
    // clang-format on

    if (!bottomLeft || !bottomMiddle || !bottomRight || !middleLeft
        || !middleMiddle || !middleRight || !topLeft || !topMiddle || !topRight
        || !otherThing || !otherThing2)
    {
        std::cerr << "Error: Failed to load one or more textures!\n";
    }

    // Temporary
    loadMap(lvl1);

    float horizontalSpeed = 0.3;

    clouds.emplace_back(std::make_unique<BackgroundCloud>(
        "res/images/Clouds/Cloud1.png", PositionComponent {1, 5},
        horizontalSpeed));

    horizontalSpeed = -0.25;

    clouds.emplace_back(std::make_unique<BackgroundCloud>(
        "res/images/Clouds/Cloud2.png", PositionComponent {25, 4},
        horizontalSpeed));

    clouds.emplace_back(std::make_unique<BackgroundCloud>(
        "res/images/Clouds/Cloud3.png", PositionComponent {40, 4},
        horizontalSpeed));

    horizontalSpeed = 0.25;

    clouds.emplace_back(std::make_unique<BackgroundCloud>(
        "res/images/Clouds/Cloud4.png", PositionComponent {-10, 4},
        horizontalSpeed));

    PhysicsMap::init(lvl1);
}

void Map::loadMap(const std::array<std::array<std::uint8_t, TILESET_WIDTH>,
                                   TILESET_HEIGHT> &arr)
{
    map = arr;
}

void Map::drawMap()
{
    SDL_FRect reckt = {0, 0, TILESET_WIDTH, TILESET_HEIGHT};

    TextureManager::Draw(BackGroundImg, reckt);

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

            // Because co-ordinate system top is max and bottom is 0
            rect.y = TILESET_HEIGHT - row - 1;

            rect.x = column;
            rect.w = 1;  // 1 -> 32px
            rect.h = 1;

            // clang-format off
            switch (type) {
                case 0: break;
                case 1: TextureManager::Draw(topLeft, rect); break;
                case 2: TextureManager::Draw(topMiddle, rect); break;
                case 3: TextureManager::Draw(topRight, rect); break;
                case 4: TextureManager::Draw(middleLeft, rect); break;
                case 5: TextureManager::Draw(middleMiddle, rect); break;
                case 6: TextureManager::Draw(middleRight, rect); break;
                case 7: TextureManager::Draw(bottomLeft, rect); break;
                case 8: TextureManager::Draw(bottomMiddle, rect); break;
                case 9: TextureManager::Draw(bottomRight, rect); break;
                case 10: TextureManager::Draw(otherThing, rect); break;
                case 11: TextureManager::Draw(otherThing2, rect); break;
                default: break;
            }
            //clang-format on
        }
    }

    for (auto &cloud: clouds)
    {
        cloud->updateCloud();
        cloud->drawCloud();
    }
}

}  // namespace Platformer
