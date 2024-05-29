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

void GameObject::Ready()
{
    // Ready
}

void GameObject::Update(double deltaTime)
{
    // Update
}

void GameObject::RoundUpdate(const TimeSpace::GameTimeSystem* gameTime)
{
    // RoundUpdate
}