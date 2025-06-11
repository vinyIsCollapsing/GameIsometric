#include "raylib.h"

#include "entities/Player.h"
#include "entities/PlayerState.h"
#include "utils/IsometricUtils.h"

Player::Player(Vector2 startPos){
    position = startPos; 
    size = { 16.0f, 16.0f }; 
    color = BLUE;
     
    currentState = new IdleState();
}

Player::~Player() {
    delete currentState;
}

void Player::Update() {
    if (currentState)
        currentState->Update(this);
}

void Player::Draw() {
    Vector2 offset = CalculateIsometricOffset(mapWidth, mapHeight, tileWidth, tileHeight);

    Vector2 isoPos = IsoToScreen(position, (float)tileWidth, (float)tileHeight);

    isoPos.x += offset.x - (tileWidth / 2.0f);
    isoPos.y += offset.y;

    DrawRectangleV(isoPos, size, color);
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