//
// Created by Krzysztof Sawicki on 02/06/2024.
//

#ifndef INF_PROJECT_MAGICSCHOOL_H
#define INF_PROJECT_MAGICSCHOOL_H

#include "Instance.h"
#include "Teacher.h"
#include <vector>
#include <memory>
#include <map>

class MagicSchool : public Instance
{
    // minimum talent required to be a student
    unsigned int minTalent;

protected:
    // Teachers of the Magic School
    std::vector<std::shared_ptr<Teacher>> teachers;
    // Students of the Magic School
    std::vector<std::shared_ptr<Agent>> students;
    // Spellbook of the Magic School
    std::vector<std::weak_ptr<Spell>> spellbook;

public:
    // Constructor
    MagicSchool(unsigned int seed, std::string name, std::shared_ptr<Instance> parentInstance = nullptr);

    // Destructor
    ~MagicSchool();

    // Ready call on start of the game
    void ready() override;

    // RoundUpdate call on every round
    void roundUpdate(TimeSpace::GameTimeSystem& gameTime) override;

    // Create Teacher for the Magic School
    void CreateTeacher();

    // geters
    std::vector<std::shared_ptr<Agent>> getTeachers() const;
    std::vector<std::shared_ptr<Agent>> getStudents() const;
    unsigned int getMinTalent() const;

    void setMinTalent(unsigned int minTalent);
    virtual void addSpell(std::weak_ptr<Spell> spell);
};


#endif //INF_PROJECT_MAGICSCHOOL_H
