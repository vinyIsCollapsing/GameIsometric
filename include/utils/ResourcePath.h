#ifndef RESOURCE_PATH_H
#define RESOURCE_PATH_H

#include <string>

// Returns the absolute path of an asset relative to the root directory configured in CMake.
// Example: ResourcePath(“Player/player_movement.png”)
// CMake sets ASSETS_PATH = ${CMAKE_SOURCE_DIR}/assets.

inline std::string ResourcePath(const std::string& relative){
    #ifdef ASSETS_PATH
        return std::string(ASSETS_PATH) + "/" + relative;
    #else
        return "assets/" + relative;        // Fallback builds outside CMake
    #endif
}

#endif