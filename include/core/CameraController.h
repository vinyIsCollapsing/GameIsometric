#ifndef CAMERA_CONTROLLER_H
#define CAMERA_CONTROLLER_H

#include "raylib.h"

#include "utils/IsometricUtils.h"

class CameraController{
    private:
        Camera2D camera;
    public:
        CameraController(float screenWidth, float screenHeight);
        ~CameraController();

        void Update(Vector2 playerPos, int mapWidth, int mapHeight, int tileWidth, int tileHeight);
        void Begin();
        void End();

        void SetZoom(float zoom);
        float GetZoom() const;
};

#endif