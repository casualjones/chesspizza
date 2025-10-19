#pragma once

#include <string>
#include <vector>

namespace ChessPizza {

/**
 * Difficulty system for managing AI strength and game settings
 */
class DifficultyManager {
public:
    enum class Level {
        BEGINNER = 0,
        NOVICE,
        INTERMEDIATE,
        ADVANCED,
        EXPERT,
        MASTER,
        GRANDMASTER
    };

    struct DifficultySettings {
        Level level;
        std::string name;
        std::string description;
        int search_depth;
        int time_limit_ms;
        bool hints_enabled;
        bool analysis_mode;
        float thinking_time_multiplier;
    };

    DifficultyManager();
    ~DifficultyManager();

    // Difficulty management
    bool set_difficulty(Level level);
    Level get_current_difficulty() const;
    const DifficultySettings& get_current_settings() const;
    
    // Settings access
    std::vector<DifficultySettings> get_all_difficulties() const;
    const DifficultySettings& get_settings_for_level(Level level) const;
    
    // Game features
    bool are_hints_enabled() const;
    bool is_analysis_mode_enabled() const;
    int get_search_depth() const;
    int get_time_limit() const;

private:
    Level current_level_;
    std::vector<DifficultySettings> difficulty_levels_;
    
    void initialize_difficulty_levels();
};

} // namespace ChessPizza