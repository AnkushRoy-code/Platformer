#ifndef INCLUDE_PLAYER_PLAYERSTATE_H_
#define INCLUDE_PLAYER_PLAYERSTATE_H_

#include "Platformer/Core/Music.h"
#include "Utils/Components/Animation.h"
#include "box2d/math_functions.h"
namespace Platformer
{

// enum class States
enum States
{
    IDLING,
    WALKING,
    FALLING,
    JUMPING,
    DOUBLE_JUMPING,
};

// enum class SFX
enum SFX
{
    JUMP,
    DJUMP,
    RUN,
};

class PlayerState
{
public:
    void init();
    void update(bool InAir);
    void render();
    void close();

private:
    States currentState = States::IDLING;

    void updateIdling();
    void updateWalking();
    void updateFalling();
    void updateJumping();
    void updateDoubleJumping();

    void updateMovement();

    void fallingCondition();

    bool dirLeft        = true;
    bool inAir          = false;
    bool doubleJumpAble = true;
    b2Vec2 vel {};
    b2Vec2 gravity {};
    float force = 15;
    float impulse = 3.5;

    Animations mAnimations;
    SFXs mSFXes;
};

}  // namespace Platformer

#endif  // INCLUDE_PLAYER_PLAYERSTATE_H_
