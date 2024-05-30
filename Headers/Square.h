//
// Created by Krzysztof Sawicki on 30/05/2024.
//

#ifndef INF_PROJECT_SQUARE_H
#define INF_PROJECT_SQUARE_H

#include "Instance.h"

class Square : public Instance
{
    // Task Table for the Squer
    //std::vector<std::shared_ptr<Task>> taskTable;

public:
    // Constructor
    Square(unsigned int seed, const WorldSettings& worldSettings, std::string name, std::shared_ptr<Instance> parentInstance = nullptr);

    // Destructor
    ~Square();

    // Ready call on start of the game
    void ready() override;

    // RoundUpdate call on every round
    void roundUpdate(TimeSpace::GameTimeSystem& gameTime) override;
};


#endif //INF_PROJECT_SQUARE_H
