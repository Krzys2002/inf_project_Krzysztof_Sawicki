//
// Created by Krzysztof Sawicki on 02/06/2024.
//

#include "../Headers/Teacher.h"

Teacher::Teacher(unsigned int seed, std::string name, std::shared_ptr<Instance> parentInstance) : Agent(seed, name,
                                                                                                        parentInstance)
{
    // Constructor
}

Teacher::Teacher(const Agent& agent) : Agent(agent)
{
    // Constructor
}

Teacher::~Teacher()
{
    // Destructor
}

void Teacher::ready()
{
    // Ready
    Agent::ready();
}

void Teacher::roundUpdate(TimeSpace::GameTimeSystem& gameTime)
{
    // RoundUpdate
    Agent::roundUpdate(gameTime);

    // Teach students
    for(auto student : students)
    {
        // Teach all spells
        for(auto spell : magicAbility.getLearnedSpells())
        {
            student.lock()->getMagicAbility()->addExpToSpell(spell, magicAbility.getSpellProficiency(spell));
        }
    }
}

void Teacher::addStudent(std::shared_ptr<Agent> student)
{
    // Add student
    students.emplace_back(student);
}
