//
// Created by Krzysztof Sawicki on 01/06/2024.
//

#include "../Headers/MagicAbility.h"

MagicAbility::MagicAbility(int talent) : talent(talent) {}

void MagicAbility::learnSpell(std::weak_ptr<Spell> spell)
{
    learnedSpells.push_back(spell.lock());
    spellProficiency[spell.lock()] = 0;
    spellExp[spell.lock()] = 0;
}

void MagicAbility::addExpToSpell(std::weak_ptr<Spell> spell, int amount)
{
    if(std::find(learnedSpells.begin(), learnedSpells.end(), spell.lock()) == learnedSpells.end())
    {
        learnedSpells.push_back(spell.lock());
    }

    spellExp[spell.lock()] += amount * talent;
    if (spellExp[spell.lock()] >= (spellProficiency[spell.lock()] * spell.lock()->getComplexity()) + 1)
    {
        spellProficiency[spell.lock()]++;
        spellExp[spell.lock()] = 0;
    }
}

int MagicAbility::getTalent() const
{
    return talent;
}

int MagicAbility::getSpellProficiency(const std::weak_ptr<Spell>& spell) const
{
    return spellProficiency.at(spell.lock());
}

int MagicAbility::getSpellExp(const std::weak_ptr<Spell>& spell) const
{
    return spellExp.at(spell.lock());
}

bool MagicAbility::canCastSpell(const std::weak_ptr<Spell>& spell) const
{
    return std::find(learnedSpells.begin(), learnedSpells.end(), spell.lock()) != learnedSpells.end();
}

void MagicAbility::setTalent(int talent)
{
    MagicAbility::talent = talent;
}

std::vector<std::weak_ptr<Spell>> MagicAbility::getLearnedSpells() const
{
    std::vector<std::weak_ptr<Spell>> w_learnedSpells(learnedSpells.begin(), learnedSpells.end());
    return w_learnedSpells;
}


