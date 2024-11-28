
#include "OpenGL.h"
#include "utils/TextureManager.h"
#include <iostream>
#include <fstream>

namespace Platformer
{

void OpenGL::init(GLuint &ShaderProgramme,
                  GLuint &VAO,
                  GLuint &VBO,
                  GLuint &EBO)
{
    glViewport(0, 0, 30 * 32, 18 * 32);

    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Failed to initialize GLEW!\n";
        return;
    }

    std::cout << "OpenGL initialized successfully!\n";

    ShaderProgramme = CreateShaderProgram("res/shader/vertex.glsl",
                                          "res/shader/fragment.glsl");

    glUseProgram(ShaderProgramme);

    float vertices[] = {
        // Positions     // TexCoords
        -0.5f, -0.5f, 0.0f, 0.0f,  // Bottom-left
        0.5f,  -0.5f, 1.0f, 0.0f,  // Bottom-right
        0.5f,  0.5f,  1.0f, 1.0f,  // Top-right
        -0.5f, 0.5f,  0.0f, 1.0f   // Top-left
    };

    // Indices for two triangles
    unsigned int indices[] = {
        0, 1, 2,  // First triangle
        2, 3, 0   // Second triangle
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
                 GL_STATIC_DRAW);

    GLint posAttrib = glGetAttribLocation(ShaderProgramme, "aPosition");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float),
                          (void *)nullptr);

    GLint texAttrib = glGetAttribLocation(ShaderProgramme, "aTexCoord");
    glEnableVertexAttribArray(texAttrib);
    glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float),
                          (void *)(2 * sizeof(float)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void OpenGL::close(GLuint &ShaderProgramme,
                   GLuint &VAO,
                   GLuint &VBO,
                   GLuint &EBO)
{
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteVertexArrays(1, &VAO);
    glDeleteProgram(ShaderProgramme);
}

GLuint OpenGL::CreateShaderProgram(const char *vertexPath,
                                   const char *fragmentPath)
{
    std::string vertexCode   = ReadShaderFile(vertexPath);
    std::string fragmentCode = ReadShaderFile(fragmentPath);

    if (vertexCode.empty() || fragmentCode.empty())
    {
        std::cerr << "Failed to read shader files!\n";
        return 0;
    }

    GLuint vertexShader = CompileShader(GL_VERTEX_SHADER, vertexCode.c_str());
    GLuint fragmentShader =
        CompileShader(GL_FRAGMENT_SHADER, fragmentCode.c_str());

    if (vertexShader == 0 || fragmentShader == 0)
    {
        return 0;
    }

    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    GLint success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetProgramInfoLog(program, 512, nullptr, infoLog);
        std::cerr << "Shader Program Linking Error:\n" << infoLog << std::endl;
        glDeleteProgram(program);
        return 0;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return program;
}

GLuint OpenGL::CompileShader(GLenum type, const char *source)
{
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cerr << "Shader Compilation Error ("
                  << (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment")
                  << "):\n"
                  << infoLog << std::endl;
        glDeleteShader(shader);
        return 0;
    }

    return shader;
}

std::string OpenGL::ReadShaderFile(const char *filePath)
{
    std::ifstream file(filePath);
    if (!file.is_open())
    {
        std::cerr << "Failed to open shader file: " << filePath << std::endl;
        return "";
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}
}  // namespace Platformer
