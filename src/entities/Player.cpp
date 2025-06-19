#include "raylib.h"
#include <glm/glm.hpp>

#include "entities/Player.h"
#include "entities/PlayerState.h"
#include "utils/IsometricUtils.h"

Player::Player(Vector2 startPos){
    position = startPos; 
    size = { 32.0f, 32.0f }; 
    color = BLUE;
     
    texture = LoadTexture("assets/Player/player_movement.png");
    
    // Inicializa olhando para o sul
    sourceRect = { 0.0f, 0.0f, 32.0f, 32.0f };
    currentDirection = SOUTH;

    currentState = new IdleState();
}

Player::~Player() {
    UnloadTexture(texture);
    delete currentState;
}

void Player::Update() {
    if (currentState)
        currentState->Update(this);
}

void Player::Draw() {
    Vector2 offset = CalculateIsometricOffset(mapWidth, mapHeight, tileWidth, tileHeight);
    glm::mat3 isoMat = GetIsometricMatrix((float)tileWidth, (float)tileHeight);
    Vector2 isoPos = IsoToScreen(isoMat, position);

    isoPos.x += offset.x - (tileWidth / 2.0f);
    isoPos.y += offset.y;

    Vector2 drawPos = {
        isoPos.x - sourceRect.width / 2.0f,
        isoPos.y - sourceRect.height
    };

    DrawTextureRec(texture, sourceRect, drawPos, WHITE);
}

void Player::ChangeState(PlayerState* newState) {
    delete currentState; // libera o antigo
    currentState = newState;
}

Vector2 Player::GetPosition() const {
    return position;
}

void Player::SetPosition(Vector2 newPos){
    this->position = newPos;
}

void Player::SetMapDimensions(int mapWidth, int mapHeight, int tileWidth, int tileHeight) {
    this->mapWidth = mapWidth;
    this->mapHeight = mapHeight;
    this->tileWidth = tileWidth;
    this->tileHeight = tileHeight;
}