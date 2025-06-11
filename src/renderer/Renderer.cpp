#include "renderer/Renderer.h"

Renderer::Renderer(int internalWidth, int internalHeight, int screenWidth, int screenHeight){
    this->screenWidth   = screenWidth;
    this->screenHeight  = screenHeight;
    target = LoadRenderTexture(internalWidth, internalHeight);
}

Renderer::~Renderer(){
    UnloadRenderTexture(target);
}

void Renderer::BeginUpscaleDraw(){
    BeginTextureMode(target);
}
void Renderer::EndUpscaleDraw(){
    EndTextureMode();
}
void Renderer::DrawUpscaled(){
    BeginDrawing();
    ClearBackground(BLACK);

    DrawTexturePro(
        target.texture,
        (Rectangle){ 0, 0, (float)target.texture.width, -(float)target.texture.height },
        (Rectangle){ 0, 0, (float)screenWidth, (float)screenHeight },
        (Vector2){ 0, 0 },
        0.0f,
        WHITE
    );

    DrawFPS(10, 10);
    EndDrawing();
}