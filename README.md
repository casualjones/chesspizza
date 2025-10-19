# ChessPizza

A modern 3D chess game with skinnable themes and adjustable difficulty levels, enhanced from the original Brutal Chess 0.5.

## Features

- **3D Graphics**: Modern OpenGL 4.0+ rendering with PBR materials
- **Skinnable Themes**: Multiple chess piece sets and board styles
- **Difficulty Levels**: Adjustable AI from Beginner to Grandmaster
- **Cross-Platform**: Linux, Windows, and macOS support
- **Modern Effects**: Dynamic lighting, shadows, and particle effects

## Building

### Prerequisites

- CMake 3.16+
- C++17 compatible compiler (GCC 7+, Clang 5+, MSVC 2017+)
- OpenGL 4.0+ compatible graphics driver

### Dependencies

#### Linux (Ubuntu/Debian)
```bash
sudo apt update
sudo apt install cmake build-essential
sudo apt install libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev
sudo apt install libglew-dev libglm-dev
```

#### Linux (Fedora/CentOS)
```bash
sudo dnf install cmake gcc-c++
sudo dnf install SDL2-devel SDL2_image-devel SDL2_mixer-devel
sudo dnf install glew-devel glm-devel
```

#### macOS
```bash
brew install cmake sdl2 sdl2_image sdl2_mixer glew glm
```

#### Windows
Use vcpkg or download libraries manually.

### Compilation

```bash
mkdir build
cd build
cmake ..
make -j$(nproc)
```

### Running

```bash
./ChessPizza
```

## Configuration

- **Themes**: Place theme files in `assets/themes/`
- **Settings**: Configuration saved in `~/.config/chesspizza/`
- **AI Engines**: Multiple difficulty levels built-in

## Controls

- **Mouse**: Move pieces, rotate camera
- **WASD**: Camera movement
- **Mouse Wheel**: Zoom in/out
- **ESC**: Main menu
- **F1**: Help
- **F11**: Fullscreen toggle

## Development

See `docs/DEVELOPMENT.md` for development guidelines and API documentation.

## License

Based on Brutal Chess 0.5. See LICENSE file for details.

## Credits

- Original Brutal Chess developers
- ChessPizza enhancements and modernization