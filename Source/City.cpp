//
// Created by Krzysztof Sawicki on 22/05/2024.
//

#include "../Headers/City.h"

City::City(unsigned int seed, std::string name, std::shared_ptr<Instance> parentInstance, bool hasIndependentPopulation) : Instance(seed, name, parentInstance, hasIndependentPopulation)
{
    RandomNumberGenerator rng(seed);
    maxPopulation = WorldSettings::GetCityPopulation() + (WorldSettings::GetCityPopulation()
                                                         * rng.generateFloat(-WorldSettings::GetAberration(),
                                                                             WorldSettings::GetAberration()));
}

City::~City()
{
    // Destructor
}

void City::ready()
{
    // Ready
}

/// <summary>
/// Method to free all agents from the instance
/// Work in progress
/// </summary>
void City::freeAllAgents()
{
    for(auto agent : busyAgents)
    {
        agent.reset();
    }

    idUsed = std::vector<bool>(maxPopulation, false);
    busyAgents.clear();
}

void City::freeAgent(std::shared_ptr<Agent> agent)
{
    // check if agent has task or is a student
    if(agent->hasTask() || agent->getSecondaryProfession() == Professions::MagicStudent)
    {
        // if agent has task or is a student, set the instance to the agent
        agent->setInstance(std::static_pointer_cast<Instance>(shared_from_this()));
        // remove agent from the busyAgents list
        busyAgents.erase(std::remove(busyAgents.begin(), busyAgents.end(), agent), busyAgents.end());
        // add agent to the freeAgents list
        freeAgents.push_back(agent);
        // and return
        return;
    }

    // Method Free agent from the instance
    Instance::freeAgent(agent);
}

std::vector<std::shared_ptr<Agent>> City::getBusyAgents() const
{
    // Method to get all busy agents from the instance
    return busyAgents;
}

std::shared_ptr<Agent>& City::getFreeRandomAgent()
{
    // Method to get agent from the instance if any free agent is available (if not it returns nullptr)
    return Instance::getFreeRandomAgent();
}

std::shared_ptr<Agent>& City::getFreeRandomAgent(unsigned int seed)
{
    // Method to get agent from the instance if any free agent is available with seed
    auto findAt = std::find_if(freeAgents.begin(), freeAgents.end(), [seed](std::shared_ptr<Agent> agent) {
        return agent->getSeed() == seed;
    });

    // check if agent is in the freeAgents list
    if(findAt != freeAgents.end())
    {
        auto& agent = *findAt;
        freeAgents.erase(findAt);
        busyAgents.push_back(agent);
        return agent;
    }

    // Method to get agent from the instance if any free agent is available with seed (if not it returns nullptr)
    return Instance::getFreeRandomAgent(seed);
}

std::shared_ptr<Tavern> City::CreateTavern(unsigned int seed)
{
    // Method to create tavern
    auto tavern = std::make_shared<Tavern>(seed, GameNameHolder::getRandomTavernName(seed),
                                           std::static_pointer_cast<Instance>(shared_from_this()));
    childrenInstances.push_back(tavern);
    return tavern;
}

std::shared_ptr<Tavern> City::CreateTavern()
{
    unsigned int seed = this->seed + childrenInstances.size() + dayCounter;
    // Method to create tavern
    return CreateTavern(seed);
}

std::shared_ptr<Square> City::CreateSquare(unsigned int seed)
{
    // Method to create square
    auto square = std::make_shared<Square>(seed, GameNameHolder::getRandomSquareName(seed),
                                           std::static_pointer_cast<Instance>(shared_from_this()));
    childrenInstances.push_back(square);
    return square;
}

std::shared_ptr<Square> City::CreateSquare()
{
    unsigned int seed = this->seed + childrenInstances.size() + dayCounter;
    // Method to create square
    return CreateSquare(seed);
}

std::vector<std::shared_ptr<Tavern>> City::getTaverns()
{
    // Method to get all taverns from the instance
    std::vector<std::shared_ptr<Tavern>> taverns;
    for(auto& instance : childrenInstances)
    {
        if(auto tavern = std::dynamic_pointer_cast<Tavern>(instance))
        {
            taverns.emplace_back(tavern);
        }
    }

    return taverns;
}

std::vector<std::shared_ptr<Square>> City::getSquares()
{
    // Method to get all squares from the instance
    std::vector<std::shared_ptr<Square>> squares;
    for(auto& instance : childrenInstances)
    {
        if(auto square = std::dynamic_pointer_cast<Square>(instance))
        {
            squares.emplace_back(square);
        }
    }

    return squares;
}

std::shared_ptr<MagicSchool> City::CreateMagicSchool(unsigned int seed)
{
    // Method to create magic school
    auto magicSchool = std::make_shared<MagicSchool>(seed, GameNameHolder::getRandomMagicSchoolName(seed),
                                                     std::static_pointer_cast<Instance>(shared_from_this()));

    magicSchool->CreateTeacher();
    magicSchool->setMinTalent(WorldSettings::GetMinTalentForSchool());
    childrenInstances.emplace_back(magicSchool);
    return magicSchool;
}

std::shared_ptr<MagicSchool> City::CreateMagicSchool()
{
    unsigned int seed = this->seed + childrenInstances.size() + dayCounter;
    // Method to create magic school
    return CreateMagicSchool(seed);
}



