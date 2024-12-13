#include "keyState.h"

namespace Platformer::KeyState
{

std::bitset<256> keyState;

void keyPress(int keyCode)
{
    keyState[keyCode] = true;
}

void keyRelease(int keyCode)
{
    keyState[keyCode] = false;
}

[[nodiscard]] bool isKeyPressed(int keyCode)
{
    return keyState[keyCode];
}

}  // namespace Platformer::KeyState
