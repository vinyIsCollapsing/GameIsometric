#include "raylib.h"

#include "core/Game.h"
#include "world/Map.h"

// Constructors
Game::Game(int width, int height, const char* title) {
    InitWindow(width, height, title);
    SetTargetFPS(60);

    renderer = new Renderer(320, 240, width, height);
    map = new Map();  // Cria o mapa após InitWindow()!
    player = new Player({0.0f, 0.0f});

    player->SetMapDimensions(
        map->GetWidth(),
        map->GetHeight(),
        map->GetTileWidth(),
        map->GetTileHeight()
    );

    #ifdef SKIP_MENU
        state = GameState::PLAYING;
    #else
        state = GameState::MENU;
    #endif
}

Game::~Game(){
    delete map;  // libera a memória alocada
    delete player;
    delete renderer;
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
    // 1. Comece a desenhar no RenderTexture (resolução interna)
    renderer->BeginUpscaleDraw();

    ClearBackground(RAYWHITE);
    
    switch (state) {
        case GameState::MENU:    DrawMenu(); break;
        case GameState::PLAYING: DrawPlaying(); break;
        case GameState::PAUSED:  DrawPaused(); break;
    }
    
    // 2. Finalize o desenho interno
    renderer->EndUpscaleDraw();

    // 3. Desenhe o RenderTexture ampliado na tela real
    renderer->DrawUpscaled();
}

void Game::UpdateMenu() {
    if (IsKeyPressed(KEY_ENTER)) {
        state = GameState::PLAYING;
    }
}

void Game::DrawMenu() {
    DrawText("MENU PRINCIPAL", 300, 200, 30, DARKBLUE);
    DrawText("Pressione ENTER para jogar", 270, 250, 20, GRAY);
}

void Game::UpdatePlaying() {
    if (IsKeyPressed(KEY_P)) {
        state = GameState::PAUSED;
    }  
    
    player->Update();
}

void Game::DrawPlaying() {
    // DrawText("JOGO EM EXECUÇÃO", 280, 200, 30, DARKGREEN);
    // DrawText("Pressione P para pausar", 280, 250, 20, GRAY);
    map->Draw();
    player->Draw();
}

void Game::UpdatePaused() {
    if (IsKeyPressed(KEY_P)) {
        state = GameState::PLAYING;
    }
}

void Game::DrawPaused() {
    DrawText("JOGO PAUSADO", 300, 200, 30, MAROON);
    DrawText("Pressione P para continuar", 270, 250, 20, GRAY);
}