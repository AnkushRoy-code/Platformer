#include "OpenGL.h"
#include "utils/TextureManager.h"
#include <GL/glu.h>
#include <iostream>

namespace Platformer
{

void OpenGL::init()
{
    glClearColor(30 / 255.0f, 150 / 255.0f, 100 / 255.0f, 1.0f);

    constexpr auto scale  = 1.3333;
    constexpr auto Width  = 30 * 32 * scale;
    constexpr auto Height = 18 * 32 * scale;

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

    glScalef(1.33f, 1.33f, 1.33f);

    std::cout << "OpenGL initialized successfully!\n";
}

void OpenGL::close() {}

}  // namespace Platformer
