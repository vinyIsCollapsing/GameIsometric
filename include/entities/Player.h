#ifndef ENTITIES_PLAYER_H
#define ENTITIES_PLAYER_H

#include "raylib.h"

class PlayerState;

class Player{
    private:
        Vector2 position;
        Vector2 size;
        Color color;

        PlayerState* currentState;
    public:
        Player(Vector2 startPos);
        ~Player();

        // Update player draw
        void Update();
        void Draw();

        // Change state of player
        void ChangeState(PlayerState* newState);

        // Getter
        Vector2 GetPosition() const;
        void    SetPosition(Vector2 newPos);

};

#endif