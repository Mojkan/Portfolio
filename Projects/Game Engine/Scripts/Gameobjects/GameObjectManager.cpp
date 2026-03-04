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
	// Clean the collider list
    auto& staticColliders = Engine::instance().getPhysics().getStaticColliders();
    auto& dynamicColliders = Engine::instance().getPhysics().getDynamicColliders();

    // Clear static collider list
    staticColliders.erase(
        std::remove_if(staticColliders.begin(), staticColliders.end(),
            [](Collider* c) {
				return !c->gameObject->isActive();
            }),
        staticColliders.end());

    // Clear dynamic collider list
    dynamicColliders.erase(
        std::remove_if(dynamicColliders.begin(), dynamicColliders.end(),
            [](Collider* c) {
                return !c->gameObject->isActive();
            }),
        dynamicColliders.end());

	// Clean the render groups
	for (auto& [_, vec] : Engine::instance().getRenderer().getRenderGroups()) std::erase_if(vec, [](auto* obj) { return !obj->isActive(); });

	// Destroy the inactive gameObjects
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

// Adds a new entity to a group
GameObject& GameObjectManager::addGameObject(const std::string& name, const Tag tag, const RenderGroups renderGroup)
{
	auto gameObject = std::make_unique<GameObject>(*this, name, tag, renderGroup);
	GameObject* rawPtr = gameObject.get();

	newGameObjects.emplace_back(std::move(gameObject));

	rawPtr->renderGroup = renderGroup;
	return *rawPtr;
}

// Returns the first gameobject with correct tag
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