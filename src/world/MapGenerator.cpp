#include "world/MapGenerator.h"
#include "raylib.h"

#include <cctype>
#include <cstdlib>
#include <fstream>
#include <sstream>

namespace {
    char TileToChar(TileType t){
        switch (t){
            case TILE_DIRT:         return '.';
            case TILE_DENSE_DIRT:   return ',';
            case TILE_ROCK:         return '#';
            default:                return '?';
        }
    }

    bool CharToTile(char c, TileType& out){
        switch (c){
            case '.': out = TILE_DIRT;          return true;
            case ',': out = TILE_DENSE_DIRT;    return true;
            case '#': out = TILE_ROCK;          return true;
            default:                            return false;
        }
    }
}

MapGenerator::MapGenerator(std::uint32_t seed)
    : seed(seed),
    width(DEFAULT_SIZE),
    height(DEFAULT_SIZE)
{
    tiles.assign(static_cast<size_t>(width * height), TILE_DIRT);
}

void MapGenerator::Generate() {
    // If it has already been loaded from a file, it retains the current size.
    // If the size is 0 (never initialized), it uses the default.
    if(width == 0 || height == 0){
        width = DEFAULT_SIZE;
        height = DEFAULT_SIZE;
        tiles.assign(static_cast<size_t>(width * height), TILE_DIRT);
    }

    const int halfW = width / 2;
    const int halfH = height / 2;

    // Pass 1: brute-force generation
    for (int y = -halfH; y <= halfH; ++y) {
        for (int x = -halfW; x <= halfW; ++x) {
            tiles[ToIndex(x, y)] = GenerateTile(x, y);
        }
    }

    // Pass 2: smoothing (in-place, preserves original behavior)
    for (int y = -halfH; y <= halfH; ++y) {
        for (int x = -halfW; x <= halfW; ++x) {
            tiles[ToIndex(x, y)] = SmoothTile(x, y);
        }
    }
}

void MapGenerator::Reseed(std::uint32_t newSeed) {
    seed = newSeed;
    Generate();
}

// Loading
bool MapGenerator::LoadFromFile(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        TraceLog(LOG_WARNING, TextFormat("MapGenerator: error to open '%s'", path.c_str()));
        return false;
    }

    std::vector<std::string> lines;
    std::string line;

    while (std::getline(file, line)) {
        if (!line.empty() && line.back() == '\r') line.pop_back();
        if (line.empty()) continue;
        lines.push_back(line);
    }

    if (lines.empty()) {
        TraceLog(LOG_ERROR, "MapGenerator: empty file");
        return false;
    }

    const size_t w = lines[0].size();
    const size_t h = lines.size();

    std::vector<TileType> loaded(w * h, TILE_DIRT);

    for (size_t y = 0; y < h; ++y) {
        if (lines[y].size() != w) {
            TraceLog(LOG_ERROR, TextFormat("MapGenerator: line %zu has an inconsistent width", y));
            return false;
        }
        for (size_t x = 0; x < w; ++x) {
            TileType t;
            if (!CharToTile(lines[y][x], t)) {
                TraceLog(LOG_ERROR, TextFormat(
                    "MapGenerator: invalid char '%c' at (%zu, %zu)",
                    lines[y][x], x, y));
                return false;
            }
            loaded[y * w + x] = t;
        }
    }

    tiles  = std::move(loaded);
    width  = static_cast<int>(w);
    height = static_cast<int>(h);

    TraceLog(LOG_INFO, TextFormat(
        "MapGenerator: loaded '%s' (%dx%d, seed %u)",
        path.c_str(), width, height, seed));
    return true;
}

bool MapGenerator::SaveToFile(const std::string& path) const {
    std::ofstream file(path);
    if (!file.is_open()) {
        TraceLog(LOG_WARNING, TextFormat("MapGenerator: error to save '%s'", path.c_str()));
        return false;
    }

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            file << TileToChar(tiles[static_cast<size_t>(y * width + x)]);
        }
        file << '\n';
    }
    TraceLog(LOG_INFO, TextFormat("MapGenerator: saved '%s'", path.c_str()));
    return true;
}

int MapGenerator::ToIndex(int x, int y) const {
    const int halfW = width  / 2;
    const int halfH = height / 2;
    const int ix = x + halfW;
    const int iy = y + halfH;
    if (ix < 0 || ix >= width || iy < 0 || iy >= height) return -1;
    return iy * width + ix;
}

TileType MapGenerator::Get(int x, int y) const {
    const int idx = ToIndex(x, y);
    if (idx < 0) return TILE_DIRT;
    return tiles[idx];
}

bool MapGenerator::IsSolidAt(int x, int y) const{
    return IsSolid(Get(x, y));
}

TileType MapGenerator::GetRaw(int x, int y) const {
    return tiles[ToIndex(x, y)];
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
    const int halfW = width  / 2;
    const int halfH = height / 2;

    for (int dy = -1; dy <= 1; ++dy) {
        for (int dx = -1; dx <= 1; ++dx) {
            if (dx == 0 && dy == 0) continue;
            const int nx = x + dx;
            const int ny = y + dy;
            if (nx < -halfW || nx > halfW || ny < -halfH || ny > halfH) continue;
            counts[static_cast<int>(GetRaw(nx, ny))]++;
        }
    }

    int maxIdx = 0;
    for (int i = 1; i < TILE_COUNT; ++i) {
        if (counts[i] > counts[maxIdx]) maxIdx = i;
    }
    return static_cast<TileType>(maxIdx);
}
