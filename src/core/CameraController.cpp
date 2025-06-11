#include "core/CameraController.h"

CameraController::CameraController(float screenWidth, float screenHeight){
    camera.offset = {screenWidth/2.0f, screenHeight/2.0f};
    camera.target = {0.0f, 0.0f};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
}
CameraController::~CameraController(){
}

void CameraController::Update(Vector2 playerPos, int mapWidth, int mapHeight, int tileWidth, int tileHeight) {
    Vector2 offset = CalculateIsometricOffset(mapWidth, mapHeight, tileWidth, tileHeight);
    Vector2 isoPos = IsoToScreen(playerPos, (float)tileWidth, (float)tileHeight);

    isoPos.x += offset.x - (tileWidth / 2.0f);
    isoPos.y += offset.y;

    camera.target = isoPos;
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