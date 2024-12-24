#include "Platformer/Core/Platformer.h"

#include "Platformer/Core/OpenGL.h"
#include "Platformer/Player/Player.h"
#include "Platformer/Core/Window.h"
#include "Platformer/Core/EventHandler.h"
#include "Platformer/Physics/Physics.h"

#include "box2d/types.h"
#include "Utils/Map.h"
#include "Utils/Components/Component.h"
#include "Utils/TextureManager.h"
#include "Utils/Time.h"

#include "debugHelp/box2dDebugDraw.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <entt/entt.hpp>
#include <box2d/box2d.h>
#include <iostream>

// const auto M2P = 120;
// const auto P2M = 1 / M2P;

namespace Platformer
{

entt::registry Game::Registry {};
entt::entity Game::PlayerEntity = Game::Registry.create();

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

void printDependencyVersions();  // Forward declaration
void Game::init()
{
    Window::init("Platformer");  // Window should init first
    OpenGL::init();

    Registry.emplace<PositionComponent>(PlayerEntity, 10.0f,
                               10.0f);  // doesn't matter will change soon
    Registry.emplace<SpriteComponent>(PlayerEntity, "res/images/flatColour.png", 1, 1);

    // Utils
    Time::init();
    Physics::init();

    mMap.init();  // Should Be initialised after Physics because it has physics
                  // tiles

    mPlayer.init();  // Also is using physics

    mIsRunning = true;
    printDependencyVersions();

    Debug::g_draw.m_debugDraw.drawShapes           = true;
    Debug::g_draw.m_debugDraw.drawJoints           = false;
    Debug::g_draw.m_debugDraw.drawJointExtras      = false;
    Debug::g_draw.m_debugDraw.drawAABBs            = false;
    Debug::g_draw.m_debugDraw.drawMass             = false;
    Debug::g_draw.m_debugDraw.drawContacts         = false;
    Debug::g_draw.m_debugDraw.drawGraphColors      = false;
    Debug::g_draw.m_debugDraw.drawContactNormals   = false;
    Debug::g_draw.m_debugDraw.drawContactImpulses  = false;
    Debug::g_draw.m_debugDraw.drawFrictionImpulses = false;
    
    Debug::g_draw.Create();
}

void Game::handleEvents()
{
    Input::handleInputs(mIsRunning);
}

void Game::update()
{
    Physics::update();
    mPlayer.update();
}

void Game::render()
{
    glClear(GL_COLOR_BUFFER_BIT);
    mMap.drawMap();

    // Render entities not needed now also doesn't work
    auto view = Registry.view<PositionComponent, SpriteComponent>();
    for (auto entity: view)
    {
        auto &pos    = view.get<PositionComponent>(entity);
        auto &sprite = view.get<SpriteComponent>(entity);

        pos.x = b2Body_GetPosition(Player::playerBody).x;
        pos.y = b2Body_GetPosition(Player::playerBody).y;

        // printf("%4.2f %4.2f\n", pos.x, pos.y );

        TextureManager::Draw(
            sprite.textureID,
            SDL_FRect {pos.x - 0.5f, pos.y - 0.5f, sprite.width, sprite.height});
    }
    b2World_Draw(Physics::worldId, &Debug::g_draw.m_debugDraw);
    Debug::g_draw.Flush();

    SDL_GL_SwapWindow(Window::window);
}

void Game::cleanup()
{
    OpenGL::close();
    Window::close();  // Window should close after opengl

    Registry.destroy(PlayerEntity);
    mPlayer.close();

    Debug::g_draw.Destroy();
    Physics::close();

}

//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//

// Other useless stuff
std::string getFormattedVersion(const SDL_version &version);

// You do not judge!
void printDependencyVersions()
{
    std::cout << std::left << std::setw(20) << "Dependency" << std::setw(15)
              << "Version" << std::endl;
    std::cout << std::string(35, '-') << std::endl;

    // SDL2 Version
    SDL_version compiled, linked;
    SDL_VERSION(&compiled);
    SDL_GetVersion(&linked);

    std::cout << std::left << std::setw(20) << "SDL2 (Compiled)"
              << getFormattedVersion(compiled) << std::endl;
    std::cout << std::left << std::setw(20) << "SDL2 (Linked)"
              << getFormattedVersion(linked) << std::endl;

    // OpenGL Version
    const char *glVersion =
        reinterpret_cast<const char *>(glGetString(GL_VERSION));
    std::cout << std::left << std::setw(20) << "OpenGL::GL"
              << (glVersion ? glVersion : "Unknown") << std::endl;

    // GLM Version
    std::cout << std::left << std::setw(20) << "glm::glm" << GLM_VERSION_MAJOR
              << "." << GLM_VERSION_MINOR << "." << GLM_VERSION_PATCH
              << std::endl;

    // Box2D Version
    b2Version b2version = b2GetVersion();
    std::cout << std::left << std::setw(20) << "Box2D" << b2version.major << "."
              << b2version.minor << "." << b2version.revision << std::endl;
}

std::string getFormattedVersion(const SDL_version &version)
{
    return std::to_string(version.major) + "." + std::to_string(version.minor)
           + "." + std::to_string(version.patch);
}

}  // namespace Platformer
