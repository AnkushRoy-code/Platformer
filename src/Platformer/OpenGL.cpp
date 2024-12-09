#include "OpenGL.h"
#include "utils/TextureManager.h"
#include "Platformer/window.h"
#include "utils/constants.h"
#include <GL/glu.h>
#include <iostream>

namespace Platformer
{

void OpenGL::init()
{
    glClearColor(30 / 255.0f, 150 / 255.0f, 100 / 255.0f, 1.0f);

    constexpr auto scale  = 1.3333;
    constexpr auto Width  = TILESET_WIDTH * TILESET_SIZE * scale;
    constexpr auto Height = TILESET_HEIGHT * TILESET_SIZE * scale;

    glViewport(0, 0, Width, Height);

    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Failed to initialize GLEW!\n";
        return;
    }

    glDisable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, Width, Height, 0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    double f = Window::WindowScale * TILESET_SIZE;
    glScalef(f, f, f);

}

void OpenGL::close() {}

}  // namespace Platformer
