//
// Created by Krzysztof Sawicki on 17/05/2024.
//

#ifndef INF_PROJECT_INSTANCE_H
#define INF_PROJECT_INSTANCE_H

#include "GameObject.h"
#include "Agent.h"
#include <string>
#include <vector>

class Agent;  // Forward declaration of Agent

class Instance : public GameObject
{
protected:
    unsigned int maxPopulation;
    Instance* parentInstance;
    bool hasIndependentPopulation;
    std::vector<Instance*> childrenInstances;
    std::vector<Agent*> busyAgents;
    std::vector<unsigned int> seedTable;
    std::vector<bool> seedUsed;

public:
    // Constructor
    Instance(unsigned int seed, std::string name, Instance* parentInstance, bool hasIndependentPopulation = false);

    // Destructor
    ~Instance();

    // Get the parent instance
    Instance* GetParentInstance() const;

    // Method to get agent from the instance if any free agent is available with seed (if not it returns nullptr)
    virtual Agent* getFreeRandomAgent(unsigned int seed);
    // Method to get agent from the instance if any free agent is available (if not it returns nullptr)
    virtual Agent* getFreeRandomAgent();

    // Method Free all agents from the instance
    virtual void freeAllAgents();
    // Method Free agent from the instance
    virtual void freeAgent(Agent* agent);
    // Method to get all busy agents from the instance
    virtual std::vector<Agent*> getBusyAgents() const;
};


#endif //INF_PROJECT_INSTANCE_H
