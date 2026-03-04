#pragma once

#include <vector>
#include <array>
#include <memory>
#include "GameObject.h"
#include "RenderGroups.h"
#include "Tags.h"

class GameObjectManager {
public:
    ~GameObjectManager();
    void update();
    void clear();

    GameObject& addGameObject(const std::string& name = "GameObject", const Tag tag = Tag::None, const RenderGroups renderGroup = RenderGroups::gameObjects);
    GameObject* findGameObjectByTag(const Tag tag);

private:
    void refreshGameObjects();
    void addNewGameObjects();
    void updateGameObjects();

    std::vector<std::unique_ptr<GameObject>> gameObjects;
    std::vector<std::unique_ptr<GameObject>> newGameObjects;
};