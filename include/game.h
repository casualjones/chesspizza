#pragma once

#include <GL/glew.h>
#include <GL/gl.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>
#include <string>
#include <iostream>
#include "renderer.h"
#include "difficulty_manager.h"
#include "theme_manager.h"

namespace ChessPizza {

enum class GameState {
    MENU,
    PLAYING,
    PAUSED,
    GAME_OVER,
    SETTINGS
};

struct GameSettings {
    bool fullscreen = false;
    bool vsync = true;
    int window_width = 1024;
    int window_height = 768;
    float master_volume = 1.0f;
    std::string theme = "classic";
};

class Game {
public:
    Game();
    ~Game();
    
    bool initialize();
    void run();
    void shutdown();

private:
    // Initialization
    bool init_sdl();
    bool init_opengl();
    bool init_game_systems();
    
    // Main loop
    void handle_events();
    void update(float delta_time);
    void render();
    
    // Event handlers
    void handle_key_event(const SDL_KeyboardEvent& event);
    void handle_mouse_event(const SDL_MouseButtonEvent& event);
    void handle_window_event(const SDL_WindowEvent& event);
    
    // Cleanup
    void cleanup_opengl();
    void cleanup_sdl();
    
    // Core systems
    SDL_Window* window_;
    SDL_GLContext gl_context_;
    std::unique_ptr<Renderer> renderer_;
    std::unique_ptr<DifficultyManager> difficulty_manager_;
    std::unique_ptr<ThemeManager> theme_manager_;
    
    // Game state
    GameState current_state_;
    GameSettings settings_;
    bool running_;
    bool vsync_;
    
    // Timing
    Uint32 last_frame_time_;
    float delta_time_;
};

} // namespace ChessPizza
