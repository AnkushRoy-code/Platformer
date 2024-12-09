#include "Platformer/Platformer.h"

#include "Platformer/OpenGL.h"
#include "Platformer/window.h"
#include "Platformer/eventHandler.h"
#include "Platformer/Physics.h"

#include "utils/Map.h"
#include "utils/Component.h"
#include "utils/TextureManager.h"
#include "utils/Time.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <entt/entt.hpp>
#include <box2d/box2d.h>
#include <iostream>

const auto M2P = 120;
const auto P2M = 1 / M2P;

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
b2BodyId bodyId;
void Game::init()
{
    Window::init("Platformer");  // Window should init first
    OpenGL::init();

    Registry.emplace<Position>(PlayerEntity, 10.0f, 10.0f);
    Registry.emplace<Sprite>(PlayerEntity, "res/images/enemy.png", 1, 1);

    // Utils
    mMap.init();
    Time::init();
    Physics::init();

    b2BodyDef bodyDef = b2DefaultBodyDef();
    bodyDef.type      = b2_dynamicBody;
    bodyDef.position  = (b2Vec2) {0.0f, 4.0f};
    bodyId   = b2CreateBody(Physics::worldId, &bodyDef);

    b2Polygon dynamicBox = b2MakeBox(1.0f, 1.0f);
    b2ShapeDef shapeDef  = b2DefaultShapeDef();
    shapeDef.density     = 1.0f;
    shapeDef.friction    = 0.3f;
    b2CreatePolygonShape(bodyId, &shapeDef, &dynamicBox);

    mIsRunning = true;
    printDependencyVersions();
}

void Game::handleEvents()
{
    Input::handleInputs(mIsRunning);
}

void Game::update()
{
    Physics::update();
}

void Game::render()
{
    glClear(GL_COLOR_BUFFER_BIT);
    mMap.drawMap();

    // Render entities not needed now also doesn't work
    auto view = Registry.view<Position, Sprite>();
    for (auto entity: view)
    {
        auto &pos    = view.get<Position>(entity);
        auto &sprite = view.get<Sprite>(entity);

        pos.x = b2Body_GetPosition(bodyId).x;
        pos.y = b2Body_GetPosition(bodyId).y;

        TextureManager::Draw(
            sprite.textureID,
            SDL_FRect {pos.x, pos.y, sprite.width, sprite.height});
    }

    SDL_GL_SwapWindow(Window::window);
}

void Game::cleanup()
{
    OpenGL::close();
    Window::close();  // Window should close after opengl

    Registry.destroy(PlayerEntity);
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

    // OpenGL GLU Version
    const char *gluVersion =
        reinterpret_cast<const char *>(gluGetString(GLU_VERSION));
    std::cout << std::left << std::setw(20) << "OpenGL::GLU"
              << (gluVersion ? gluVersion : "Unknown") << std::endl;

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
