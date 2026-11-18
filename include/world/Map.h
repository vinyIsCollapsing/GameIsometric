#ifndef MAP_H
#define MAP_H

#include <memory>
#include <string>

#include "raylib.h"
#include "world/MapGenerator.h"

class Map {
public:
    Map();                                      // Procedural constructor
    explicit Map(const std::string& mapPath);   // File constructor
    ~Map();

    int GetMapWidth() const;
    int GetMapHeight() const;
    int GetTileWidth() const;
    int GetTileHeight() const;

    // Converts isometric grid coordinates to screen position,
    // already including the map's center offset.
    // Consolidates the formula that was previously duplicated in 
    Vector2 GridToScreen(Vector2 gridPos) const;
    bool IsWalkable(int x, int y) const;

    void Draw();                // Draw map

private:
    void LoadTileTexture();
    Vector2 GetCachedOffset() const;

    std::unique_ptr<MapGenerator> generator;
    
    int mapWidth = 0;
    int mapHeight = 0;
    const int tileWidth = 32;
    const int tileHeight = 32;

    Image img;
    Texture2D texture;
    Rectangle sourceRect;

    // mutable: cache populated on demand in GetCachedOffset() const
    mutable Vector2 cachedOffset{};
    mutable bool offsetCalculated = false;
};

#endif
