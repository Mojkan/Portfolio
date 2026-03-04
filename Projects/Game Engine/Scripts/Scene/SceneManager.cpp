#include "SceneManager.h"
#include "Engine.h"
#include "MainMenuScene.h"
#include "MainScene.h"

SceneManager::SceneManager()
{
    static MainScene mainScene;
    static MainMenuScene mainMenuScene;

    registerScene("MainScene", &mainScene);
    registerScene("MainMenuScene", &mainMenuScene);

    loadScene("MainMenuScene");
}

void SceneManager::registerScene(const std::string& name, Scene* scene)
{
    scenes[name] = scene;
}

void SceneManager::loadScene(const std::string& name)
{
    if (!loadNewScene)
    {
        auto it = scenes.find(name);
        if (it != scenes.end())
        {
            currentScene = it->second;

            loadNewScene = true;
            std::cout << "Loaded scene: " << name << "\n";
        }
        else
        {
            std::cout << "Scene not found: " << name << "\n";
        }
    }
}

void SceneManager::update()
{
    if (loadNewScene)
    {
        Engine::instance().getTexture().clear();
        Engine::instance().getAudio().clear();
        Engine::instance().getRenderer().clear();
        Engine::instance().getPhysics().clear();
        Engine::instance().getGameObjectManager().clear();

        initNewScene();
    }
}

void SceneManager::initNewScene()
{
    currentScene->load();

    activeCamera = currentScene->activeCamera;
    if (!activeCamera)
    {
        std::cout << "No active camera in scene!";
    }

    loadNewScene = false;
}