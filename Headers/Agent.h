//
// Created by Krzysztof Sawicki on 17/05/2024.
//

#ifndef INF_PROJECT_AGENT_H
#define INF_PROJECT_AGENT_H

#include "GameObject.h"
#include "Instance.h"

class Instance;  // Forward declaration of Instance

class Agent : public GameObject
{
protected:
    std::shared_ptr<Instance> currentInstance;
    const unsigned int seed;
public:
    // Constructor
    Agent(unsigned int seed, std::string name, std::shared_ptr<Instance> currentInstance);
    Agent(unsigned int ID, unsigned int seed, std::string name, std::shared_ptr<Instance> currentInstance);

    // Destructor
    ~Agent();

    // Update every Round
    void RoundUpdate(TimeSpace::GameTimeSystem& gameTime) override;

    // Get the current instance
    std::shared_ptr<Instance> GetCurrentInstance() const;
    // get the seed of the agent
    unsigned int GetSeed() const;

    // Set the current instance
    void SetInstance(std::shared_ptr<Instance> newInstance);
};


#endif //INF_PROJECT_AGENT_H
