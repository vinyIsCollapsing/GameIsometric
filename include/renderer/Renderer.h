#ifndef RENDERER_RENDERER_H
#define RENDERER_RENDERER_H

#include "raylib.h"

class Renderer{
    private:
        int screenWidth, screenHeight;
        RenderTexture2D target;
    public:
        Renderer(int internalWidth, int internalHeight, int screenWidth, int screenHeight);
        ~Renderer();

        void BeginUpscaleDraw();
        void EndUpscaleDraw();
        void DrawUpscaled();
};

#endif