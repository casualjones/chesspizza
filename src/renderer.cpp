#include "renderer.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

namespace ChessPizza {

// Shader implementation
Shader::Shader(const std::string& vertex_path, const std::string& fragment_path) {
    std::string vertex_source = load_shader_source(vertex_path);
    std::string fragment_source = load_shader_source(fragment_path);

    GLuint vertex_shader = compile_shader(GL_VERTEX_SHADER, vertex_source);
    GLuint fragment_shader = compile_shader(GL_FRAGMENT_SHADER, fragment_source);

    program_id_ = glCreateProgram();
    glAttachShader(program_id_, vertex_shader);
    glAttachShader(program_id_, fragment_shader);
    glLinkProgram(program_id_);

    GLint success;
    glGetProgramiv(program_id_, GL_LINK_STATUS, &success);
    if (!success) {
        char info_log[512];
        glGetProgramInfoLog(program_id_, 512, NULL, info_log);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << info_log << std::endl;
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
}

Shader::~Shader() {
    glDeleteProgram(program_id_);
}

void Shader::use() {
    glUseProgram(program_id_);
}

std::string Shader::load_shader_source(const std::string& path) {
    std::ifstream shader_file;
    std::stringstream shader_stream;
    shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        shader_file.open(path);
        shader_stream << shader_file.rdbuf();
        shader_file.close();
    } catch (std::ifstream::failure& e) {
        std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: " << path << std::endl;
    }
    return shader_stream.str();
}

GLuint Shader::compile_shader(GLenum type, const std::string& source) {
    GLuint shader = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(shader, 1, &src, NULL);
    glCompileShader(shader);

    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char info_log[512];
        glGetShaderInfoLog(shader, 512, NULL, info_log);
        std::cerr << "ERROR::SHADER::COMPILATION_FAILED\n" << info_log << std::endl;
    }
    return shader;
}

// Renderer implementation
Renderer::Renderer() : vao_(0), vbo_(0), ebo_(0), width_(0), height_(0) {}

Renderer::~Renderer() {
    if (vao_ != 0) {
        glDeleteVertexArrays(1, &vao_);
        glDeleteBuffers(1, &vbo_);
        glDeleteBuffers(1, &ebo_);
    }
}

bool Renderer::initialize(int width, int height) {
    width_ = width;
    height_ = height;

    if (!load_shaders()) {
        return false;
    }

    // Setup a simple triangle for testing
    float vertices[] = {
        // positions         // normals           // texture coords
        -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
         0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  1.0f, 0.0f,
         0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  0.5f, 1.0f
    };

    glGenVertexArrays(1, &vao_);
    glGenBuffers(1, &vbo_);

    glBindVertexArray(vao_);

    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // Normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // Texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return true;
}

void Renderer::render() {
    glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (basic_shader_) {
        basic_shader_->use();
        glBindVertexArray(vao_);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);
    }
}

void Renderer::resize(int width, int height) {
    width_ = width;
    height_ = height;
    glViewport(0, 0, width, height);
}

bool Renderer::load_shaders() {
    try {
        basic_shader_ = std::make_unique<Shader>("assets/shaders/basic.vert", "assets/shaders/basic.frag");
    } catch (const std::exception& e) {
        std::cerr << "Failed to load shaders: " << e.what() << std::endl;
        return false;
    }
    return true;
}

} // namespace ChessPizza