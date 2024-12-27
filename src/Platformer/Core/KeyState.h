#ifndef INCLUDE_PLATFORMER_KEYSTATE_H_
#define INCLUDE_PLATFORMER_KEYSTATE_H_

#include <bitset>

namespace Platformer::KeyState
{

enum keyCodes
{
    SPACE,
    RIGHT,
    LEFT,
    SHIFT,
    DASH,
    R_MOUSEBUTTON,
    L_MOUSEBUTTON,
    M_MOUSEBUTTON,
};

extern std::bitset<8> keyState; // If you change the size of this bitset here don't forget to change it in keyState.cpp too

void keyPress(int keyCode);
void keyRelease(int keyCode);

}  // namespace Platformer::KeyState

#endif  // INCLUDE_PLATFORMER_KEYSTATE_H_
