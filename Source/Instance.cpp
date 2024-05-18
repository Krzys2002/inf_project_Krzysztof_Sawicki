//
// Created by Krzysztof Sawicki on 17/05/2024.
//

#include "../Headers/Instance.h"

Instance::Instance(unsigned int seed, std::string name, Instance* parentInstance, bool hasIndependentPopulation) : GameObject(name)
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

Instance* Instance::GetParentInstance() const
{
    return parentInstance;
}

Agent* Instance::getFreeRandomAgent(unsigned int seed)
{
    if(hasIndependentPopulation)
    {
        if (busyAgents.size() >= maxPopulation)
        {
            return nullptr;
        }

        RandomNumberGenerator rng(seed);
        unsigned int index = RandomNumberGenerator::getRandomIndex(&rng, seedUsed);
        seedUsed[index] = true;
        rng = RandomNumberGenerator(seedTable[index]);

        Agent *agent = new Agent(seedTable[index], GameNameHolder::GetRandomAgentName(rng.generate()), this);
        busyAgents.push_back(agent);
        return agent;
    }
    else
    {
        if (parentInstance == nullptr)
        {
            return nullptr;
        }

        Agent* agent = parentInstance->getFreeRandomAgent(seed);
        if(agent != nullptr)
        {
            agent->SetInstance(this);
            busyAgents.push_back(agent);
            return agent;
        }
    }
}

Agent* Instance::getFreeRandomAgent()
{
    RandomNumberGenerator rng;
    return getFreeRandomAgent(rng.generate());
}

void Instance::freeAllAgents()
{
    for(auto agent : busyAgents)
    {
        delete agent;
    }
    busyAgents.clear();
}

void Instance::freeAgent(Agent* agent)
{
    busyAgents.erase(std::remove(busyAgents.begin(), busyAgents.end(), agent), busyAgents.end());
    delete agent;
}

std::vector<Agent*> Instance::getBusyAgents() const
{
    return busyAgents;
}

Instance::~Instance()
{
    for(auto agent : busyAgents)
    {
        delete agent;
    }

    for(auto instance : childrenInstances)
    {
        delete instance;
    }
}
