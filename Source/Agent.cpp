//
// Created by Krzysztof Sawicki on 17/05/2024.
//

#include "../Headers/Agent.h"

Agent::Agent(unsigned int seed, std::string name, Instance* currentInstance) : GameObject(name), seed(seed)
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

void Agent::RoundUpdate(const TimeSpace::GameTimeSystem* gameTime)
{
    // RoundUpdate
}

Instance* Agent::GetCurrentInstance() const
{
    return currentInstance;
}

void Agent::SetInstance(Instance* newInstance)
{
    currentInstance = newInstance;
}

