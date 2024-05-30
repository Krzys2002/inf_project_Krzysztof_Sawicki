//
// Created by Krzysztof Sawicki on 17/05/2024.
//

#ifndef INF_PROJECT_GAMENAMEHOLDER_H
#define INF_PROJECT_GAMENAMEHOLDER_H

#include <string>
#include <vector>
#include "Profession.h"

namespace GameNameHolder
{
    std::string getRandomAgentName(unsigned int nameNumber);
    std::string getRandomTavernName(unsigned int nameNumber);
    std::string getRandomTavernHealerDescription(unsigned int descriptionNumber);
    std::string getRandomTavernAdventurerDescription(unsigned int descriptionNumber);
    std::string getRandomTavernMerchantDescription(unsigned int descriptionNumber);
    std::string getRandomTavernScholarDescription(unsigned int descriptionNumber);
    std::string getRandomTavernSupportDescription(unsigned int descriptionNumber);
    std::string getRandomTavernApothecaryDescription(unsigned int descriptionNumber);
    std::string getRandomTavernMageDescription(unsigned int descriptionNumber);
    std::string getRandomTavernMiscellaneousDescription(unsigned int descriptionNumber);

    std::string getRandomApothecaryDescription(unsigned int descriptionNumber);
    std::string getRandomHealerDescription(unsigned int descriptionNumber);
    std::string getRandomSupportDescription(unsigned int descriptionNumber);
    std::string getRandomScholarlyDescription(unsigned int descriptionNumber);
    std::string getRandomMagicalDescription(unsigned int descriptionNumber);
    std::string getRandomAdventurerDescription(unsigned int descriptionNumber);
    std::string getRandomMerchantDescription(unsigned int descriptionNumber);
    std::string getRandomMiscellaneousDescription(unsigned int descriptionNumber);

    std::string getRandomCityName(unsigned int nameNumber);

    std::string getRandomSquareName(unsigned int nameNumber);

    std::string getRandomTavernDescription(unsigned int descriptionNumber, Professions profession);
    std::string getRandomAgentDescription(unsigned int descriptionNumber, Professions profession);


}

#endif //INF_PROJECT_GAMENAMEHOLDER_H
