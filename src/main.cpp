#include "game.h"
#include <iostream>

int main(int argc, char* argv[]) {
    (void)argc; // Suppress unused parameter warning
    (void)argv;
    
    std::cout << "ChessPizza - Modern 3D Chess Game" << std::endl;
    std::cout << "Based on Brutal Chess 0.5" << std::endl;
    
    try {
        ChessPizza::Game game;
        
        if (!game.initialize()) {
            std::cerr << "Failed to initialize game!" << std::endl;
            return 1;
        }
        
        game.run();
        game.shutdown();
        
    } catch (const std::exception& e) {
        std::cerr << "Game error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}