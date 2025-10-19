#include "difficulty_manager.h"
#include <iostream>

namespace ChessPizza {

DifficultyManager::DifficultyManager() 
    : current_level_(Level::INTERMEDIATE) {
    initialize_difficulty_levels();
}

DifficultyManager::~DifficultyManager() = default;

bool DifficultyManager::set_difficulty(Level level) {
    current_level_ = level;
    const auto& settings = get_current_settings();
    std::cout << "Difficulty set to: " << settings.name << std::endl;
    std::cout << "Description: " << settings.description << std::endl;
    return true;
}

DifficultyManager::Level DifficultyManager::get_current_difficulty() const {
    return current_level_;
}

const DifficultyManager::DifficultySettings& DifficultyManager::get_current_settings() const {
    return get_settings_for_level(current_level_);
}

std::vector<DifficultyManager::DifficultySettings> DifficultyManager::get_all_difficulties() const {
    return difficulty_levels_;
}

const DifficultyManager::DifficultySettings& DifficultyManager::get_settings_for_level(Level level) const {
    for (const auto& settings : difficulty_levels_) {
        if (settings.level == level) {
            return settings;
        }
    }
    
    // Fallback to intermediate if not found
    return difficulty_levels_[static_cast<int>(Level::INTERMEDIATE)];
}

bool DifficultyManager::are_hints_enabled() const {
    return get_current_settings().hints_enabled;
}

bool DifficultyManager::is_analysis_mode_enabled() const {
    return get_current_settings().analysis_mode;
}

int DifficultyManager::get_search_depth() const {
    return get_current_settings().search_depth;
}

int DifficultyManager::get_time_limit() const {
    return get_current_settings().time_limit_ms;
}

void DifficultyManager::initialize_difficulty_levels() {
    difficulty_levels_.clear();
    
    // Beginner - Very easy, lots of help
    difficulty_levels_.push_back({
        Level::BEGINNER,
        "Beginner",
        "Perfect for learning chess basics. Includes hints and move suggestions.",
        2,          // search_depth
        1000,       // time_limit_ms
        true,       // hints_enabled
        true,       // analysis_mode
        0.5f        // thinking_time_multiplier
    });
    
    // Novice - Easy with some help
    difficulty_levels_.push_back({
        Level::NOVICE,
        "Novice",
        "Easy difficulty with optional hints for new players.",
        3,          // search_depth
        2000,       // time_limit_ms
        true,       // hints_enabled
        true,       // analysis_mode
        0.7f        // thinking_time_multiplier
    });
    
    // Intermediate - Balanced gameplay
    difficulty_levels_.push_back({
        Level::INTERMEDIATE,
        "Intermediate",
        "Balanced difficulty for casual players.",
        4,          // search_depth
        3000,       // time_limit_ms
        false,      // hints_enabled
        true,       // analysis_mode
        1.0f        // thinking_time_multiplier
    });
    
    // Advanced - Challenging
    difficulty_levels_.push_back({
        Level::ADVANCED,
        "Advanced",
        "Challenging difficulty for experienced players.",
        5,          // search_depth
        5000,       // time_limit_ms
        false,      // hints_enabled
        true,       // analysis_mode
        1.2f        // thinking_time_multiplier
    });
    
    // Expert - Very challenging
    difficulty_levels_.push_back({
        Level::EXPERT,
        "Expert",
        "Very challenging for strong players.",
        6,          // search_depth
        8000,       // time_limit_ms
        false,      // hints_enabled
        false,      // analysis_mode
        1.5f        // thinking_time_multiplier
    });
    
    // Master - Tournament level
    difficulty_levels_.push_back({
        Level::MASTER,
        "Master",
        "Tournament-level strength for serious players.",
        7,          // search_depth
        12000,      // time_limit_ms
        false,      // hints_enabled
        false,      // analysis_mode
        2.0f        // thinking_time_multiplier
    });
    
    // Grandmaster - Maximum difficulty
    difficulty_levels_.push_back({
        Level::GRANDMASTER,
        "Grandmaster",
        "Maximum difficulty - prepare for a real challenge!",
        8,          // search_depth
        20000,      // time_limit_ms
        false,      // hints_enabled
        false,      // analysis_mode
        3.0f        // thinking_time_multiplier
    });
    
    std::cout << "Initialized " << difficulty_levels_.size() << " difficulty levels." << std::endl;
}

} // namespace ChessPizza