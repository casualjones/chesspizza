#pragma once

#include <memory>
#include <string>
#include <iostream>
#include "renderer.h"
#include "difficulty_manager.h"
#include "theme_manager.h"

// Forward declare SDL types if not available
#ifndef SDL_AVAILABLE
#ifndef SDL2_AVAILABLE
typedef struct SDL_Window SDL_Window;
typedef void* SDL_GLContext;
typedef unsigned int Uint32;
typedef union SDL_Event SDL_Event;
typedef struct SDL_KeyboardEvent SDL_KeyboardEvent;
typedef struct SDL_MouseButtonEvent SDL_MouseButtonEvent;
typedef struct SDL_WindowEvent SDL_WindowEvent;
#define SDL_NUM_SCANCODES 512
#endif
#endif

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
    bool sdl_available_;
    bool opengl_available_;
    
    // Timing
    Uint32 last_frame_time_;
    float delta_time_;
};

} // namespace ChessPizza
