
#ifndef INCLUDE_PLATFORMER_COMPONENT_H_
#define INCLUDE_PLATFORMER_COMPONENT_H_

namespace Platformer
{

struct PositionComponent
{
public:
    int x {}, y {};
    void update();
};

}  // namespace Platformer

#endif  // INCLUDE_PLATFORMER_COMPONENT_H_
