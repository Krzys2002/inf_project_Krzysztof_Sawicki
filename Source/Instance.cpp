//
// Created by Krzysztof Sawicki on 17/05/2024.
//

#include "../Headers/Instance.h"

std::vector<unsigned int> Instance::getIDPool(unsigned int size)
{
    std::vector<unsigned int> pool(size);

    for (int i = 0; i < size; ++i)
    {
        pool[i] = newID;
        newID++;
    }

    return pool;
}

Instance::Instance(unsigned int seed, const WorldSettings& worldSettings, std::string name, std::shared_ptr<Instance> parentInstance, bool hasIndependentPopulation)
: GameObject(name), seed(seed), worldSettings(worldSettings)
{
    this->parentInstance = parentInstance;
    this->hasIndependentPopulation = hasIndependentPopulation;
}


std::string Instance::getDescription() const
{
    return description;
}

void Instance::setDescription(const std::string& description)
{
    this->description = description;
}

void Instance::ready()
{
    // Ready
    // this check is necessary to set Ready only one time to any Agent
    if(hasIndependentPopulation)
    {

        // call Ready on all agents
        for (auto agent : busyAgents)
        {
            agent->ready();
        }
    }
}

void Instance::roundUpdate(TimeSpace::GameTimeSystem& gameTime)
{
    // RoundUpdate
    dayCounter = gameTime.getDayFromStart();
    if(hasIndependentPopulation)
    {
        for (auto agent : busyAgents)
        {
            agent->roundUpdate(gameTime);
        }
    }
}

std::vector<std::shared_ptr<Instance>> Instance::getChildrenInstances()
{
    return childrenInstances;
}

std::shared_ptr<Instance> Instance::getParentInstance()
{
    return parentInstance;
}

std::shared_ptr<Agent> Instance::getFreeRandomAgent(unsigned int seed)
{
    if(hasIndependentPopulation)
    {
        if(idPool.empty())
        {
            idPool = getIDPool(maxPopulation);
            idUsed = std::vector<bool>(maxPopulation, false);
        }

        if (busyAgents.size() >= maxPopulation)
        {
            return nullptr;
        }

        while (idUsed[seed % maxPopulation])
        {
            seed++;
        }

        auto agent = std::make_shared<Agent>(idPool[seed % maxPopulation], seed,
                                             GameNameHolder::getRandomAgentName(seed),
                                             std::static_pointer_cast<Instance>(shared_from_this()));
        idUsed[seed % maxPopulation] = true;
        busyAgents.emplace_back(agent);
        return  agent;
    }
    else
    {
        if (parentInstance == nullptr)
        {
            return nullptr;
        }

        std::shared_ptr<Agent> agent = parentInstance->getFreeRandomAgent(seed);
        if(agent != nullptr)
        {
            agent->setInstance(std::static_pointer_cast<Instance>(shared_from_this()));
            busyAgents.push_back(agent);
            return agent;
        }
    }
}

std::shared_ptr<Agent> Instance::getFreeRandomAgent()
{
    RandomNumberGenerator rng;
    return getFreeRandomAgent(rng.generate());
}

void Instance::freeAllAgents()
{
    for(auto agent : busyAgents)
    {
        agent.reset();
    }
    busyAgents.clear();
}

void Instance::freeAgent(std::shared_ptr<Agent> agent)
{
    busyAgents.erase(std::remove(busyAgents.begin(), busyAgents.end(), agent), busyAgents.end());
    idUsed[agent->getSeed() % maxPopulation] = false;
    agent.reset();
}

std::vector<std::shared_ptr<Agent>> Instance::getBusyAgents() const
{
    return busyAgents;
}

Instance::~Instance()
{
    // Destructor
}
