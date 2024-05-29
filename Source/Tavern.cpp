//
// Created by Krzysztof Sawicki on 28/05/2024.
//

#include "../Headers/Tavern.h"

Tavern::Tavern(unsigned int seed, std::string name, std::shared_ptr<Instance> parentInstance) : Instance(seed, name, parentInstance,false)
{
    // Constructor
    maxPopulation = 30;

}

Tavern::~Tavern()
{
    // Destructor
}

void Tavern::Ready()
{
    for (int i = 0; i < maxPopulation; ++i)
    {
        auto agent = parentInstance->getFreeRandomAgent(seed + busyAgents.size());
        if (agent != nullptr)
        {
            agent->SetInstance(std::static_pointer_cast<Instance>(shared_from_this()));
            busyAgents.push_back(agent);
        }
    }
}

void Tavern::RoundUpdate(TimeSpace::GameTimeSystem& gameTime)
{
    // Method to update every round
    for (auto& agent : busyAgents)
    {
        parentInstance->freeAgent(agent);
    }
    busyAgents.clear();

    for (int i = 0; i < maxPopulation; ++i)
    {
        auto agent = parentInstance->getFreeRandomAgent(seed + busyAgents.size() + gameTime.getDayFromStart());
        if (agent != nullptr)
        {
            agent->SetInstance(std::static_pointer_cast<Instance>(shared_from_this()));
            busyAgents.push_back(agent);
        }
    }
}