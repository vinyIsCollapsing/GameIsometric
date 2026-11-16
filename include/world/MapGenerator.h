#ifndef MAP_GENERATOR_H
#define MAP_GENERATOR_H

#include <array>
#include <cstdint>

#include "world/TileType.h"

class MapGenerator
{
public:
    static constexpr int RADIUS         = 16;
    static constexpr int SIZE           = 2 * RADIUS + 1;
    static constexpr int TOTAL_TILES    = SIZE * SIZE;

    explicit MapGenerator(std::uint32_t seed);      // Explicit seed = deterministic
    
    void Generate();                                // Generates the complete map using current seed
    void Reseed(std::uint32_t seed);                // Regenerates the map from a new seed
        
    static int ToIndex(int coord);                  // Internal index

    TileType Get(int x, int y) const;               // Retrives a tile based on grid coordinates. Coordinates outside [-RADIUS, RADIUS return TILE_DIRT]

    const std::array<TileType, TOTAL_TILES>& Tiles() const {return tiles;}      // Direct access to data for the Map to draw

    std::uint32_t Seed() const { return seed; }
private:
    std::uint32_t seed;
    std::array<TileType, TOTAL_TILES> tiles;

    TileType GenerateTile(int x, int y) const;
    TileType SmoothTile(int x, int y) const;
    TileType GetRaw(int x, int y) const;            // No bounds
};

#endif