//
// Created by Krzysztof Sawicki on 01/06/2024.
//

#ifndef INF_PROJECT_MAGICABILITY_H
#define INF_PROJECT_MAGICABILITY_H


#include "Spell.h"
#include <map>
#include <vector>
#include <memory>
#include <utility>

class MagicAbility
{
    // how good the character is at magic
    int talent;
    // list of spells the character has learned
    std::vector<std::shared_ptr<Spell>> learnedSpells;
    // proficiency and experience for each spell
    std::map<std::shared_ptr<Spell>, int> spellProficiency;
    std::map<std::shared_ptr<Spell>, int> spellExp;

public:
    MagicAbility() = default;
    explicit MagicAbility(int talent);
    void setTalent(int talent);
    void learnSpell(std::weak_ptr<Spell> spell);
    void addExpToSpell(std::weak_ptr<Spell> spell, int amount);

    int getTalent() const;
    int getSpellProficiency(const std::weak_ptr<Spell>& spell) const;
    int getSpellExp(const std::weak_ptr<Spell>& spell) const;

    bool canCastSpell(const std::weak_ptr<Spell>& spell) const;
    std::vector<std::weak_ptr<Spell>> getLearnedSpells() const;
};


#endif //INF_PROJECT_MAGICABILITY_H
