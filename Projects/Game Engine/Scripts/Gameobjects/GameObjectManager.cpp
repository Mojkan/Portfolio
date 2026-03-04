#include "GameObjectManager.h"
#include <algorithm>
#include <iostream>
#include "Engine.h"

void GameObjectManager::update()
{
    addNewGameObjects();
    updateGameObjects();
    refreshGameObjects();
}

void GameObjectManager::refreshGameObjects()
{
    auto& staticColliders = Engine::instance().getPhysics().getStaticColliders();
    auto& dynamicColliders = Engine::instance().getPhysics().getDynamicColliders();

    staticColliders.erase(
        std::remove_if(staticColliders.begin(), staticColliders.end(),
            [](Collider* c) {
				return !c->gameObject->isActive();
            }),
        staticColliders.end());

    dynamicColliders.erase(
        std::remove_if(dynamicColliders.begin(), dynamicColliders.end(),
            [](Collider* c) {
                return !c->gameObject->isActive();
            }),
        dynamicColliders.end());

	for (auto& [_, vec] : Engine::instance().getRenderer().getRenderGroups()) std::erase_if(vec, [](auto* obj) { return !obj->isActive(); });

    std::erase_if(gameObjects, [](const auto& obj) {
        return !obj->isActive();
        });
}

void GameObjectManager::addNewGameObjects()
{
    std::vector<GameObject*> addedObjects;
    addedObjects.reserve(newGameObjects.size());

    auto& renderGroups = Engine::instance().getRenderer().getRenderGroups();
    for (auto& gameObject : newGameObjects)
    {
        renderGroups[gameObject->renderGroup].push_back(gameObject.get());
        addedObjects.push_back(gameObject.get());
        gameObjects.emplace_back(std::move(gameObject));
    }

    newGameObjects.clear();

    for (auto* obj : addedObjects)
    {
        obj->start();
    }
}

void GameObjectManager::updateGameObjects()
{
	for (auto& gameObject : gameObjects)
    {
        if (!gameObject->isActive()) continue;
        if (gameObject->isEnabled()) gameObject->update();
    }
}

void GameObjectManager::clear()
{
    gameObjects.clear();
    newGameObjects.clear();
}

GameObject& GameObjectManager::addGameObject(const std::string& name, const Tag tag, const RenderGroups renderGroup)
{
	auto gameObject = std::make_unique<GameObject>(*this, name, tag, renderGroup);
	GameObject* rawPtr = gameObject.get();

	newGameObjects.emplace_back(std::move(gameObject));

	rawPtr->renderGroup = renderGroup;
	return *rawPtr;
}

GameObject* GameObjectManager::findGameObjectByTag(const Tag tag)
{
	for (auto& gameObject : gameObjects)
	{
		if (gameObject->tag == tag)
		{
			return gameObject.get();
		}
	}
	return nullptr;
}

GameObjectManager::~GameObjectManager()
{
    clear();
}
