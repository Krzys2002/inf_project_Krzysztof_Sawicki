//
// Created by Krzysztof Sawicki on 17/05/2024.
//

#ifndef INF_PROJECT_INSTANCE_H
#define INF_PROJECT_INSTANCE_H

#include "GameObject.h"
#include "Agent.h"
#include <string>
#include <vector>
#include "WorldSettings.h"

class Agent;  // Forward declaration of Agent

class Instance : public GameObject, public std::enable_shared_from_this<Instance>
{
protected:
    std::string description;
    const WorldSettings& worldSettings;
    unsigned int dayCounter = 0;
    unsigned int seed;
    unsigned int maxPopulation;
    std::shared_ptr<Instance> parentInstance;
    bool hasIndependentPopulation;
    std::vector<std::shared_ptr<Instance>> childrenInstances;
    std::vector<std::shared_ptr<Agent>> busyAgents;
    std::vector<unsigned int> idPool;
    std::vector<bool> idUsed;

public:
    // Constructor
    Instance(unsigned int seed, const WorldSettings& worldSettings, std::string name, std::shared_ptr<Instance> parentInstance, bool hasIndependentPopulation = false);

    // Destructor
    ~Instance();

    // Ready call on start of the game
    void ready() override;

    // RoundUpdate call on every round
    void roundUpdate(TimeSpace::GameTimeSystem& gameTime) override;

    // Get the parent instance
    std::shared_ptr<Instance> getParentInstance();
    // Get the children instances
    std::vector<std::shared_ptr<Instance>> getChildrenInstances();

    // Method to reserve ID pool for agents
    static std::vector<unsigned int> getIDPool(unsigned int size);

    // Get description of the instance
    virtual std::string getDescription() const;
    // Set description of the instance
    virtual void setDescription(const std::string& description);

    // Method to get agent from the instance if any free agent is available with seed (if not it returns nullptr)
    virtual std::shared_ptr<Agent> getFreeRandomAgent(unsigned int seed);
    // Method to get agent from the instance if any free agent is available (if not it returns nullptr)
    virtual std::shared_ptr<Agent> getFreeRandomAgent();

    // Method Free all agents from the instance
    virtual void freeAllAgents();
    // Method Free agent from the instance
    virtual void freeAgent(std::shared_ptr<Agent> agent);
    // Method to get all busy agents from the instance
    virtual std::vector<std::shared_ptr<Agent>> getBusyAgents() const;
};


#endif //INF_PROJECT_INSTANCE_H
