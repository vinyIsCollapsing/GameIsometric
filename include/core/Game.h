#ifndef GAME_H
#define GAME_H

#include <memory>

#include "world/Map.h"
#include "entities/Player.h"
#include "renderer/Renderer.h"
#include "core/CameraController.h"

enum class GameState {MENU, PLAYING, PAUSED};

class Game{
    public:
        Game(int width, int height, const char* title);
        ~Game();

        Game(const Game&) = delete;
        Game& operator=(const Game&) = delete;

        void Run();

    private:
        // NOTE: The order in which variables are declared determines the order in which they are destroyed
        // (members are destroyed in reverse order). Since Player holds
        // a Map*, Player must be destroyed before map—which is why
        // it is declared last.
        std::unique_ptr<Renderer> renderer;
        std::unique_ptr<CameraController> camera;
        std::unique_ptr<Map> map;
        std::unique_ptr<Player> player;

        GameState state;
        
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