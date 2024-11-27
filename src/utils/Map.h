#ifndef INCLUDE_UTILS_MAP_H_
#define INCLUDE_UTILS_MAP_H_

#include <SDL.h>
#include <array>
#include <cstdint>
#include <GL/glew.h>


namespace Platformer
{

class Map
{
public:
    Map();
    ~Map() = default;

    void loadMap(const std::array<std::array<std::uint8_t, 30>, 18> &arr);
    void drawMap();

private:
    SDL_Rect dst {}, src {};

    GLuint dirt {};
    GLuint grass {};
    GLuint water {};

    std::array<std::array<std::uint8_t, 30>, 18> map {};
};

}  // namespace Platformer

#endif  // INCLUDE_UTILS_MAP_H_
