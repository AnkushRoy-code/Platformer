#ifndef INCLUDE_UTILS_BACKGROUND_H_
#define INCLUDE_UTILS_BACKGROUND_H_

#include "Components/Component.h"
#include <filesystem>
#include <GL/glew.h>

namespace Platformer
{

class BackgroundCloud
{
public:
    explicit BackgroundCloud(const std::filesystem::path &path,
                             PositionComponent initialPos,
                             float Hspeed);

    void drawCloud();
    void updateCloud();

private:
    PositionComponent pos;
    GLuint texId;
    int texHeight {};
    int texWidth {};
    float horizontalSpeed;

    float width;
    float height;
};

}  // namespace Platformer

#endif  // INCLUDE_UTILS_BACKGROUND_H_
