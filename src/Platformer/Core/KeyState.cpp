#include "Platformer/Core/KeyState.h"

namespace Platformer::KeyState
{

std::bitset<7> keyState;

void keyPress(int keyCode)
{
    keyState[keyCode] = true;
}

void keyRelease(int keyCode)
{
    keyState[keyCode] = false;
}

}  // namespace Platformer::KeyState
