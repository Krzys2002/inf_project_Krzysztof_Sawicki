//
// Created by Krzysztof Sawicki on 30/05/2024.
//

#include "../Headers/Profession.h"



std::string professionToString(Professions profession)
{
    switch (profession) {
        case Professions::Apothecary:
            return "Apothecary";
        case Professions::Healer:
            return "Healer";
        case Professions::Support:
            return "Support";
        case Professions::Scholarly:
            return "Scholarly";
        case Professions::Magical:
            return "Magical";
        case Professions::Adventurer:
            return "Adventurer";
        case Professions::Merchant:
            return "Merchant";
        case Professions::Miscellaneous:
            return "Miscellaneous";
        case Professions::MagicStudent:
            return "MagicStudent";
        default:
            return "Invalid";
    }
}