#include "Engine.h"

bool constexpr fullScreen = true;
bool constexpr VSync = true;

int main(int argc, char* argv[])
{
    Engine engine;
    engine.init("Real Engine", 1920, 1080, fullScreen, VSync);

    engine.run();
    return 0;
}