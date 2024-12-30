#ifndef INCLUDE_UTILS_MAP_H_
#define INCLUDE_UTILS_MAP_H_

#include "BackGround.h"
#include "Utils/Constants.h"
#include <SDL.h>
#include <array>
#include <cstdint>
#include <GL/glew.h>

#include <vector>

namespace Platformer
{

class Map
{
public:
    void init();

    /// Loads an array of ints that should be 30 width and 18 hegiht!
    void loadMap(const std::array<std::array<std::uint8_t, TILESET_WIDTH>,
                                  TILESET_HEIGHT> &arr);
    void drawMap();

private:
    SDL_FRect rect {};

    GLuint bottomLeft;
    GLuint bottomMiddle;
    GLuint bottomRight;
    GLuint middleLeft;
    GLuint middleMiddle;
    GLuint middleRight;
    GLuint topLeft;
    GLuint topMiddle;
    GLuint topRight;

    GLuint otherThing;
    GLuint otherThing2;

    GLuint BackGroundImg;

    std::array<std::array<std::uint8_t, 30>, TILESET_HEIGHT> map {};
    std::vector<std::unique_ptr<BackgroundCloud>> clouds;
};

}  // namespace Platformer

#endif  // INCLUDE_UTILS_MAP_H_
