//
// Created by Krzysztof Sawicki on 30/05/2024.
//

#ifndef INF_PROJECT_PROFESSION_H
#define INF_PROJECT_PROFESSION_H

#include <string>

enum class Professions
{
    Apothecary,
    Healer,
    Support,
    Scholarly,
    Magical,
    Adventurer,
    Merchant,
    Miscellaneous,
    MagicStudent,
    Count
};

std::string professionToString(Professions profession);


#endif //INF_PROJECT_PROFESSION_H
