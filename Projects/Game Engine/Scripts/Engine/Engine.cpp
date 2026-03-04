#include "Engine.h"

Engine* Engine::s_instance = nullptr;

Engine::Engine()
{
    s_instance = this;
}

Engine::~Engine()
{
    shutdown();
}

bool Engine::init(const char* title, int width, int height, bool fullscreen, bool vSync)
{
    window              = std::make_unique<Window>();
    renderer            = std::make_unique<Renderer>();
    input               = std::make_unique<Input>();
    texture             = std::make_unique<Texture>();
    audio               = std::make_unique<Audio>();
    gameObjectManager   = std::make_unique<GameObjectManager>();
    physics             = std::make_unique<Physics>();
    scenes              = std::make_unique<SceneManager>();

    if (!window->create(title, width, height, fullscreen)) return false;
    if (!renderer->create(window->getWindow(), vSync)) return false;

    Time::init();

    isRunning = true;
    return true;
}

void Engine::run()
{
    while (isRunning)
    {
        handleEvents();
        update();
        render();
        Time::update();
    }
}

void Engine::shutdown()
{
    scenes.reset();
    gameObjectManager.reset();
    physics.reset();
    audio.reset();
    texture.reset();
    input.reset();
    renderer.reset();
    window.reset();
    SDL_Quit();
}

void Engine::handleEvents()
{
    input->poll();
    if (input->isQuitRequested())
    {
        isRunning = false;
    }
}

void Engine::update()
{
    scenes->update();
    gameObjectManager->update();
    physics->update();
}

void Engine::render()
{
    renderer->render();
}