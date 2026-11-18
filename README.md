# GameIsometric

A 2D isometric game prototype in C++17 with Raylib. It features a modular architecture, a state machine for the player, deterministic procedural generation, and unit tests.

![Gameplay](docs/screenshots/gameplay.gif)

## Features

- Isometric rendering with internal-resolution upscaling (640×480 → window)
- Player FSM (`Idle` / `Running`) with 8-direction sprite animation and grid movement
- Camera that follows the player, with smooth zoom
- Deterministic procedural map generation with neighbor-based smoothing
- Main menu and pause screen
- Unit tests with Catch2 covering isometric conversion, sprite directions, and map generation
- Collision with tiles, sliding movement along walls and delta time

## Stack

| Layer | Technology |
|---|---|
| Language | C++17 |
| Graphics | [Raylib](https://www.raylib.com/) |
| Math | [GLM](https://github.com/g-truc/glm) (header-only, vendored) |
| Build | CMake ≥ 3.16 |
| Tests | [Catch2 v3](https://github.com/catchorg/Catch2) (via FetchContent) |

## Build & Run

### Requirements

- CMake ≥ 3.16
- A compiler with C++17 support (GCC 9+, Clang 10+, MSVC 2019+)
- Git on PATH (only needed on the first build, for FetchContent)

### Linux / macOS

```bash
git clone https://github.com/vinyIsCollapsing/GameIsometric.git
cd GameIsometric
cmake -S . -B build
cmake --build build
./build/game
```

If Raylib is installed on the system, CMake uses it. Otherwise, it downloads and compiles version 5.5 automatically on the first configuration.

### Windows

```powershell
cmake -S . -B build
cmake --build build --config Release
.\build\Release\game.exe
```

### Skipping the menu

```bash
cmake -S . -B build -DSKIP_MENU=ON
```

## Testing

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

To see detailed output for each test case:

```bash
./build/tests --reporter console
```

Current coverage: 13 test cases. `MapGenerator` has no Raylib dependency, so it can be tested without opening a graphics context.

## Controls

| Key | Action |
|---|---|
| Enter | Start game (from menu) |
| P | Pause / resume |
| ↑ ↓ ← → | Move the player (8 isometric directions) |
| Mouse scroll | Camera zoom |
| Esc | Quit |

## Project Structure

```
GameIsometric/
├── include/
│   ├── core/        # Game loop, camera
│   ├── entities/    # Player, FSM
│   ├── renderer/    # Upscaling
│   ├── utils/       # Isometric math, resource paths
│   └── world/       # Map (rendering), MapGenerator (logic), TileType
├── src/             # Implementations mirroring include/
├── tests/           # Catch2 test cases
├── external/glm/    # Vendored header-only dependency
├── docs/screenshots/
└── assets/          # Sprites and tiles
```

`MapGenerator` is a pure class with no Raylib dependency. It produces the tile array from a seed, while `Map` uses the generator and handles only rendering. This makes generation testable without a window, and the algorithm can be swapped without touching the renderer.

## Architecture Decisions

- **RAII everywhere:** graphics resources and game objects are managed by `std::unique_ptr`. No manual `new`/`delete` in the main loop.
- **`Game` is non-copyable and non-movable:** it owns the window, a `RenderTexture`, and the game state, so duplicating it has no coherent meaning.
- **Self-contained headers:** every header includes what it uses, verified by compiling each one in isolation (`g++ -fsyntax-only`).
- **Logic / rendering separation:** `MapGenerator` knows nothing about Raylib, and `Map` knows nothing about generation logic.
- **Build-time asset paths:** `ASSETS_PATH` is defined by CMake and embedded in the binary, so the executable runs from any working directory.
- **Reproducible build:** Raylib is pinned to 5.5 via `FetchContent` (`GIT_TAG`, never `master`).
- **Pure, testable collision logic**: `Collision::TryMove` takes an `isWalkable` function as a parameter, without depending on `Player`, `Map`, or raylib. This allows you to test sliding, edges, and complete blocking without opening a graphics context.

## Roadmap

- [x] Isometric rendering with upscaling
- [x] Player FSM with 8 directions
- [x] Camera with zoom
- [x] Deterministic procedural generation
- [x] Unit tests (Catch2)
- [x] Reproducible build (FetchContent fallback)
- [x] Tile collision system
- [ ] Collision with footprint (box instead of point) for visual polish
- [ ] Pathfinding (A*)
- [ ] Map loading from file
- [ ] Simple map editor
- [ ] Sound effects and music