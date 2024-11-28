#ifndef INCLUDE_PLATFORMER_OPENGL_H_
#define INCLUDE_PLATFORMER_OPENGL_H_

// I spent wayy to long documenting this...IDK why
#include "utils/TextureManager.h"
namespace Platformer
{
class OpenGL
{
public:
    /**
     * Initialises GLEW and creates the shader programme
     *
     * Creates Shaderprogramme, takes in GLuint ShaderProgramme, VAO, VBO, EBO as reference and does OpenGL stuff to them.
     *
     * @param ShaderProgramme GLuint& The shader Programme.
     * @param VAO GLuint& VAO the vertex array object.
     * @param VBO GLuint& why am I still writing these... aren't this obvious?
     * @param EBO Fuck you.
     * @return void returns nothing changes the parameters though.
     *
     * @example
     * // Description of my example.
     * GLuint ShaderProgramme{}, VAO{}, VBO{}, EBO{};
     * Platformer::OpenGL::init(ShaderProgramme, VAO, VBO, EBO);
     * // Now do other OpenGL stuff.
     */
    static void
        init(GLuint &ShaderProgramme, GLuint &VAO, GLuint &VBO, GLuint &EBO);

    /**
     * Closes the OpenGL context?
     *
     * Deletes the Buffers/Array/Programme
     *
     * @param ShaderProgramme GLuint& The shader Programme.
     * @param VAO GLuint& VAO the vertex array object.
     * @param VBO GLuint& why am I still writing these... aren't this obvious?
     * @param EBO Fuck you.
     * @return void returns nothing.
     *
     * @example
     * // Description of my example.
     * Write me later
     */
    static void
        close(GLuint &ShaderProgramme, GLuint &VAO, GLuint &VBO, GLuint &EBO);

private:
    static GLuint CreateShaderProgram(const char *vertexPath,
                                      const char *fragmentPath);
    static GLuint CompileShader(GLenum type, const char *source);
    static std::string ReadShaderFile(const char *filePath);
};

}  // namespace Platformer

#endif  // INCLUDE_PLATFORMER_OPENGL_H_
