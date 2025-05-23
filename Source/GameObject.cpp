//
// Created by Krzysztof Sawicki on 14/05/2024.
//

#include "../Headers/GameObject.h"

unsigned int GameObject::newID = 0;

GameObject::GameObject(const std::string& name) : ID(newID)
{
    newID++;
    this->name = name;
}

GameObject::GameObject(unsigned int ID, const std::string& name) : ID(ID)
{
    this->name = name;
}

int GameObject::getID() const
{
    return ID;
}

std::string GameObject::getName() const
{
    return name;
}

GameObject::~GameObject()
{
    // Destructor
}

void GameObject::ready()
{
    // Ready
}

void GameObject::update(double deltaTime)
{
    // Update
}

void GameObject::roundUpdate(TimeSpace::GameTimeSystem& gameTime)
{
    // RoundUpdate
}