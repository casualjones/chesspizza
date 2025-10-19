#include <iostream>
#include <chrono>
#include <thread>
#include "../include/difficulty_manager.h"
#include "../include/theme_manager.h"

int main() {
    std::cout << "ChessPizza - Modern 3D Chess Game" << std::endl;
    std::cout << "=================================" << std::endl;
    
    try {
        // Test difficulty manager
        ChessPizza::DifficultyManager difficulty_mgr;
        std::cout << "\n[Difficulty Manager Test]" << std::endl;
        std::cout << "Setting difficulty to Intermediate..." << std::endl;
        difficulty_mgr.set_difficulty(ChessPizza::DifficultyManager::Level::INTERMEDIATE);
        
        const auto& settings = difficulty_mgr.get_current_settings();
        std::cout << "Current difficulty settings:" << std::endl;
        std::cout << "- Level: " << settings.name << std::endl;
        std::cout << "- Description: " << settings.description << std::endl;
        std::cout << "- Search depth: " << settings.search_depth << std::endl;
        std::cout << "- Time limit: " << settings.time_limit_ms << "ms" << std::endl;
        std::cout << "- Hints enabled: " << (settings.hints_enabled ? "Yes" : "No") << std::endl;
        
        // Test theme manager  
        ChessPizza::ThemeManager theme_mgr;
        std::cout << "\n[Theme Manager Test]" << std::endl;
        std::cout << "Loading themes..." << std::endl;
        
        auto themes = theme_mgr.get_available_themes();
        std::cout << "Available themes:" << std::endl;
        for (const auto& theme : themes) {
            std::cout << "- " << theme.name << std::endl;
        }
        
        if (!themes.empty()) {
            std::cout << "Setting active theme to: " << themes[0].name << std::endl;
            if (theme_mgr.set_active_theme(themes[0].name)) {
                const auto* active_theme = theme_mgr.get_active_theme();
                if (active_theme) {
                    std::cout << "Active theme: " << active_theme->name << std::endl;
                    std::cout << "Description: " << active_theme->description << std::endl;
                }
            } else {
                std::cout << "Failed to set active theme." << std::endl;
            }
        }
        
        std::cout << "\n[Chess Board Preview]" << std::endl;
        std::cout << "  a b c d e f g h" << std::endl;
        std::cout << "8 r n b q k b n r 8" << std::endl;
        std::cout << "7 p p p p p p p p 7" << std::endl;
        std::cout << "6 . . . . . . . . 6" << std::endl;
        std::cout << "5 . . . . . . . . 5" << std::endl;
        std::cout << "4 . . . . . . . . 4" << std::endl;
        std::cout << "3 . . . . . . . . 3" << std::endl;
        std::cout << "2 P P P P P P P P 2" << std::endl;
        std::cout << "1 R N B Q K B N R 1" << std::endl;
        std::cout << "  a b c d e f g h" << std::endl;
        
        std::cout << "\nDemo complete! ChessPizza core systems initialized successfully." << std::endl;
        std::cout << "To run the full 3D version, install SDL2 and GLEW dependencies." << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
