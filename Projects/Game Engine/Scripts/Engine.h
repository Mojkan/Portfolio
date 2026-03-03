#pragma once
#include <memory>
#include "Window.h"
#include "Renderer.h"
#include "Input.h"
#include "Texture.h"
#include "Time.h"
#include "Audio.h"
#include "GameObjectManager.h"
#include "Physics.h"
#include "SceneManager.h"
#include "Vector2D.h"

class Engine
{
public:
    Engine();
    ~Engine();

    bool init(const char* title, int width, int height, bool fullscreen, bool vSync);
    void run();
    void shutdown();

    // Accessors to subsystems
    inline static Engine& instance() { return *s_instance; }

    Window&             getWindow()             { return *window; }
    Renderer&           getRenderer()           { return *renderer; }
    Input&              getInput()              { return *input; }
    Texture&            getTexture()            { return *texture; }
    Audio&              getAudio()              { return *audio; }
    GameObjectManager&  getGameObjectManager()  { return *gameObjectManager; }
    Physics&            getPhysics()            { return *physics; }
    SceneManager&       getScenes()             { return *scenes; }

    bool isRunning = true;

private:
    void handleEvents();
    void update();
    void render();

    std::unique_ptr<Window>             window;
    std::unique_ptr<Renderer>           renderer;
    std::unique_ptr<Input>              input;
    std::unique_ptr<Texture>            texture;
    std::unique_ptr<Audio>              audio;
    std::unique_ptr<GameObjectManager>  gameObjectManager;
    std::unique_ptr<Physics>            physics;
    std::unique_ptr<SceneManager>       scenes;

    static Engine* s_instance;
};