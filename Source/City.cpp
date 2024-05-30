//
// Created by Krzysztof Sawicki on 22/05/2024.
//

#include "../Headers/City.h"

City::City(unsigned int seed, const WorldSettings& worldSettings, std::string name, std::shared_ptr<Instance> parentInstance, bool hasIndependentPopulation) : Instance(seed, worldSettings, name, parentInstance, hasIndependentPopulation)
{
    RandomNumberGenerator rng(seed);
    maxPopulation = worldSettings.getCityPopulation() + (worldSettings.getCityPopulation()
            * rng.generateFloat(-worldSettings.getAberration(), worldSettings.getAberration()));
}

City::~City()
{
    // Destructor
}

void City::ready()
{
    // Ready
}

void City::freeAllAgents()
{
    for(auto agent : busyAgents)
    {
        agent.reset();
    }

    idUsed = std::vector<bool>(maxPopulation, false);
    busyAgents.clear();
}

void City::freeAgent(std::shared_ptr<Agent> agent)
{
    // Method Free agent from the instance
    Instance::freeAgent(agent);
}

std::vector<std::shared_ptr<Agent>> City::getBusyAgents() const
{
    // Method to get all busy agents from the instance
    return busyAgents;
}

std::shared_ptr<Agent> City::getFreeRandomAgent()
{
    // Method to get agent from the instance if any free agent is available (if not it returns nullptr)
    return Instance::getFreeRandomAgent();
}

std::shared_ptr<Agent> City::getFreeRandomAgent(unsigned int seed)
{
    // Method to get agent from the instance if any free agent is available with seed (if not it returns nullptr)
    return Instance::getFreeRandomAgent(seed);
}

std::shared_ptr<Tavern> City::CreateTavern(unsigned int seed)
{
    // Method to create tavern
    auto tavern = std::make_shared<Tavern>(seed, worldSettings, GameNameHolder::getRandomTavernName(seed),
                                           std::static_pointer_cast<Instance>(shared_from_this()));
    childrenInstances.push_back(tavern);
    return tavern;
}

std::shared_ptr<Tavern> City::CreateTavern()
{
    unsigned int seed = this->seed + childrenInstances.size() + dayCounter;
    // Method to create tavern
    return CreateTavern(seed);
}

std::shared_ptr<Square> City::CreateSquare(unsigned int seed)
{
    // Method to create square
    auto square = std::make_shared<Square>(seed, worldSettings, GameNameHolder::getRandomSquareName(seed),
                                           std::static_pointer_cast<Instance>(shared_from_this()));
    childrenInstances.push_back(square);
    return square;
}

std::shared_ptr<Square> City::CreateSquare()
{
    unsigned int seed = this->seed + childrenInstances.size() + dayCounter;
    // Method to create square
    return CreateSquare(seed);
}



