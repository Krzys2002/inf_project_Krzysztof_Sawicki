//
// Created by Krzysztof Sawicki on 08/06/2024.
//

#ifndef INF_PROJECT_GAMELOUDOBJECTS_H
#define INF_PROJECT_GAMELOUDOBJECTS_H

#include <vector>
#include <memory>
#include <fstream>

class Spell;

class GameLoudObject
{
    // Spells
    static std::vector<std::shared_ptr<Spell>> Spells;


public:
    // Load spells from file
    static void LoudSpellsFromFile(std::string& path);

    // Get spells
    static std::vector<std::shared_ptr<Spell>>& GetSpells();
    static std::shared_ptr<Spell> GetRandomSpell();
    static std::shared_ptr<Spell> GetSpellByName(std::string name);

    // Resources
    enum class ResourceType
    {
        Gold,
        MagicStone,
        Count
    };
};


#endif //INF_PROJECT_GAMELOUDOBJECTS_H
