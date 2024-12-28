#ifndef INCLUDE_PLAYER_PLAYERSTATE_H_
#define INCLUDE_PLAYER_PLAYERSTATE_H_

#include "Utils/Components/Animation.h"
#include "box2d/math_functions.h"
namespace Platformer
{

enum States
{
    Idling,
    Walking,
    Falling,
    Jumping,
    DoubleJumping,
};

class PlayerState
{
public:
    void init();
    void update(bool InAir);
    void render();

private:
    States currentState = States::Idling;

    void updateIdling();
    void updateWalking();
    void updateFalling();
    void updateJumping();
    void updateDoubleJumping();

    void updateMovement();

    bool inAir          = false;
    bool doubleJumpAble = true;
    b2Vec2 vel {};
    b2Vec2 gravity {};
    float force = 15;

    Animations mAnimations;
};

}  // namespace Platformer

#endif  // INCLUDE_PLAYER_PLAYERSTATE_H_
