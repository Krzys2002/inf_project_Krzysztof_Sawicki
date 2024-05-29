//
// Created by Krzysztof Sawicki on 28/05/2024.
//

#ifndef INF_PROJECT_TAVERN_H
#define INF_PROJECT_TAVERN_H

#include "Instance.h"

class Tavern : public Instance
{
public:
    // Constructor
    Tavern(unsigned int seed, std::string name, std::shared_ptr<Instance> parentInstance = nullptr);

    // Destructor
    ~Tavern();

    // Ready call on start of the game
    void Ready() override;

    // RoundUpdate call on every round
    void RoundUpdate(const TimeSpace::GameTimeSystem* gameTime) override;

};


#endif //INF_PROJECT_TAVERN_H
