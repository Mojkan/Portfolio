#pragma once
#include <unordered_map>
#include <string>
#include <iostream>
#include "Scene.h"

class SceneManager {
public:
    SceneManager();
    GameObject* activeCamera = nullptr;

    void registerScene(const std::string& name, Scene* scene);
    void loadScene(const std::string& name);
    void update();
    void initNewScene();

private:
    bool loadNewScene = false;

    std::unordered_map<std::string, Scene*> scenes;
    Scene* currentScene = nullptr;
};