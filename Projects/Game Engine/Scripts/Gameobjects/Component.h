#pragma once

class GameObject;
class Collider;

// Base class that all components should inherit from
class Component
{
private:
	bool enabled = true;

public:
	// A pointer to the gameobject that owns the object
	GameObject* gameObject;

	void setEnabled(bool value) { enabled = value; }
	bool isEnabled() const { return enabled; }

	// Virtual functions that can be overridden by derived components
	virtual void start() {}    // called once when the component is added
	virtual void update() {}  // called every frame
	virtual void draw() {}    // called every frame for rendering
	virtual void onCollisionEnter(Collider* other){}

	// Virtual destructor allows derived components to clean up correctly
	virtual ~Component() {}
};