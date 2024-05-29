//
// Created by Krzysztof Sawicki on 17/05/2024.
//

#include "../Headers/Instance.h"

Instance::Instance(unsigned int seed, std::string name, std::shared_ptr<Instance> parentInstance, bool hasIndependentPopulation) : GameObject(name), seed(seed)
{
    this->parentInstance = parentInstance;
    this->hasIndependentPopulation = hasIndependentPopulation;
    RandomNumberGenerator rng(seed);
    maxPopulation = rng.generate(100, 1000);
    for (int i = 0; i < 100; ++i)
    {
        seedTable.push_back(rng.generate());
        seedUsed.push_back(false);
    }
}

void Instance::Ready()
{
    // Ready
    // this check is necessary to set Ready only one time to any Agent
    if(hasIndependentPopulation)
    {
        // call Ready on all agents
        for (auto agent : busyAgents)
        {
            agent->Ready();
        }
    }
}

void Instance::RoundUpdate(const TimeSpace::GameTimeSystem* gameTime)
{
    // RoundUpdate
    if(hasIndependentPopulation)
    {
        for (auto agent : busyAgents)
        {
            agent->RoundUpdate(gameTime);
        }
    }
}

std::vector<std::shared_ptr<Instance>> Instance::getChildrenInstances()
{
    return childrenInstances;
}

std::shared_ptr<Instance> Instance::GetParentInstance()
{
    return parentInstance;
}

std::shared_ptr<Agent> Instance::getFreeRandomAgent(unsigned int seed)
{
    if(hasIndependentPopulation)
    {
        if (busyAgents.size() >= maxPopulation)
        {
            return nullptr;
        }

        RandomNumberGenerator rng(seed);
        seed = rng.generate();

        std::shared_ptr<Agent> agent = std::make_shared<Agent>(seed, GameNameHolder::GetRandomAgentName(seed), this);
        busyAgents.emplace_back(agent);
        return agent;
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
            agent->SetInstance(this);
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
