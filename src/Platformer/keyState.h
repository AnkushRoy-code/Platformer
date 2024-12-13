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
    R_MOUSEBUTTON,
    L_MOUSEBUTTON,
    M_MOUSEBUTTON,
};

extern std::bitset<256> keyState;

void keyPress(int keyCode);
void keyRelease(int keyCode);
[[nodiscard]] bool isKeyPressed(int keyCode);

}  // namespace Platformer::KeyState

#endif  // INCLUDE_PLATFORMER_KEYSTATE_H_
