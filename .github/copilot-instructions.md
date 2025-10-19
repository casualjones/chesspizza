# ChessPizza Development Guidelines

ChessPizza is a modern 3D chess game with skinnable themes and adjustable difficulty levels, based on the original Brutal Chess 0.5.

## Project Overview
- **Base**: Enhanced port of Brutal Chess 0.5
- **Key Features**: Skinnable themes, difficulty levels, modern graphics
- **Tech Stack**: C++17, OpenGL 4.0+, SDL2, CMake
- **Target**: Cross-platform (Linux, Windows, macOS)

## Core Features
1. **Skinnable Theme System**
   - Multiple chess piece sets (Classic, Modern, Fantasy, etc.)
   - Customizable board materials and textures
   - Dynamic lighting and environment themes
   - User-selectable skin packs

2. **Difficulty System**
   - Multiple AI difficulty levels (Beginner to Grandmaster)
   - Configurable time controls
   - Hint system for learning
   - Analysis mode

3. **Graphics Enhancements**
   - Modern OpenGL rendering pipeline
   - PBR (Physically Based Rendering) materials
   - Dynamic shadows and lighting
   - Particle effects for moves and captures
   - Anti-aliasing and post-processing

## Development Focus
- Clean, modular C++ architecture
- Resource management for themes and assets
- Configuration system for difficulty and preferences
- Modern OpenGL best practices
- Cross-platform compatibility

## Coding Standards
- Use C++17 features
- RAII for resource management
- Consistent naming conventions (snake_case for functions/variables)
- Comprehensive error handling
- Performance-conscious rendering code