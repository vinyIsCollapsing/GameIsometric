#ifndef CORE_CAMERACONTROLLER_H
#define CORE_CAMERACONTROLLER_H

#include "raylib.h"
#include <glm/glm.hpp>

class CameraController {
public:
    CameraController(float screenWidth, float screenHeight, float tileWidth, float tileHeight);
    ~CameraController();

    void Update(Vector2 playerPos, int mapWidth, int mapHeight);
    void Begin();
    void End();

    void SetZoom(float zoom);
    float GetZoom() const;

private:
    Camera2D camera;
    glm::mat3 isoMat; // ← matriz isométrica armazenada
    float tileWidth;
    float tileHeight;
};

#endif
