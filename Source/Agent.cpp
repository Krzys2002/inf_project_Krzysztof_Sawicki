//
// Created by Krzysztof Sawicki on 17/05/2024.
//

#include "../Headers/Agent.h"

Agent::Agent(unsigned int seed, std::string name, std::shared_ptr<Instance> currentInstance) : GameObject(name), seed(seed)
{
    this->currentInstance = currentInstance;
}

Agent::Agent(unsigned int ID, unsigned int seed, std::string name, std::shared_ptr<Instance> currentInstance) : GameObject(ID, name), seed(seed)
{
    this->currentInstance = currentInstance;
}

unsigned int Agent::getSeed() const
{
    return seed;
}

Agent::~Agent()
{
    // Destructor
}

void Agent::roundUpdate(TimeSpace::GameTimeSystem& gameTime)
{
    // RoundUpdate
}

std::shared_ptr<Instance> Agent::getCurrentInstance() const
{
    return currentInstance;
}

void Agent::setInstance(std::shared_ptr<Instance> newInstance)
{
    currentInstance = newInstance;
}

Professions Agent::getMainProfession() const
{
    return mainProfession;
}

Professions Agent::getSecondaryProfession() const
{
    return secondaryProfession;
}

void Agent::setMainProfession(Professions profession)
{
    mainProfession = profession;
    description = GameNameHolder::getRandomAgentDescription(seed, mainProfession);
}

void Agent::setSecondaryProfession(Professions profession)
{
    secondaryProfession = profession;
}

std::string Agent::getDescription() const
{
    return description;
}

