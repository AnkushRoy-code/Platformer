#include "Platformer.h"

#include "window/window.h"
#include "input/eventHandler.h"
#include "Platformer/GameObject.h"
#include "utils/Map.h"

#include <SDL_render.h>

Platformer::GameObject *player;
Platformer::Map *map;

namespace Platformer
{

SDL_Renderer *Game::mRenderer = nullptr;

void Game::init()
{
    Window::init("Platformer", mWindow);  // Window should init first

    mIsRunning = true;

    player = new GameObject("res/images/enemy.png", 20, 50);
    map = new Map();
}

void Game::handleEvents()
{
    Input::handleInputs(mIsRunning);
}

void Game::update()
{
    player->update();
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
    delete player;
    delete map;
}

}  // namespace Platformer
