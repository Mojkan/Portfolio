#pragma once

class GameObject;

class Scene {
public:
    virtual void load() = 0;
    GameObject* activeCamera = nullptr;
};