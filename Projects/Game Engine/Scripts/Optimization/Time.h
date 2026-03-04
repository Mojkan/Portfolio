#pragma once
#include "SDL3/SDL.h"

namespace Time
{
    extern float deltaTime;

    extern Uint64 lastCounter;
    extern double lastFPSPrint;
    extern int frames;

    extern int FPSLimit;
    extern double expectedFrameTime;
    extern bool vSync;

    void init();
    void update();
}