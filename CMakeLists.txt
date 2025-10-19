cmake_minimum_required(VERSION 3.16)
project(ChessPizza VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Compiler flags
set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

# Find required packages
find_package(PkgConfig REQUIRED)
find_package(OpenGL REQUIRED)

# Try to find SDL2
pkg_check_modules(SDL2 sdl2)
if(NOT SDL2_FOUND)
    # Fallback to system SDL2
    find_library(SDL2_LIBRARIES SDL2)
    find_path(SDL2_INCLUDE_DIRS SDL.h PATH_SUFFIXES SDL2)
endif()

# Optional libraries - use if available
pkg_check_modules(SDL2_IMAGE SDL2_image)
pkg_check_modules(SDL2_MIXER SDL2_mixer)

# Try GLEW
find_package(GLEW)
if(NOT GLEW_FOUND)
    find_library(GLEW_LIBRARIES GLEW)
    find_path(GLEW_INCLUDE_DIRS GL/glew.h)
endif()

# GLM - header only library
find_path(GLM_INCLUDE_DIRS glm/glm.hpp)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)
if(SDL2_INCLUDE_DIRS)
    include_directories(${SDL2_INCLUDE_DIRS})
endif()
if(GLEW_INCLUDE_DIRS)
    include_directories(${GLEW_INCLUDE_DIRS})
endif()
if(GLM_INCLUDE_DIRS)
    include_directories(${GLM_INCLUDE_DIRS})
endif()

# Source files
file(GLOB SOURCES 
    "src/theme_manager.cpp"
    "src/difficulty_manager.cpp"
    "src/game.cpp"
    "src/main.cpp"
    "src/renderer.cpp"
)
file(GLOB_RECURSE HEADERS "include/*.h")

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Link libraries
target_link_libraries(${PROJECT_NAME}
    ${OpenGL_LIBRARIES}
)

# Link SDL2 if found
if(SDL2_LIBRARIES)
    target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
endif()

# Link additional libraries if found
if(SDL2_IMAGE_LIBRARIES)
    target_link_libraries(${PROJECT_NAME} ${SDL2_IMAGE_LIBRARIES})
endif()
if(SDL2_MIXER_LIBRARIES)
    target_link_libraries(${PROJECT_NAME} ${SDL2_MIXER_LIBRARIES})
endif()
if(GLEW_LIBRARIES)
    target_link_libraries(${PROJECT_NAME} ${GLEW_LIBRARIES})
endif()

# Compiler-specific options
target_compile_options(${PROJECT_NAME} PRIVATE ${SDL2_CFLAGS_OTHER})

# Copy assets to build directory
file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})

# Install rules
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
install(DIRECTORY assets DESTINATION share/chesspizza)