# Development Workflow

## Git Repository Setup

This repository tracks the ChessPizza project development.

### Initial Setup Complete ✅
- [x] Git repository initialized
- [x] .gitignore configured for C++ projects
- [x] Initial commit with full codebase
- [x] Proper branch structure

### Pushing to GitHub

1. Create a repository on GitHub.com named `chesspizza`
2. Run these commands:
```bash
git remote add origin https://github.com/YOUR_USERNAME/chesspizza.git
git branch -M main
git push -u origin main
```

### Development Workflow

#### Branch Strategy
- `main` - Stable releases
- `develop` - Development integration
- `feature/*` - New features
- `bugfix/*` - Bug fixes
- `hotfix/*` - Critical fixes

#### Commit Messages
Use conventional commits:
- `feat:` - New feature
- `fix:` - Bug fix
- `docs:` - Documentation changes
- `style:` - Code style changes
- `refactor:` - Code refactoring
- `test:` - Adding tests
- `build:` - Build system changes

#### Examples:
```bash
git commit -m "feat: add advanced AI difficulty levels"
git commit -m "fix: resolve OpenGL shader compilation errors"
git commit -m "docs: update build instructions for Windows"
```

### Current Status

**Commit Hash:** da8d9f8
**Files Tracked:** 89 files
**Lines of Code:** ~14,878

### Next Steps

1. Fix build dependencies (GLEW, SDL2-dev, GLM)
2. Complete OpenGL renderer implementation
3. Implement chess game logic integration
4. Add theme loading system
5. Create AI difficulty management
6. Add unit tests
7. Create release packages

### Build Status

Current build issues:
- Missing GLEW development headers
- SDL2 development packages needed
- OpenGL includes need fixing

### Contributing

1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Test thoroughly
5. Submit a pull request

### Release History

- **v1.0-dev** (Current) - Initial development version
  - Modern C++ architecture
  - OpenGL 4.0+ rendering foundation
  - Modular design
  - Cross-platform CMake build system