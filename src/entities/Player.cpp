#include "Player.h"
#include "PlayerState.h"
#include "raylib.h"

Player::Player(Vector2 startPos){
    position = startPos; 
    size = { 32.0f, 32.0f }; 
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
    DrawRectangleV(position, size, color);
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
