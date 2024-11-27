#ifndef INCLUDE_PLATFORMER_OPENGL_H_
#define INCLUDE_PLATFORMER_OPENGL_H_

#include "utils/TextureManager.h"
namespace Platformer
{
class OpenGL
{
public:
    static void
        init(GLuint &ShaderProgramme, GLuint &VAO, GLuint &VBO, GLuint &EBO);
    static void
        close(GLuint &ShaderProgramme, GLuint &VAO, GLuint &VBO, GLuint &EBO);

    static GLuint CreateShaderProgram(const char *vertexPath,
                                      const char *fragmentPath);

private:
    static GLuint CompileShader(GLenum type, const char *source);
    static std::string ReadShaderFile(const char *filePath);
};

}  // namespace Platformer

#endif  // INCLUDE_PLATFORMER_OPENGL_H_
