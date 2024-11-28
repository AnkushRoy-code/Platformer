
/// Needs work.
#ifndef INCLUDE_PLATFORMER_COMPONENT_H_
#define INCLUDE_PLATFORMER_COMPONENT_H_

#include "utils/TextureManager.h"
#include <SDL.h>
#include <filesystem>

namespace Platformer
{
/// Position in 2D space
struct Position
{
    float x, y;
};

struct Sprite
{
    Sprite(const std::filesystem::path &Path, int Width, int Height);
    ~Sprite();
    int width {}, height {};
    GLuint vaoID {}, vboID {}, eboID {}, textureID {};
    void initialise();
    void deinitialise();
};

}  // namespace Platformer

#endif  // INCLUDE_PLATFORMER_COMPONENT_H_
