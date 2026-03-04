#pragma once

#include <vector>
#include <memory>
#include <bitset>
#include <array>
#include "Component.h"
#include "Tags.h"
#include "RenderGroups.h"

// Maximum types of different componetns
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

	// A template function for adding new components to an entity
	// T is the component type, Targs lets you pass arguments to the component
	// These ... indicates a parameter pack
	// TArgs&& allows for named variables and temporaries
	// Targs is for the types of the arguments and mArgs the values of the arguments
	template <typename T, typename... TArgs>T& addComponent(TArgs&&... mArgs)
	{
		// T* component declares a pointer of that component type
		// new T creates a new component on the heap
		// mArgs are the argument values and TArgs the argument types
		T* component(new T(std::forward<TArgs>(mArgs)...));
		// Sets the entity to the component to this entity
		component->gameObject = this;
		// Makes the component pointer to a unique_ptr and takes ownership of it
		std::unique_ptr<Component> uPtr{ component };
		// Moves the uPtr to the vector of components pointers
		components.emplace_back(std::move(uPtr));

		// Stores the component in a array of component pointers
		componentArray[getComponentTypeID<T>()] = component;
		// Sets the specific component to true
		componentBitset[getComponentTypeID<T>()] = true;

		// Returns a pointer to the created component
		return *component;
	}

	// A template that returns a reference to a specific component type
	template<typename T> T& getComponent() const
	{
		// Get the stored pointer for this component type from the component array
		auto ptr(componentArray[getComponentTypeID<T>()]);
		// Cast the base Component* to the actual component type (T*) and return a reference
		return *static_cast<T*>(ptr);
	}

	// Generates a unique ID
	static std::size_t getComponentNewTypeID()
	{
		// This variable is static which doesn't destroy the variable when function is finished
		static std::size_t lastID = 0u;
		return lastID++;
	}

	// Assigns a unique fixed ID to each component type
	template <typename T> static std::size_t getComponentTypeID() noexcept
	{
		static std::size_t typeID = getComponentNewTypeID();
		return typeID;
	}
};