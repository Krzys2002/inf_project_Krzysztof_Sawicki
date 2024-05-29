//
// Created by Krzysztof Sawicki on 17/05/2024.
//

#include "../Headers/Agent.h"

Agent::Agent(unsigned int seed, std::string name, std::shared_ptr<Instance> currentInstance) : GameObject(name), seed(seed)
{
    this->currentInstance = currentInstance;
}

Agent::Agent(unsigned int ID, unsigned int seed, std::string name, std::shared_ptr<Instance> currentInstance) : GameObject(ID, name), seed(seed)
{
    this->currentInstance = currentInstance;
}

unsigned int Agent::GetSeed() const
{
    return seed;
}

Agent::~Agent()
{
    // Destructor
}

void Agent::RoundUpdate(TimeSpace::GameTimeSystem& gameTime)
{
    // RoundUpdate
}

std::shared_ptr<Instance> Agent::GetCurrentInstance() const
{
    return currentInstance;
}

void Agent::SetInstance(std::shared_ptr<Instance> newInstance)
{
    currentInstance = newInstance;
}

