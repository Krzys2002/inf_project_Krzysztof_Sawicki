//
// Created by Krzysztof Sawicki on 28/05/2024.
//

#include "../Headers/Tavern.h"

Tavern::Tavern(unsigned int seed, std::string name, std::shared_ptr<Instance> parentInstance) : Instance(seed, name, parentInstance,false)
{
    // Constructor
    RandomNumberGenerator rng(seed);
    maxPopulation = WorldSettings::GetTavernPopulation() + (WorldSettings::GetTavernPopulation()
                                                           * rng.generateFloat(-WorldSettings::GetAberration(),
                                                                               WorldSettings::GetAberration()));
}

Tavern::~Tavern() = default;

void Tavern::ready()
{
    mainProfession = static_cast<Professions>(seed % static_cast<int>(Professions::Count));
    setDescription(GameNameHolder::getRandomTavernDescription(seed, mainProfession));


    for (int i = 0; i < maxPopulation; ++i)
    {
        auto agent = parentInstance->getFreeRandomAgent(seed + busyAgents.size());
        if (agent != nullptr)
        {
            agent->setInstance(std::static_pointer_cast<Instance>(shared_from_this()));
            busyAgents.push_back(agent);
            agent->setMainProfession(mainProfession);
            agent->createMagicAbility();
        }
    }
}

void Tavern::roundUpdate(TimeSpace::GameTimeSystem& gameTime)
{
    Instance::roundUpdate(gameTime);
    // Method to update every round
    for (auto& agent : busyAgents)
    {
        parentInstance->freeAgent(agent);
    }
    busyAgents.clear();

    for (int i = 0; i < maxPopulation; ++i)
    {
        auto agent = parentInstance->getFreeRandomAgent((seed + dayCounter  + busyAgents.size()) * dayCounter);
        if (agent != nullptr)
        {
            agent->setInstance(std::static_pointer_cast<Instance>(shared_from_this()));
            busyAgents.push_back(agent);
            agent->setMainProfession(mainProfession);
            agent->createMagicAbility();
        }
    }
}