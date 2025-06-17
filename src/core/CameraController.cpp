#include "core/CameraController.h"
#include "utils/IsometricUtils.h"
#include <glm/glm.hpp>

CameraController::CameraController(float screenWidth, float screenHeight, float tileWidth, float tileHeight)
    : tileWidth(tileWidth), tileHeight(tileHeight)
{
    camera.offset = { screenWidth / 2.0f, screenHeight / 2.0f };
    camera.target = { 0.0f, 0.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    // Cria matriz isométrica apenas uma vez
    isoMat = GetIsometricMatrix(tileWidth, tileHeight);
}

CameraController::~CameraController() {}

void CameraController::Update(Vector2 playerPos, int mapWidth, int mapHeight) {
    Vector2 screenPos = IsoToScreen(isoMat, playerPos);

    Vector2 offset = CalculateIsometricOffset(mapWidth, mapHeight, tileWidth, tileHeight);

    screenPos.x += offset.x - (tileWidth / 2.0f);
    screenPos.y += offset.y;

    camera.target = screenPos;
}

void CameraController::Begin() {
    BeginMode2D(camera);
}

void CameraController::End() {
    EndMode2D();
}

void CameraController::SetZoom(float zoom) {
    camera.zoom = zoom;
}

float CameraController::GetZoom() const {
    return camera.zoom;
}
