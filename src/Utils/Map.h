#ifndef INCLUDE_UTILS_MAP_H_
#define INCLUDE_UTILS_MAP_H_

#include "Utils/Constants.h"
#include <SDL.h>
#include <array>
#include <cstdint>
#include <GL/glew.h>


namespace Platformer
{

class Map
{
public:

    void init();
    
    /// Loads an array of ints that should be 30 width and 18 hegiht!
    void loadMap(const std::array<std::array<std::uint8_t, TILESET_WIDTH>, TILESET_HEIGHT> &arr);
    void drawMap();

private:
    SDL_FRect rect {};

    GLuint dirt {};
    GLuint grass {};
    GLuint water {};

    std::array<std::array<std::uint8_t, 30>, TILESET_HEIGHT> map {};
};

}  // namespace Platformer

#endif  // INCLUDE_UTILS_MAP_H_
