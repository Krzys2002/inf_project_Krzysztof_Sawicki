//
// Created by Krzysztof Sawicki on 17/05/2024.
//

#ifndef INF_PROJECT_GAMENAMEHOLDER_H
#define INF_PROJECT_GAMENAMEHOLDER_H

#include <string>
#include <vector>

class GameNameHolder
{
public:
    static std::vector<std::string> InstancesNames;
    static std::vector<std::string> AgentsNames;

    static std::string GetRandomInstanceName(unsigned int seed = 0);
    static std::string GetRandomAgentName(unsigned int seed = 0);
    static std::string GetRandomTavernName(unsigned int seed = 0);
};

#endif //INF_PROJECT_GAMENAMEHOLDER_H
