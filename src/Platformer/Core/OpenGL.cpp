#include "OpenGL.h"
#include "Utils/TextureManager.h"
#include "Platformer/Core/Window.h"
#include "Utils/Constants.h"
#include <GL/glu.h>
#include <iostream>

namespace Platformer
{

void OpenGL::init()
{
    glClearColor(30 / 255.0f, 150 / 255.0f, 100 / 255.0f, 1.0f);

    auto scale  = Window::WindowScale;
    auto Width  = TILESET_WIDTH * TILESET_SIZE * scale;
    auto Height = TILESET_HEIGHT * TILESET_SIZE * scale;

    glViewport(0, 0, Width, Height);

    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Failed to initialize GLEW!\n";
        return;
    }

    glDisable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, Width, 0, Height);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    double f = Window::WindowScale * TILESET_SIZE;
    glScalef(f, f, f);
}

void OpenGL::close() {}

}  // namespace Platformer
