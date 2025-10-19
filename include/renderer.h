#pragma once

#include <GL/glew.h>
#include <GL/gl.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <vector>
#include <memory>
#include <iostream>

namespace ChessPizza {

class Shader {
public:
    Shader(const std::string& vertex_source, const std::string& fragment_source);
    ~Shader();
    
    void use();
    GLuint get_program_id() const { return program_id_; }
    
    // Uniform setters
    void set_uniform(const std::string& name, float value);
    void set_uniform(const std::string& name, int value);
    void set_uniform(const std::string& name, const glm::vec3& value);
    void set_uniform(const std::string& name, const glm::vec4& value);
    void set_uniform(const std::string& name, const glm::mat4& value);

private:
    GLuint program_id_;
    GLuint compile_shader(GLenum type, const std::string& source);
};

class Renderer {
public:
    Renderer();
    ~Renderer();
    
    bool initialize(int window_width, int window_height);
    void render();
    void resize(int width, int height);
    
    void set_projection_matrix(const glm::mat4& projection);
    void set_view_matrix(const glm::mat4& view);
    void set_model_matrix(const glm::mat4& model);

private:
    // OpenGL objects
    GLuint vao_, vbo_, ebo_;
    
    // Shaders
    std::unique_ptr<Shader> basic_shader_;
    
    // Matrices
    glm::mat4 projection_matrix_;
    glm::mat4 view_matrix_;
    glm::mat4 model_matrix_;
    
    // Rendering state
    int window_width_, window_height_;
    
    // Initialize methods
    bool setup_shaders();
    bool setup_buffers();
    
    // Utility methods
    std::string load_shader_source(const std::string& filepath);
};

} // namespace ChessPizza
