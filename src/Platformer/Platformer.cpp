#include "Platformer/Platformer.h"

#include "Platformer/OpenGL.h"
#include "Platformer/window.h"
#include "Platformer/eventHandler.h"

#include "utils/Map.h"
#include "utils/Component.h"
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
    OpenGL::init(mShaderProgramme, mVAO, mVBO, mEBO);

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
    // Clear the OpenGL framebuffer with a background color
    glClearColor(30 / 255.0f, 150 / 255.0f, 100 / 255.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Bind and render the map (uses OpenGL textures and a VAO)
    map->drawMap();

    // Use your shader program (assumes you've created one)
    glUseProgram(mShaderProgramme);

    // Render entities not needed now also doesn't work
    /* auto view = Registry.view<Position, Sprite>();
    for (auto entity: view)
    {
        auto &pos    = view.get<Position>(entity);
        auto &sprite = view.get<Sprite>(entity);

        // Update position based on delta time
        pos.x += 100.0f * Time::deltaTime;
        pos.y += 100.0f * Time::deltaTime;

        // Bind the texture for the sprite
        glBindTexture(GL_TEXTURE_2D, sprite.textureID);

        // Calculate the model transformation matrix
        glm::mat4 model =
            glm::translate(glm::mat4(1.0f), glm::vec3(pos.x, pos.y, 0.0f));
        model = glm::scale(model, glm::vec3(sprite.width, sprite.height, 1.0f));

        // Pass the model matrix to the shader
        GLint modelLoc = glGetUniformLocation(mShaderProgramme, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

        glBindVertexArray(sprite.vaoID);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        glBindVertexArray(0);
    } */

    SDL_GL_SwapWindow(mWindow);
}

void Game::cleanup()
{
    OpenGL::close(mShaderProgramme, mVAO, mVBO, mEBO);
    Window::close(mWindow, mContext);  // Window should close last
    Registry.destroy(PlayerEntity);
    delete map;
}

}  // namespace Platformer