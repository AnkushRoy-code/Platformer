#ifndef INCLUDE_UTILS_MAP_H_
#define INCLUDE_UTILS_MAP_H_

#include <SDL.h>
#include <array>
#include <cstdint>
namespace Platformer
{

class Map
{
public:
    Map();
    ~Map() = default;

    void loadMap(const std::array<std::array<std::uint8_t, 25>, 20> &arr);
    void drawMap();

private:
    SDL_Rect dst {}, src {};

    SDL_Texture *dirt {};
    SDL_Texture *grass {};
    SDL_Texture *water {};

    std::array<std::array<std::uint8_t, 25>, 20> map {};
};

}  // namespace Platformer

#endif  // INCLUDE_UTILS_MAP_H_
