#include "Time.h"
#include "Engine.h"

namespace Time
{
    float deltaTime = 0.0f;

    Uint64 lastCounter = 0;
    double lastFPSPrint = 0.0;
    int frames = 0;

    int FPSLimit = INT_MAX;
    double expectedFrameTime = 1000.0 / FPSLimit;
    bool vSync = false;

    void init()
    {
        lastCounter = SDL_GetPerformanceCounter();
        vSync = Engine::instance().getRenderer().isVSyncEnabled();
    }

    void update()
    {
        Uint64 NOW = SDL_GetPerformanceCounter();

        if (!vSync)
        {
            double frameTimeMs = (static_cast<double>(NOW - lastCounter) / SDL_GetPerformanceFrequency()) * 1000.0;
            if (frameTimeMs < expectedFrameTime)
            {
                Uint64 remainingTimeNs = static_cast<Uint64>((expectedFrameTime - frameTimeMs) * 1000000.0);
                SDL_DelayPrecise(remainingTimeNs);

                NOW = SDL_GetPerformanceCounter();
            }
        }

        double frameTimeMs = (static_cast<double>(NOW - lastCounter) / SDL_GetPerformanceFrequency()) * 1000.0;

        deltaTime = static_cast<float>(frameTimeMs / 1000.0f);

        frames++;
        lastFPSPrint += frameTimeMs;

        if (lastFPSPrint >= 1000.0)
        {
            double fps = frames / (lastFPSPrint / 1000.0);
            std::cout << "FPS: " << fps << "\n";
            frames = 0;
            lastFPSPrint = 0;
        }

        lastCounter = NOW;
    }
}