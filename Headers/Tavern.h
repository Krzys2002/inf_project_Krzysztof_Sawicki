//
// Created by Krzysztof Sawicki on 28/05/2024.
//

#ifndef INF_PROJECT_TAVERN_H
#define INF_PROJECT_TAVERN_H

#include "Instance.h"

class Tavern : public Instance
{
    // main anent of profession of the Tavern
    Professions mainProfession;
    std::shared_ptr<Agent> tavernKeeper;
public:
    // Constructor
    Tavern(unsigned int seed, const WorldSettings& worldSettings, std::string name, std::shared_ptr<Instance> parentInstance = nullptr);

    // Destructor
    ~Tavern();

    // Ready call on start of the game
    void ready() override;

    // RoundUpdate call on every round
    void roundUpdate(TimeSpace::GameTimeSystem& gameTime) override;

};


#endif //INF_PROJECT_TAVERN_H
