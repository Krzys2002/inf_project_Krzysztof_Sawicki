//
// Created by Krzysztof Sawicki on 01/06/2024.
//

#ifndef INF_PROJECT_SPELL_H
#define INF_PROJECT_SPELL_H

#include <string>
#include <nlohmann/json.hpp>
#include <utility>

using json = nlohmann::json;

class Spell
{
    // name of the spell
    std::string name;
    // how much mana the spell costs
    int manaCost;
    // how difficult the spell is to get proficient at
    int complexity;

public:
    Spell() = default;
    Spell(std::string name, int manaCost, int complexity);
    virtual std::string getName() const;
    virtual int getManaCost() const;
    virtual int getComplexity() const;
    virtual void from_json(const json& j);
};

class AttackSpell : public Spell
{
    // how much damage the spell does
    int damage;
public:
    AttackSpell(std::string name, int manaCost, int complexity, int damage);
    AttackSpell(const json& j);
    int getDamage() const;
    void from_json(const json& j) override;
};

class HealingSpell : public Spell
{
    // how much the spell heals
    int power;

public:
    HealingSpell(std::string name, int manaCost, int complexity, int power);
    HealingSpell(const json& j);
    int getPower() const;
    void from_json(const json& j) override;
};

class DefenseSpell : public Spell
{
    // how much the spell protects
    int protection;
    // how long the spell lasts
    int duration;

public:
    DefenseSpell(std::string name, int manaCost, int complexity, int protection, int duration);
    DefenseSpell(const json& j);
    int getProtection() const;
    int getDuration() const;
    void from_json(const json& j) override;
};



#endif //INF_PROJECT_SPELL_H
