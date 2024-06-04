//
// Created by Krzysztof Sawicki on 30/05/2024.
//

#include "../Headers/Square.h"

Square::Square(unsigned int seed, std::string name, std::shared_ptr<Instance> parentInstance) : Instance(seed, name, parentInstance, false)
{
    // Constructor
    RandomNumberGenerator rng(seed);
    maxPopulation = WorldSettings::GetSquarePopulation() + (WorldSettings::GetSquarePopulation()
                                                           * rng.generateFloat(-WorldSettings::GetAberration(),
                                                                               WorldSettings::GetAberration()));
}

Square::~Square()
{
    // Destructor
}

void Square::ready()
{
    for (int i = 0; i < maxPopulation; ++i)
    {
        auto agent = parentInstance->getFreeRandomAgent(seed + busyAgents.size());
        if (agent != nullptr)
        {
            agent->setInstance(std::static_pointer_cast<Instance>(shared_from_this()));
            busyAgents.push_back(agent);
        }
    }
}

void Square::roundUpdate(TimeSpace::GameTimeSystem& gameTime)
{
    // Method to update every round
    Instance::roundUpdate(gameTime);

    RandomNumberGenerator rng(seed * gameTime.getDayFromStart());

    for (auto& agent : busyAgents)
    {
        parentInstance->freeAgent(agent);
    }
    busyAgents.clear();

    for (int i = 0; i < maxPopulation; ++i)
    {
        auto agent = parentInstance->getFreeRandomAgent(seed + busyAgents.size() + gameTime.getDayFromStart());
        if (agent != nullptr)
        {
            agent->setInstance(std::static_pointer_cast<Instance>(shared_from_this()));
            busyAgents.push_back(agent);

            if(rng.generate(0, 100) < 75)
            {
                taskTable.emplace_back(agent->createTask());
            }
        }
    }

    for (auto& task : taskTable)
    {
        if(!task.lock() || task.lock()->isAccepted())
        {
            taskTable.erase(std::remove_if(taskTable.begin(), taskTable.end(), [task](const std::weak_ptr<Task>& other) {
                return task.lock() == other.lock();
            }), taskTable.end());
        }
    }
}