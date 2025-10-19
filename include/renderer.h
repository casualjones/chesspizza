#pragma once

#include <string>
#include <vector>
#include <memory>
#include <iostream>

// Try to include OpenGL headers in order of preference
#ifdef __has_include
  #if __has_include(<GL/glew.h>)
    #include <GL/glew.h>
    #define GLEW_AVAILABLE
  #elif __has_include(<GL/gl.h>)
    #include <GL/gl.h>
    #include <GL/glext.h>
    #define OPENGL_AVAILABLE
  #endif
  
  #if __has_include(<SDL2/SDL.h>)
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_opengl.h>
    #define SDL2_AVAILABLE
  #elif __has_include(<SDL.h>)
    #include <SDL.h>
    #include <SDL_opengl.h>
    #define SDL_AVAILABLE
  #endif
  
  #if __has_include(<glm/glm.hpp>)
    #include <glm/glm.hpp>
    #include <glm/gtc/matrix_transform.hpp>
    #include <glm/gtc/type_ptr.hpp>
    #define GLM_AVAILABLE
  #endif
#else
  // Fallback for older compilers
  #include <GL/gl.h>
  #include <GL/glext.h>
  #define OPENGL_AVAILABLE
#endif

// Fallback type definitions if headers not found
#ifndef GL_VERSION
typedef unsigned int GLuint;
typedef unsigned int GLenum;
typedef int GLint;
typedef float GLfloat;
typedef unsigned char GLboolean;
typedef int GLsizei;
typedef void GLvoid;
#endif

namespace ChessPizza {

#ifdef GLM_AVAILABLE
using Mat4 = glm::mat4;
using Vec3 = glm::vec3;
using Vec4 = glm::vec4;
#else
// Simple matrix/vector types if GLM not available
struct Vec3 { float x, y, z; };
struct Vec4 { float x, y, z, w; };
struct Mat4 { float data[16]; };
#endif

class Shader {
public:
    Shader(const std::string& vertex_source, const std::string& fragment_source);
    ~Shader();
    
    void use();
    GLuint get_program_id() const { return program_id_; }
    
    // Uniform setters
    void set_uniform(const std::string& name, float value);
    void set_uniform(const std::string& name, int value);
    void set_uniform(const std::string& name, const Vec3& value);
    void set_uniform(const std::string& name, const Vec4& value);
    void set_uniform(const std::string& name, const Mat4& value);

private:
    GLuint program_id_;
    GLuint compile_shader(GLenum type, const std::string& source);
    bool opengl_available_;
};

class Renderer {
public:
    Renderer();
    ~Renderer();
    
    bool initialize(int window_width, int window_height);
    void render();
    void resize(int width, int height);
    
    void set_projection_matrix(const Mat4& projection);
    void set_view_matrix(const Mat4& view);
    void set_model_matrix(const Mat4& model);

private:
    // OpenGL objects
    GLuint vao_, vbo_, ebo_;
    
    // Shaders
    std::unique_ptr<Shader> basic_shader_;
    
    // Matrices
    Mat4 projection_matrix_;
    Mat4 view_matrix_;
    Mat4 model_matrix_;
    
    // Rendering state
    int window_width_, window_height_;
    bool opengl_available_;
    
    // Initialize methods
    bool setup_shaders();
    bool setup_buffers();
    
    // Utility methods
    std::string load_shader_source(const std::string& filepath);
};

} // namespace ChessPizza
