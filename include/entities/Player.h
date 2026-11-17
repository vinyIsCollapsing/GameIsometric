#ifndef ENTITIES_PLAYER_H
#define ENTITIES_PLAYER_H

#include "raylib.h"
#include "world/Map.h"

class PlayerState;

enum Direction8 {
    SOUTH = 0,
    SOUTHEAST,
    EAST,
    NORTHEAST,
    NORTH,
    NORTHWEST,
    WEST,
    SOUTHWEST
};

class Player{
    private:
        Vector2 position;
        Vector2 size;
        Color color;

        PlayerState* currentState;

        Texture2D texture;        // Player texture
        Map* map;                 // Reference to the Map object for shared offset

    public:
        Player(Vector2 startPos, Map* gameMap);
        ~Player();

        // Update player draw
        void Update(float dt);
        void Draw();

        // Change state of player
        void TryMove(Vector2 delta);
        void ChangeState(PlayerState* newState);

        // Getter and Setter
        Vector2 GetPosition() const;
        void SetPosition(Vector2 newPos);
        
        // Variáveis acessadas pelo estado
        Direction8 currentDirection;
        Rectangle sourceRect;
        Direction8 lastDirectionPrinted = SOUTH;
};

#endif
