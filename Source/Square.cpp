//
// Created by Krzysztof Sawicki on 30/05/2024.
//

#include "../Headers/Square.h"

Square::Square(unsigned int seed, const WorldSettings& worldSettings, std::string name, std::shared_ptr<Instance> parentInstance) : Instance(seed, worldSettings, name, parentInstance, false)
{
    // Constructor
    RandomNumberGenerator rng(seed);
    maxPopulation = worldSettings.getSquarePopulation() + (worldSettings.getSquarePopulation()
            * rng.generateFloat(-worldSettings.getAberration(), worldSettings.getAberration()));
}

Square::~Square()
{
    // Destructor
}

void Square::ready()
{
    for (int i = 0; i < maxPopulation; ++i)
    {
        auto agent = parentInstance->getFreeRandomAgent(seed + busyAgents.size());
        if (agent != nullptr)
        {
            agent->setInstance(std::static_pointer_cast<Instance>(shared_from_this()));
            busyAgents.push_back(agent);
        }
    }
}

void Square::roundUpdate(TimeSpace::GameTimeSystem& gameTime)
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
            agent->setInstance(std::static_pointer_cast<Instance>(shared_from_this()));
            busyAgents.push_back(agent);
        }
    }
}