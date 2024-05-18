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
    Instance* currentInstance;
    const unsigned int seed;
public:
    // Constructor
    Agent(unsigned int seed, std::string name, Instance* currentInstance);

    // Destructor
    ~Agent();

    // Get the current instance
    Instance* GetCurrentInstance() const;
    // get the seed of the agent
    unsigned int GetSeed() const;

    // Set the current instance
    void SetInstance(Instance* newInstance);
};


#endif //INF_PROJECT_AGENT_H
