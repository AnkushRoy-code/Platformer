#include "Platformer.h"

#include "window/window.h"
#include "input/eventHandler.h"
#include "Platformer/GameObject.h"
#include "utils/Map.h"
#include "entt/entt.hpp"
#include "utils/Component.h"

#include <SDL_render.h>
#include <iostream>

Platformer::GameObject *player;
Platformer::Map *map;

entt::registry Registry;

auto PlayerEntity = Registry.create();

namespace Platformer
{

SDL_Renderer *Game::mRenderer = nullptr;

PositionComponent playerComponent;

void Game::init()
{
    Window::init("Platformer", mWindow);  // Window should init first

    mIsRunning = true;

    player = new GameObject("res/images/enemy.png", 20, 50);
    map    = new Map();
    Registry.emplace<PositionComponent>(PlayerEntity, 10, 10);

    playerComponent = Registry.get<PositionComponent>(PlayerEntity);
    playerComponent.x = 300;
    playerComponent.y = 690;
}

void Game::handleEvents()
{
    Input::handleInputs(mIsRunning);
}

void Game::update()
{
    player->update();
    playerComponent.update();
    std::cout << "Player x: " << playerComponent.x
              << " y: " << playerComponent.y << "\n";
}

void Game::render()
{
    // SDL_SetRenderDrawColor(mRenderer, 30, 150, 100, 255);
    SDL_RenderClear(mRenderer);
    map->drawMap();
    player->render();
    SDL_RenderPresent(mRenderer);
}

void Game::clean()
{
    Window::close(mWindow);  // Window should close last
    Registry.destroy(PlayerEntity);
    delete player;
    delete map;
}

}  // namespace Platformer
