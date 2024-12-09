#include "eventHandler.h"

#include <SDL_keycode.h>
#include <entt/entt.hpp>
#include <SDL_events.h>
#include <box2d/box2d.h>

namespace Platformer
{
void Input::handleInputs(bool &isRunning, const b2BodyId &playerBody)
{
    SDL_Event event;

    const float speed = 5.0f;  // Walking speed

    while (SDL_PollEvent(&event) != 0)
    {
        if (event.type == SDL_QUIT)
        {
            isRunning = false;
        }

        else if (event.type == SDL_KEYDOWN)
        {
            switch (event.key.keysym.sym)
            {
                case SDLK_a:
                case SDLK_LEFT:
                    b2Body_SetLinearVelocity(
                        playerBody,
                        b2Vec2 {-speed,
                                b2Body_GetLinearVelocity(playerBody).y});
                    break;
                case SDLK_d:
                case SDLK_RIGHT:
                    b2Body_SetLinearVelocity(
                        playerBody,
                        b2Vec2 {speed, b2Body_GetLinearVelocity(playerBody).y});
                    break;
                case SDLK_SPACE:
                    b2Body_ApplyLinearImpulseToCenter(
                        playerBody,
                        b2Vec2 {b2Body_GetLinearVelocity(playerBody).x, 15},
                        true);
                    break;

                default:
                    break;
            }
        }
        if (event.type == SDL_KEYUP)
        {
            switch (event.key.keysym.sym)
            {
                case SDLK_LEFT:
                case SDLK_RIGHT:
                    // Stop horizontal movement when the key is released
                    b2Body_SetLinearVelocity(
                        playerBody,
                        b2Vec2 {0, b2Body_GetLinearVelocity(playerBody).y});
                    break;
            }
        }
    }
}

}  // namespace Platformer
