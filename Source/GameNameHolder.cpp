//
// Created by Krzysztof Sawicki on 17/05/2024.
//

#include <string>
#include <vector>

namespace GameNameHolder
{
    std::vector<std::string> AgentsNames = {"Frankie", "Cree", "Thornton", "Blessing", "Ernest",
                                            "Todd", "Harve", "Micah", "Stan", "Tennyson", "Geoff",
                                            "Page", "Laird", "Rain", "Reece", "Regan", "Randolph",
                                            "Esmé", "Kolton", "Kirby", "Kendall", "Kendrick", "Kendall",
                                            "Kendrick", "Kendall", "Kendrick", "Kendall", "Kendrick"};
    std::vector<std::string> InstancesNames = {"Instance1", "Instance2", "Instance3", "Instance4", "Instance5"};

    std::string GetRandomAgentName(unsigned int nameNumber)
    {
        return AgentsNames[nameNumber % AgentsNames.size()];
    }

    std::string GetRandomInstanceName(unsigned int nameNumber)
    {
        return InstancesNames[nameNumber % InstancesNames.size()];
    }
}