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

    std::string description;

    // Main professions of Agent
    Professions mainProfession;
    // Secondary professions of Agent
    Professions secondaryProfession;
public:
    // Constructor
    Agent(unsigned int seed, std::string name, std::shared_ptr<Instance> currentInstance);
    Agent(unsigned int ID, unsigned int seed, std::string name, std::shared_ptr<Instance> currentInstance);

    // Destructor
    ~Agent();

    // Update every Round
    void roundUpdate(TimeSpace::GameTimeSystem& gameTime) override;

    // Get the current instance
    std::shared_ptr<Instance> getCurrentInstance() const;
    // get the seed of the agent
    unsigned int getSeed() const;

    // Set the current instance
    void setInstance(std::shared_ptr<Instance> newInstance);

    // Get the main profession of the agent
    Professions getMainProfession() const;
    // Get the secondary profession of the agent
    Professions getSecondaryProfession() const;

    // Set the main profession of the agent
    void setMainProfession(Professions profession);
    // Set the secondary profession of the agent
    void setSecondaryProfession(Professions profession);

    // Get the description of the agent
    std::string getDescription() const;
};


#endif //INF_PROJECT_AGENT_H
