//
// Created by Krzysztof Sawicki on 01/06/2024.
//

#include "../Headers/Spell.h"


Spell::Spell(std::string name, int manaCost, int complexity) : name(std::move(name)), manaCost(manaCost), complexity(complexity) {}

std::string Spell::getName() const
{
    return name;
}

int Spell::getManaCost() const
{
    return manaCost;
}

int Spell::getComplexity() const
{
    return complexity;
}

void Spell::from_json(const json& j)
{
    name = j.at("name").get<std::string>();
    manaCost = j.at("manaCost").get<int>();
    complexity = j.at("complexity").get<int>();
}

AttackSpell::AttackSpell(std::string name, int manaCost, int complexity, int damage) : Spell(name, manaCost, complexity), damage(damage) {}
AttackSpell::AttackSpell(const json& j)
{
    from_json(j);
}

int AttackSpell::getDamage() const
{
    return damage;
}

void AttackSpell::from_json(const json& j)
{
    Spell::from_json(j);
    damage = j.at("damage").get<int>();
}

HealingSpell::HealingSpell(std::string name, int manaCost, int complexity, int power) : Spell(name, manaCost, complexity), power(power) {}
HealingSpell::HealingSpell(const json& j)
{
    from_json(j);
}

int HealingSpell::getPower() const
{
    return power;
}

void HealingSpell::from_json(const json& j)
{
    Spell::from_json(j);
    power = j.at("power").get<int>();
}

DefenseSpell::DefenseSpell(std::string name, int manaCost, int complexity, int protection, int duration) : Spell(name, manaCost, complexity), protection(protection), duration(duration) {}
DefenseSpell::DefenseSpell(const json& j)
{
    from_json(j);
}


int DefenseSpell::getProtection() const
{
    return protection;
}

int DefenseSpell::getDuration() const
{
    return duration;
}

void DefenseSpell::from_json(const json& j)
{
    Spell::from_json(j);
    protection = j.at("protection").get<int>();
    duration = j.at("duration").get<int>();
}


