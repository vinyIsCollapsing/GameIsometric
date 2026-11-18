#ifndef MAP_GENERATOR_H
#define MAP_GENERATOR_H

#include <cstdint>
#include <string>
#include <vector>

#include "world/TileType.h"

class MapGenerator
{
public:
    // Default procedural size map
    static constexpr int DEFAULT_RADIUS         = 16;
    static constexpr int DEFAULT_SIZE           = 2 * DEFAULT_RADIUS + 1;

    explicit MapGenerator(std::uint32_t seed);      // Explicit seed = deterministic
    
    void Generate();                                // Generates the complete map using current seed
    void Reseed(std::uint32_t seed);                // Regenerates the map from a new seed
    
    // Loading
    bool LoadFromFile(const std::string& path);
    bool SaveToFile(const std::string & path) const;

    // Dimension
    int GetWidth()  const {return width; }
    int GetHeight() const {return height; }

    int ToIndex(int x, int y) const;                  // Internal index

    TileType Get(int x, int y) const;               // Retrives a tile based on grid coordinates. Coordinates outside [-RADIUS, RADIUS return TILE_DIRT]
    bool IsSolidAt(int x, int y) const;             // true if is solid 

    const std::vector<TileType>& Tiles() const {return tiles;}      // Direct access to data for the Map to draw
    std::uint32_t Seed() const { return seed; }
    
private:
    std::uint32_t seed;
    int width = 0;
    int height = 0;
    std::vector<TileType> tiles;

    TileType GenerateTile(int x, int y) const;
    TileType SmoothTile(int x, int y) const;
    TileType GetRaw(int x, int y) const;            // No bounds
};

#endif