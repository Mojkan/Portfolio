#pragma once

class GameObject;
class Collider;

class Component
{
private:
	bool enabled = true;

public:
	GameObject* gameObject;

	void setEnabled(bool value) { enabled = value; }
	bool isEnabled() const { return enabled; }

	virtual void start() {}   
	virtual void update() {}  
	virtual void draw() {}    
	virtual void onCollisionEnter(Collider* other){}

	virtual ~Component() {}
};
