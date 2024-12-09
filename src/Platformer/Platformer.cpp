#include "Platformer/Platformer.h"

#include "Platformer/OpenGL.h"
#include "Platformer/window.h"
#include "Platformer/eventHandler.h"

#include "utils/Map.h"
#include "utils/Component.h"
#include "utils/TextureManager.h"
#include "utils/Time.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <entt/entt.hpp>
#include <box2d/box2d.h>

const auto M2P = 120;
const auto P2M = 1 / M2P;

namespace Platformer
{

entt::registry Game::Registry {};
entt::entity Game::PlayerEntity = Game::Registry.create();

b2WorldDef worldDef {};
b2WorldId worldId {};
b2BodyDef groundBodyDef {};
b2BodyId groundId {};
b2Polygon groundBox;
b2ShapeDef groundShapeDef;
b2BodyDef bodyDef;
b2BodyId bodyId;
b2Polygon dynamicBox;
b2ShapeDef shapeDef;
GLuint boxImg {};

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
    Window::init("Platformer");  // Window should init first
    OpenGL::init();
    mMap.init();

    mIsRunning = true;

    Registry.emplace<Position>(PlayerEntity, 10.0f, 10.0f);
    Registry.emplace<Sprite>(PlayerEntity, "res/images/enemy.png", 32, 32);

    Time::init();

    // Physics stuff
    worldDef               = b2DefaultWorldDef();  // The world
    worldDef.gravity       = (b2Vec2) {0.0f, -10.0f};
    worldId                = b2CreateWorld(&worldDef);
    groundBodyDef          = b2DefaultBodyDef();  // The static body ground
    groundBodyDef.position = (b2Vec2) {0.0f, -10.0f};
    groundId               = b2CreateBody(worldId, &groundBodyDef);
    groundBox              = b2MakeBox(100.0f, 10.0f);
    groundShapeDef         = b2DefaultShapeDef();
    b2CreatePolygonShape(groundId, &groundShapeDef, &groundBox);

    // The dynamic body(player)
    bodyDef           = b2DefaultBodyDef();
    bodyDef.type      = b2_dynamicBody;
    bodyDef.position  = (b2Vec2) {0.0f, 4.0f};
    bodyId            = b2CreateBody(worldId, &bodyDef);
    dynamicBox        = b2MakeBox(1.0f, 1.0f);
    shapeDef          = b2DefaultShapeDef();
    shapeDef.density  = 1.0f;
    shapeDef.friction = 0.3f;
    b2CreatePolygonShape(bodyId, &shapeDef, &dynamicBox);

    boxImg = TextureManager::LoadTexture("res/images/player.png");
}

void Game::handleEvents()
{
    Input::handleInputs(mIsRunning, bodyId);
}

void Game::update()
{
    float timeStep   = 1.0f / 60.0f;
    int subStepCount = 4;
    b2World_Step(worldId, timeStep, subStepCount);
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

        b2Vec2 position = b2Body_GetPosition(bodyId);

        pos.x = position.x * M2P;
        pos.y = position.y * M2P;

        TextureManager::Draw(
            sprite.textureID,
            SDL_FRect {pos.x, pos.y, sprite.width, sprite.height});
    }

    SDL_GL_SwapWindow(Window::window);
}

void Game::cleanup()
{
    b2DestroyWorld(worldId);

    OpenGL::close();
    Window::close();  // Window should close after opengl

    Registry.destroy(PlayerEntity);
}

}  // namespace Platformer
