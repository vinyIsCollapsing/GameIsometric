#include "world/MapGenerator.h"

#include <cstdlib>

MapGenerator::MapGenerator(std::uint32_t seed)
    : seed(seed)
{
    tiles.fill(TILE_DIRT);
}

void MapGenerator::Reseed(std::uint32_t newSeed) {
    seed = newSeed;
    Generate();
}

void MapGenerator::Generate() {
    // Pass 1: brute-force generation
    for (int y = -RADIUS; y <= RADIUS; ++y) {
        for (int x = -RADIUS; x <= RADIUS; ++x) {
            tiles[ToIndex(y) * SIZE + ToIndex(x)] = GenerateTile(x, y);
        }
    }

    // Pass 2: smoothing (in-place, preserves original behavior)
    for (int y = -RADIUS; y <= RADIUS; ++y) {
        for (int x = -RADIUS; x <= RADIUS; ++x) {
            tiles[ToIndex(y) * SIZE + ToIndex(x)] = SmoothTile(x, y);
        }
    }
}

int MapGenerator::ToIndex(int coord) {
    return coord + RADIUS;
}

TileType MapGenerator::Get(int x, int y) const {
    if (x < -RADIUS || x > RADIUS || y < -RADIUS || y > RADIUS) {
        return TILE_DIRT;
    }
    return GetRaw(x, y);
}

bool MapGenerator::IsSolidAt(int x, int y) const{
    return IsSolid(Get(x, y));
}

TileType MapGenerator::GetRaw(int x, int y) const {
    return tiles[ToIndex(y) * SIZE + ToIndex(x)];
}

TileType MapGenerator::GenerateTile(int x, int y) const {
    const int hash = std::abs(
        static_cast<int>(((x + seed) * 73856093) ^ ((y + seed) * 19349663))
    ) % 100;

    // Northwest: rockier
    if (x < 0 && y < 0) {
        if (hash < 80) return TILE_ROCK;
        if (hash < 70) return TILE_DENSE_DIRT;  // unreachable (intentionally preserved)
        return TILE_DIRT;
    }

    // Southeast: more fertile
    if (x > 0 && y > 0) {
        if (hash < 10) return TILE_ROCK;
        if (hash < 20) return TILE_DENSE_DIRT;
        return TILE_DIRT;
    }

    // Default
    if (hash < 30) return TILE_ROCK;
    if (hash < 70) return TILE_DENSE_DIRT;
    return TILE_DIRT;
}

TileType MapGenerator::SmoothTile(int x, int y) const {
    int counts[TILE_COUNT] = {0, 0, 0};

    for (int dy = -1; dy <= 1; ++dy) {
        for (int dx = -1; dx <= 1; ++dx) {
            if (dx == 0 && dy == 0) continue;

            const int nx = x + dx;
            const int ny = y + dy;

            if (nx >= -RADIUS && nx <= RADIUS && ny >= -RADIUS && ny <= RADIUS) {
                counts[static_cast<int>(GetRaw(nx, ny))]++;
            }
        }
    }

    int maxIdx = 0;
    for (int i = 1; i < TILE_COUNT; ++i) {
        if (counts[i] > counts[maxIdx]) maxIdx = i;
    }
    return static_cast<TileType>(maxIdx);
}