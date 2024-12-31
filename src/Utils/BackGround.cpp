#include "Utils/BackGround.h"

#include "Utils/Constants.h"
#include "Utils/TextureManager.h"
#include "Utils/Time.h"

namespace Platformer
{

BackgroundCloud::BackgroundCloud(const std::filesystem::path &path,
                                 PositionComponent initialPos,
                                 float Hspeed) :
    pos(initialPos), horizontalSpeed(Hspeed)
{
    texId = TextureManager::LoadTexture(path);

    glBindTexture(GL_TEXTURE_2D, texId);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &texWidth);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &texHeight);
    glBindTexture(GL_TEXTURE_2D, 0);

    float ratio = static_cast<float>(texWidth) / static_cast<float>(texHeight);
    width       = 8;
    height      = width / ratio;
}

void BackgroundCloud::updateCloud()
{
    pos.x += horizontalSpeed * Time::deltaTime();
}

void BackgroundCloud::drawCloud()
{

    SDL_FRect rect = {pos.x, static_cast<float>(TILESET_HEIGHT) - pos.y, width,
                      height};

    TextureManager::Draw(texId, rect);
}

}  // namespace Platformer
