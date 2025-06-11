#ifndef GAME_H
#define GAME_H

#include "world/Map.h"
#include "entities/Player.h"
#include "renderer/Renderer.h"

enum class GameState {MENU, PLAYING, PAUSED};

class Game{
    public:
        Game(int width, int height, const char* title);
        ~Game();

        void Run();

    private:
        GameState state;
        Map *map;
        Renderer *renderer;
        bool WindowShouldCloseFlag;

        // Entities
        Player* player;
        
        void Update();
        void Draw();

        void UpdateMenu();
        void DrawMenu();

        void UpdatePlaying();
        void DrawPlaying();

        void UpdatePaused();
        void DrawPaused();
};


#endif