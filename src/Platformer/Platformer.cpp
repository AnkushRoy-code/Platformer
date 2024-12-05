#include "Platformer/Platformer.h"

#include "Platformer/OpenGL.h"
#include "Platformer/window.h"
#include "Platformer/eventHandler.h"

#include "utils/Map.h"
#include "utils/Component.h"
#include "utils/TextureManager.h"
#include "utils/Time.h"

#include <SDL_video.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <entt/entt.hpp>

Platformer::Map *map;

entt::registry Registry;

auto PlayerEntity = Registry.create();

namespace Platformer
{

void Game::run()
{
    init();

    while (mIsRunning)
    {
        Time::updateDeltaTime();

        handleEvents();
        update();
        render();

        Time::capFPS();
    }

    cleanup();
}

void Game::init()
{
    Window::init("Platformer", mWindow, mContext);  // Window should init first
    OpenGL::init();

    mIsRunning = true;

    map = new Map();
    Registry.emplace<Position>(PlayerEntity, 10.0f, 10.0f);
    Registry.emplace<Sprite>(PlayerEntity, "res/images/enemy.png", 32, 32);

    Time::init();
}

void Game::handleEvents()
{
    Input::handleInputs(mIsRunning);
}

void Game::update() {}

void Game::render()
{
    glClear(GL_COLOR_BUFFER_BIT);

    map->drawMap();

    // Render entities not needed now also doesn't work
    auto view = Registry.view<Position, Sprite>();
    for (auto entity: view)
    {
        auto &pos    = view.get<Position>(entity);
        auto &sprite = view.get<Sprite>(entity);

        pos.x += 100.0f * Time::deltaTime();
        pos.y += 100.0f * Time::deltaTime();

        TextureManager::Draw(sprite.textureID,
                             SDL_FRect {pos.x, pos.y, sprite.width, sprite.height});
    }

    SDL_GL_SwapWindow(mWindow);
}

void Game::cleanup()
{
    OpenGL::close();
    Window::close(mWindow, mContext);  // Window should close last
    Registry.destroy(PlayerEntity);
    delete map;
}

}  // namespace Platformer
