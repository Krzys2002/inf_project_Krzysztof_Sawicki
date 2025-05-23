//
// Created by Krzysztof Sawicki on 22/05/2024.
//

#ifndef INF_PROJECT_CITY_H
#define INF_PROJECT_CITY_H

#include "Instance.h"
#include "Tavern.h"
#include "GameNameHolder.h"
#include "Square.h"
#include "PlayerMagicSchool.h"

class MagicSchool;
class PlayerMagicSchool;

class City : public Instance
{
    // list of free agents
    // save in memory because of tack or student of school
    std::vector<std::shared_ptr<Agent>> freeAgents;
public:
    // Constructor
    City(unsigned int seed, std::string name, std::shared_ptr<Instance> parentInstance = nullptr, bool hasIndependentPopulation = true);

    // Destructor
    ~City();

    // Ready call on start of the game
    void ready() override;

    // Method to get agent from the instance if any free agent is available with seed (if not it returns nullptr)
    std::shared_ptr<Agent>& getFreeRandomAgent(unsigned int seed) override;
    // Method to get agent from the instance if any free agent is available (if not it returns nullptr)
    std::shared_ptr<Agent>& getFreeRandomAgent() override;

    // Method Free all agents from the instance
    void freeAllAgents() override;
    // Method Free agent from the instance
    void freeAgent(std::shared_ptr<Agent> agent) override;
    // Method to get all busy agents from the instance
    std::vector<std::shared_ptr<Agent>> getBusyAgents() const override;

    std::shared_ptr<Tavern> CreateTavern();
    std::shared_ptr<Tavern> CreateTavern(unsigned int seed);

    std::shared_ptr<Square> CreateSquare();
    std::shared_ptr<Square> CreateSquare(unsigned int seed);

    std::shared_ptr<MagicSchool> CreateMagicSchool();
    std::shared_ptr<MagicSchool> CreateMagicSchool(unsigned int seed);

    std::shared_ptr<PlayerMagicSchool> CreatePlayerMagicSchool();

    std::vector<std::shared_ptr<Tavern>> getTaverns();

    std::vector<std::shared_ptr<Square>> getSquares();

    std::vector<std::shared_ptr<MagicSchool>> getMagicSchools();

};


#endif //INF_PROJECT_CITY_H
