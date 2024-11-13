#include "Platformer.h"

#include "window/window.h"
#include "input/eventHandler.h"
#include "Platformer/GameObject.h"

#include <SDL_render.h>

Platformer::GameObject *player;

namespace Platformer
{
SDL_Rect dst;

void Game::init()
{
    Window::init("Platformer", mWindow, mRenderer);  // Window should init first

    mIsRunning = true;

    player = new GameObject("res/images/enemy.png", mRenderer, 20, 50);
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
    SDL_SetRenderDrawColor(mRenderer, 30, 150, 100, 255);
    SDL_RenderClear(mRenderer);
    player->render();
    SDL_RenderPresent(mRenderer);
}

void Game::clean()
{
    Window::close(mWindow, mRenderer);  // Window should close last
    delete player;
}

}  // namespace Platformer
