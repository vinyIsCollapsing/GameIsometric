#ifndef ENTITIES_PLAYER_H
#define ENTITIES_PLAYER_H

#include "raylib.h"

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

        int mapWidth;
        int mapHeight;
        int tileWidth;
        int tileHeight;
        
        Texture2D texture;        // Textura do jogador
    public:
        Player(Vector2 startPos);
        ~Player();

        // Update player draw
        void Update();
        void Draw();

        // Change state of player
        void ChangeState(PlayerState* newState);

        // Getter and Setter
        Vector2 GetPosition() const;
        void    SetPosition(Vector2 newPos);

        void SetMapDimensions(int mapWidth, int mapHeight, int tileWidth, int tileHeight);
        
        // Variáveis acessadas pelo estado
        Direction8 currentDirection;
        Rectangle sourceRect;
};

#endif