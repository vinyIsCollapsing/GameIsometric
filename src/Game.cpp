#include "raylib.h"
#include "Game.h"
#include "Map.h"

// Constructors
Game::Game(int width, int height, const char* title) {
    InitWindow(width, height, title);
    SetTargetFPS(60);

    map = new Map();  // Cria o mapa após InitWindow()!
    player = new Player({320.0f, 240.0f});

    #ifdef SKIP_MENU
        state = GameState::PLAYING;
    #else
        state = GameState::MENU;
    #endif
}

Game::~Game(){
    delete map;  // libera a memória alocada
    delete player;
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
    BeginDrawing();
    ClearBackground(RAYWHITE);
    
    switch (state) {
        case GameState::MENU:    DrawMenu(); break;
        case GameState::PLAYING: DrawPlaying(); break;
        case GameState::PAUSED:  DrawPaused(); break;
    }
    
    EndDrawing();
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