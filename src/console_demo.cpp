#include "theme_manager.h"
#include "difficulty_manager.h"
#include <iostream>

int main() {
    std::cout << "=== ChessPizza - Modern 3D Chess Game ===" << std::endl;
    std::cout << "Based on Brutal Chess 0.5" << std::endl;
    std::cout << std::endl;
    
    // Test Theme Manager
    std::cout << "Initializing Theme System..." << std::endl;
    ChessPizza::ThemeManager theme_manager;
    
    if (theme_manager.load_themes()) {
        std::cout << "Available themes:" << std::endl;
        auto themes = theme_manager.get_available_themes();
        for (const auto& theme : themes) {
            std::cout << "  - " << theme.name << ": " << theme.description << std::endl;
        }
        
        // Set a theme
        if (!themes.empty()) {
            theme_manager.set_active_theme(themes[0].name);
            std::cout << "Active theme: " << theme_manager.get_active_theme()->name << std::endl;
        }
    }
    
    std::cout << std::endl;
    
    // Test Difficulty Manager
    std::cout << "Initializing Difficulty System..." << std::endl;
    ChessPizza::DifficultyManager difficulty_manager;
    
    std::cout << "Available difficulty levels:" << std::endl;
    auto difficulties = difficulty_manager.get_all_difficulties();
    for (const auto& diff : difficulties) {
        std::cout << "  - " << diff.name << ": " << diff.description << std::endl;
        std::cout << "    Search Depth: " << diff.search_depth << ", Time Limit: " << diff.time_limit_ms << "ms" << std::endl;
    }
    
    // Test difficulty switching
    std::cout << std::endl;
    difficulty_manager.set_difficulty(ChessPizza::DifficultyManager::Level::EXPERT);
    std::cout << "Current difficulty: " << difficulty_manager.get_current_settings().name << std::endl;
    std::cout << "Hints enabled: " << (difficulty_manager.are_hints_enabled() ? "Yes" : "No") << std::endl;
    
    std::cout << std::endl;
    std::cout << "ChessPizza core systems initialized successfully!" << std::endl;
    std::cout << "Ready for 3D graphics integration." << std::endl;
    
    return 0;
}