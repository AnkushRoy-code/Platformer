#include "PhysicsMap.h"
#include "Platformer/Physics.h"
#include "box2d/box2d.h"
#include "box2d/id.h"
#include "box2d/math_functions.h"
#include "box2d/types.h"
#include <SDL_rect.h>
#include <vector>

void Platformer::PhysicsMap::init(
    const std::array<std::array<std::uint8_t, Platformer::TILESET_WIDTH>,
                     Platformer::TILESET_HEIGHT> &map)
{
    b2BodyId perimeterBodyId {};
    b2BodyDef perimeterBodyDef = b2DefaultBodyDef();
    perimeterBodyDef.position  = (b2Vec2) {0, 0};
    perimeterBodyId = b2CreateBody(Physics::worldId, &perimeterBodyDef);

    std::vector<b2Vec2> points(10);

    b2ChainDef perimeterChainDef = b2DefaultChainDef();
    perimeterChainDef.isLoop     = true;

    // auto type {0};
    // for (int row = 0; row < TILESET_HEIGHT; row++)
    // {
    //     for (int column = 0; column < TILESET_WIDTH; column++)
    //     {
    //         type = map[row][column];

    //         if (type != 2)
    //         {
    //             continue;
    //         }

    //         float x = column;
    //         float y = TILESET_HEIGHT - row - 1;

    //         b2Vec2 tmp {x, y};
    //         points.emplace_back(tmp);
    //     }
    // }
    b2Vec2 first {2, 2};
    b2Vec2 secnd {15, 2};
    b2Vec2 third {15, 4};
    b2Vec2 foruth {2, 4};

    points.emplace_back(first);
    points.emplace_back(secnd);
    points.emplace_back(third);
    points.emplace_back(foruth);

    perimeterChainDef.count  = points.size();
    perimeterChainDef.points = points.data();

    b2CreateChain(perimeterBodyId, &perimeterChainDef);
}

// 2 -> dirt
