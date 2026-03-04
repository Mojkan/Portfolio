#pragma once

#include <vector>
#include <memory>
#include <bitset>
#include <array>
#include "Component.h"
#include "Tags.h"
#include "RenderGroups.h"

constexpr std::size_t maxComponents = 32;

class GameObjectManager;
class Component;
class Collider;

class GameObject
{
private:
    bool active = true;
	bool enabled = true;

    std::vector<std::unique_ptr<Component>> components;
	std::bitset<maxComponents> componentBitset;
	std::array<class Component*, maxComponents> componentArray;

public:
	Tag tag;
	std::string name;
	RenderGroups renderGroup;
    GameObjectManager& manager;

	GameObject(GameObjectManager& mManager, const std::string& n, const Tag t, const RenderGroups g);

	void start();
	void update();
    void draw();
	void onCollisionEnter(Collider* other);

	void setEnabled(bool value) { enabled = value; }
	bool isEnabled() const { return enabled; }

    void destroy() { active = false; }
    bool isActive() const { return active; }

    template <typename T> bool hasComponent() const
    {
        return componentBitset[getComponentTypeID<T>()];
    }

	template <typename T, typename... TArgs>T& addComponent(TArgs&&... mArgs)
	{
		T* component(new T(std::forward<TArgs>(mArgs)...));
		component->gameObject = this;
		std::unique_ptr<Component> uPtr{ component };
		components.emplace_back(std::move(uPtr));

		componentArray[getComponentTypeID<T>()] = component;
		componentBitset[getComponentTypeID<T>()] = true;

		return *component;
	}

	template<typename T> T& getComponent() const
	{
		auto ptr(componentArray[getComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
	}

	static std::size_t getComponentNewTypeID()
	{
		static std::size_t lastID = 0u;
		return lastID++;
	}

	template <typename T> static std::size_t getComponentTypeID() noexcept
	{
		static std::size_t typeID = getComponentNewTypeID();
		return typeID;
	}
};
