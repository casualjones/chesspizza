#pragma once

#include <string>
#include <vector>
#include <memory>

namespace ChessPizza {

/**
 * Theme system for managing different visual styles
 * Supports multiple piece sets, board materials, and environments
 */
class ThemeManager {
public:
    struct Theme {
        std::string name;
        std::string description;
        std::string pieces_path;
        std::string board_texture;
        std::string environment_map;
        bool has_animations;
    };

    ThemeManager();
    ~ThemeManager();

    // Theme management
    bool load_themes();
    bool set_active_theme(const std::string& theme_name);
    const Theme* get_active_theme() const;
    std::vector<Theme> get_available_themes() const;

    // Resource loading
    bool load_theme_resources(const Theme& theme);
    void unload_theme_resources();

private:
    std::vector<Theme> available_themes_;
    std::unique_ptr<Theme> active_theme_;
    std::string themes_directory_;

    bool scan_themes_directory();
    bool parse_theme_config(const std::string& config_path, Theme& theme);
};

} // namespace ChessPizza