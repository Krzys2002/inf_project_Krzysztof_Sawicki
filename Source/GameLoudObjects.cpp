//
// Created by Krzysztof Sawicki on 08/06/2024.
//

#include "../Headers/GameLoudObjects.h"
#include "RandomNumberGenerator.cpp"
#include "../Headers/Spell.h"


std::vector<std::shared_ptr<Spell>> GameLoudObject::Spells;

void GameLoudObject::LoudSpellsFromFile(std::string &path)
{
    // Open the JSON file
    std::ifstream file(path);

    // Parse the JSON file
    json j;
    file >> j;

    // Get the spells category
    auto spells = j.at("spells");

    // Loop over the spells in the JSON file
    for (const auto& spell : spells)
    {
        // Get the type of the spell
        std::string type = spell.at("type").get<std::string>();

        // Create the appropriate spell based on the type
        if (type == "attack")
        {
            Spells.push_back(std::make_shared<AttackSpell>(spell));
        }
        else if (type == "healing")
        {
            Spells.push_back(std::make_shared<HealingSpell>(spell));
        }
        else if (type == "defense")
        {
            Spells.push_back(std::make_shared<DefenseSpell>(spell));
        }
    }
}

std::vector<std::shared_ptr<Spell>>& GameLoudObject::GetSpells()
{
    return Spells;
}

std::shared_ptr<Spell> GameLoudObject::GetRandomSpell()
{
    return Spells[RandomNumberGenerator::Generate(0, Spells.size() - 1)];
}

std::shared_ptr<Spell> GameLoudObject::GetSpellByName(std::string name)
{
    auto findAt = std::find_if(Spells.begin(), Spells.end(), [&name](std::shared_ptr<Spell> spell){
        return spell->getName() == name;
    });

    if(findAt != Spells.end())
    {
        return *findAt;
    }

    return nullptr;
}