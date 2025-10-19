#include "game.h"
#include "renderer.h"
#include <iostream>
#include <chrono>

namespace ChessPizza {

Game::Game() 
    : window_(nullptr)
    , gl_context_(nullptr)
    , running_(false)
    , window_width_(1024)
    , window_height_(768)
    , fullscreen_(false)
    , vsync_(true) {
}

Game::~Game() {
    shutdown();
}

bool Game::initialize() {
    std::cout << "Initializing ChessPizza..." << std::endl;
    
    if (!init_sdl()) {
        std::cerr << "Failed to initialize SDL!" << std::endl;
        return false;
    }
    
    if (!init_opengl()) {
        std::cerr << "Failed to initialize OpenGL!" << std::endl;
        return false;
    }
    
    if (!init_game_systems()) {
        std::cerr << "Failed to initialize game systems!" << std::endl;
        return false;
    }
    
    running_ = true;
    std::cout << "ChessPizza initialized successfully!" << std::endl;
    return true;
}

void Game::run() {
    std::cout << "Starting game loop..." << std::endl;
    
    auto last_time = std::chrono::high_resolution_clock::now();
    
    while (running_) {
        auto current_time = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(current_time - last_time);
        float delta_time = duration.count() / 1000000.0f;
        last_time = current_time;
        
        handle_events();
        update(delta_time);
        render();
    }
    
    std::cout << "Game loop ended." << std::endl;
}

void Game::shutdown() {
    std::cout << "Shutting down ChessPizza..." << std::endl;
    
    theme_manager_.reset();
    difficulty_manager_.reset();
    
    cleanup_opengl();
    cleanup_sdl();
    
    std::cout << "ChessPizza shutdown complete." << std::endl;
}

bool Game::init_sdl() {
#ifdef SDL_AVAILABLE
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        std::cerr << "SDL_Init failed: " << SDL_GetError() << std::endl;
        return false;
    }
#else
    std::cout << "SDL2 not available - running in console mode" << std::endl;
    return true;
#endif
    
    // Set OpenGL attributes
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
    
    // Create window
    Uint32 window_flags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN;
    if (fullscreen_) {
        window_flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
    }
    
    window_ = SDL_CreateWindow(
        "ChessPizza",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        window_width_,
        window_height_,
        window_flags
    );
    
    if (!window_) {
        std::cerr << "SDL_CreateWindow failed: " << SDL_GetError() << std::endl;
        return false;
    }
    
    return true;
}

bool Game::init_opengl() {
    // Create OpenGL context
    gl_context_ = SDL_GL_CreateContext(window_);
    if (!gl_context_) {
        std::cerr << "SDL_GL_CreateContext failed: " << SDL_GetError() << std::endl;
        return false;
    }
    
    // Initialize GLEW
    if (glewInit() != GLEW_OK) {
        std::cerr << "GLEW initialization failed!" << std::endl;
        return false;
    }
    
    // Set VSync
    SDL_GL_SetSwapInterval(vsync_ ? 1 : 0);
    
    // OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    
    // Enable multisampling
    glEnable(GL_MULTISAMPLE);
    
    // Set clear color
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    
    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "OpenGL Renderer: " << glGetString(GL_RENDERER) << std::endl;
    
    return true;
}

bool Game::init_game_systems() {
    // Initialize theme manager
    theme_manager_ = std::make_unique<ThemeManager>();
    if (!theme_manager_->load_themes()) {
        std::cerr << "Failed to load themes!" << std::endl;
        return false;
    }
    
    // Initialize difficulty manager
    difficulty_manager_ = std::make_unique<DifficultyManager>();
    difficulty_manager_->set_difficulty(DifficultyManager::Level::INTERMEDIATE);

    // Initialize renderer
    renderer_ = std::make_unique<Renderer>();
    if (!renderer_->initialize(window_width_, window_height_)) {
        std::cerr << "Failed to initialize renderer!" << std::endl;
        return false;
    }
    
    return true;
}

void Game::handle_events() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                running_ = false;
                break;
                
            case SDL_KEYDOWN:
            case SDL_KEYUP:
                handle_key_event(event.key);
                break;
                
            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEBUTTONUP:
                handle_mouse_event(event.button);
                break;
                
            case SDL_WINDOWEVENT:
                handle_window_event(event.window);
                break;
        }
    }
}

void Game::update(float delta_time) {
    (void)delta_time; // Suppress unused parameter warning
    // TODO: Update game logic
}

void Game::render() {
    if (renderer_) {
        renderer_->render();
    }
    
    SDL_GL_SwapWindow(window_);
}

void Game::handle_key_event(const SDL_KeyboardEvent& event) {
    if (event.type == SDL_KEYDOWN) {
        switch (event.keysym.sym) {
            case SDLK_ESCAPE:
                running_ = false;
                break;
                
            case SDLK_F11:
                // Toggle fullscreen
                fullscreen_ = !fullscreen_;
                if (fullscreen_) {
                    SDL_SetWindowFullscreen(window_, SDL_WINDOW_FULLSCREEN_DESKTOP);
                } else {
                    SDL_SetWindowFullscreen(window_, 0);
                }
                break;
        }
    }
}

void Game::handle_mouse_event(const SDL_MouseButtonEvent& event) {
    (void)event; // Suppress unused parameter warning
    // TODO: Handle mouse input for piece movement
}

void Game::handle_window_event(const SDL_WindowEvent& event) {
    if (event.event == SDL_WINDOWEVENT_RESIZED) {
        window_width_ = event.data1;
        window_height_ = event.data2;
        if (renderer_) {
            renderer_->resize(window_width_, window_height_);
        }
    }
}

void Game::cleanup_opengl() {
    if (gl_context_) {
        SDL_GL_DeleteContext(gl_context_);
        gl_context_ = nullptr;
    }
}

void Game::cleanup_sdl() {
    if (window_) {
        SDL_DestroyWindow(window_);
        window_ = nullptr;
    }
    
    SDL_Quit();
}

} // namespace ChessPizza