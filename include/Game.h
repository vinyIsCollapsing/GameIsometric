#ifndef GAME_H
#define GAME_H

#include "Map.h"

enum class GameState {MENU, PLAYING, PAUSED};

class Game{
    public:
        Game(int width, int height, const char* title);
        ~Game();

        void Run();

    private:
        GameState state;
        Map *map;
        bool WindowShouldCloseFlag;
        
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