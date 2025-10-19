cmake_minimum_required(VERSION 3.16)
project(ChessPizza VERSION 1.0.0 LANGUAGES CXX)

# Set C++17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add executable with simple demo
add_executable(ChessPizza-Demo
    src/simple_demo.cpp
    src/difficulty_manager.cpp
    src/theme_manager.cpp
)

# Add executable with full game (if dependencies available)
set(BUILD_FULL_GAME OFF CACHE BOOL "Build full 3D game with SDL2/OpenGL")

if(BUILD_FULL_GAME)
    # Find packages
    find_package(OpenGL REQUIRED)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(SDL2 REQUIRED sdl2)
    pkg_check_modules(GLEW REQUIRED glew)
    pkg_check_modules(GLM REQUIRED glm)

    add_executable(ChessPizza
        src/main.cpp
        src/game.cpp
        src/renderer.cpp
        src/difficulty_manager.cpp
        src/theme_manager.cpp
    )

    target_include_directories(ChessPizza PRIVATE include)
    target_link_libraries(ChessPizza 
        ${OPENGL_LIBRARIES}
        ${SDL2_LIBRARIES}
        ${GLEW_LIBRARIES}
    )
    target_compile_options(ChessPizza PRIVATE ${SDL2_CFLAGS_OTHER} ${GLEW_CFLAGS_OTHER})
endif()

# Include directories for demo
target_include_directories(ChessPizza-Demo PRIVATE include)

# Copy assets to build directory
file(COPY assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# Installation
install(TARGETS ChessPizza-Demo RUNTIME DESTINATION bin)
if(BUILD_FULL_GAME)
    install(TARGETS ChessPizza RUNTIME DESTINATION bin)
endif()
install(DIRECTORY assets DESTINATION share/chesspizza)

# Package configuration
set(CPACK_PACKAGE_NAME "ChessPizza")
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_PACKAGE_DESCRIPTION "Modern 3D chess game with skinnable themes")
include(CPack)
