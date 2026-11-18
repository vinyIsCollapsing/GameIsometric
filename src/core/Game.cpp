#include "raylib.h"
#include "raymath.h"

#include "core/Game.h"
#include "utils/ResourcePath.h"
#include "world/Map.h"

// Constructors
Game::Game(int width, int height, const char* title) {
    InitWindow(width, height, title);
    SetTargetFPS(60);

    renderer    = std::make_unique<Renderer>(320*2, 240*2, width, height);
    // Attempts to load a specific map, if it fails, we use the default (procedural) version
    const std::string mapPath = ResourcePath("maps/level1.map");
    map = std::make_unique<Map>(mapPath);

    camera = std::make_unique<CameraController>(
        (float)GetScreenWidth(),
        (float)GetScreenHeight(),
        (float)map->GetTileWidth(),
        (float)map->GetTileHeight()
    );

    player = std::make_unique<Player>(Vector2{1.0f, 0.0f}, map.get());

    #ifdef SKIP_MENU
        state = GameState::PLAYING;
    #else
        state = GameState::MENU;
    #endif
}

Game::~Game(){
    // unique_ptr automatically frees everything in the correct order
    CloseWindow();
}

// Public functions
void Game::Run() {
    while (!WindowShouldClose()) {
        Update();
        Draw();
    }
}

// Private functions
void Game::Update(){
    // Add input logic, physics, etc.
    switch (state){
        case GameState::MENU:       UpdateMenu(); break;
        case GameState::PLAYING:    UpdatePlaying(); break;
        case GameState::PAUSED:     UpdatePaused(); break;
        
        default: break;
    }
}
void Game::Draw(){
    // 1. Start drawing to the RenderTexture (internal resolution)
    renderer->BeginUpscaleDraw();

    ClearBackground(RAYWHITE);

    switch (state) {
        case GameState::MENU:    DrawMenu(); break;
        case GameState::PLAYING: DrawPlaying(); break;
        case GameState::PAUSED:  DrawPaused(); break;
    }

    // 2. Finish the internal drawing
    renderer->EndUpscaleDraw();

    // 3. Draw the upscaled RenderTexture on the actual screen
    renderer->DrawUpscaled();
}

void Game::UpdateMenu() {
    if (IsKeyPressed(KEY_ENTER)) {
        state = GameState::PLAYING;
    }
}

void Game::DrawMenu() {
    DrawText("MAIN MENU", 300, 200, 30, DARKBLUE);
    DrawText("Press ENTER to play", 270, 250, 20, GRAY);
}

void Game::UpdatePlaying() {
    if (IsKeyPressed(KEY_P)) {
        state = GameState::PAUSED;
        return;
    }

    // Clamp: if the game is minimized or paused, GetFrameTime() may return a large value.
    // 0.1s = 100ms prevents “teleportation” when resuming
    float dt = GetFrameTime();
    if (dt > 0.1f) dt = 0.1f;

    player->Update(dt);

    const float zoomChange = GetMouseWheelMove();  // positive or negative scroll
    if (zoomChange != 0.0f) {
        const float currentZoom = camera->GetZoom();
        float newZoom = currentZoom + zoomChange * 0.1f; // sensitivity factor

        // Limits zoom between 0.5x and 3.0x
        newZoom = Clamp(newZoom, 0.5f, 3.0f);
        camera->SetZoom(newZoom);
    }

    camera->Update(player->GetPosition(), map->GetMapWidth(), map->GetMapHeight());

}

void Game::DrawPlaying() {
    // DrawText(“GAME IN PROGRESS”, 280, 200, 30, DARKGREEN);
    // DrawText(“Press P to pause”, 280, 250, 20, GRAY);
    camera->Begin();
    map->Draw();
    player->Draw();
    camera->End();
}

void Game::UpdatePaused() {
    if (IsKeyPressed(KEY_P)) {
        state = GameState::PLAYING;
    }
}

void Game::DrawPaused() {
    DrawText("GAME PAUSED", 300, 200, 30, MAROON);
    DrawText("Press P to continue", 270, 250, 20, GRAY);
}