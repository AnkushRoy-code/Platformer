#include "Platformer/Core/KeyState.h"

namespace Platformer::KeyState
{

std::bitset<8> keyState;

void keyPress(int keyCode)
{
    keyState[keyCode] = true;
}

void keyRelease(int keyCode)
{
    keyState[keyCode] = false;
}

}  // namespace Platformer::KeyState
