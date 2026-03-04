#include "GameObject.h"
#include "GameObjectManager.h"
#include "Component.h"
#include <iostream>

GameObject::GameObject(GameObjectManager& mManager, const std::string& n, const Tag t, const RenderGroups g) : manager(mManager), name(n), tag(t), renderGroup(g){}

void GameObject::start() {
    for (auto& component : components)
    {
        if(component->isEnabled()) component->start();
    }
}

void GameObject::update() {
    for (auto& component : components)
    {
        if (component->isEnabled()) component->update();
    }
}

void GameObject::draw() {
    for (auto& component : components)
    {
        if (component->isEnabled()) component->draw();
    }
}

void GameObject::onCollisionEnter(Collider *other) {
    for (auto& component : components)
    {
        if (component->isEnabled()) component->onCollisionEnter(other);
    }
}