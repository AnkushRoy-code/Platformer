#include "PhysicsMap.h"
#include "Platformer/Physics.h"
#include "box2d/box2d.h"
#include <SDL_rect.h>

void Platformer::PhysicsMap::init(
    const std::array<std::array<std::uint8_t, Platformer::TILESET_WIDTH>,
                     Platformer::TILESET_HEIGHT> &map)
{
    auto type {0};
    for (int row = 0; row < TILESET_HEIGHT; row++)
    {
        for (int column = 0; column < TILESET_WIDTH; column++)
        {
            type = map[row][column];

            if (type != 2)
            {
                continue;
            }

            SDL_FRect rect {};
            rect.x = column;
            rect.y =
                TILESET_HEIGHT - row
                - 1;  // Because co-ordinate system top is max and bottom is 0
            rect.w = 1;
            rect.h = 1;

            b2BodyDef staticBody = b2DefaultBodyDef();
            staticBody.position  = (b2Vec2) {rect.x, rect.y - 0.5f};

            b2BodyId staticBodyId   = b2CreateBody(Physics::worldId, &staticBody);
            // b2Polygon staticBodyBox = b2MakeBox(rect.w / 2, rect.h / 2);
            b2Polygon staticBodyBox = b2MakeBox(rect.w / 2, rect.h / 2);

            b2ShapeDef staticBodyShapeDef = b2DefaultShapeDef();
            b2CreatePolygonShape(staticBodyId, &staticBodyShapeDef, &staticBodyBox);

            // b2Polygon staticBodyBox =
            //     b2MakeRoundedBox((rect.w / 2) - 0.1, (rect.h / 2) - 0.1, 0.1);

            // b2ShapeDef staticBodyShapeDef = b2DefaultShapeDef();
            // staticBodyShapeDef.friction = 0.1;
            // b2CreatePolygonShape(staticBodyId, &staticBodyShapeDef,
            //                      &staticBodyBox);
        }
    }
}
// 2 -> dirt
