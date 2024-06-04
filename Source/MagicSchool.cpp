//
// Created by Krzysztof Sawicki on 02/06/2024.
//

#include "../Headers/MagicSchool.h"


MagicSchool::MagicSchool(unsigned int seed, std::string name, std::shared_ptr<Instance> parentInstance) : Instance(seed, name, parentInstance)
{
    // Constructor
}

MagicSchool::~MagicSchool()
{
    // Destructor
}

void MagicSchool::ready()
{
    // Ready
    Instance::ready();
}

void MagicSchool::roundUpdate(TimeSpace::GameTimeSystem& gameTime)
{
    // RoundUpdate
    Instance::roundUpdate(gameTime);

    RandomNumberGenerator rng(seed);

    // get all Taverns in the parentInstance
    auto city = std::dynamic_pointer_cast<City>(parentInstance);
    auto taverns = city->getTaverns();

    // recruit students from random taverns
    for(int i = 0; i < teachers.size(); ++i)
    {
        auto teacher = teachers[i];
        auto tavern = taverns[rng.generate(0, taverns.size() - 1)];
        teacher->setInstance(tavern);

        // recruit students
        for(auto agent : tavern->getBusyAgents())
        {
            if(agent->getMagicAbility()->getTalent() >= minTalent)
            {
                teacher->addStudent(agent);
                tavern->transferAgent(agent, shared_from_this());
            }
        }
    }
}

void MagicSchool::CreateTeacher()
{
    // Create Teacher
    std::shared_ptr<Agent>& agent = parentInstance->getFreeRandomAgent();
    std::shared_ptr<Teacher> teacher = agent->transformToTeacher();
    teachers.emplace_back(teacher);
    teacher->setInstance(shared_from_this());

    agent = teacher;

    teacher->setMainProfession(Professions::Magical);

    teacher->createMagicAbility();
    teacher->getMagicAbility()->setTalent(10);
    for(auto spell : spellbook)
    {
        teacher->getMagicAbility()->addExpToSpell(spell, 10);

        while (teacher->getMagicAbility()->getSpellProficiency(spell) < 60)
        {
            teacher->getMagicAbility()->addExpToSpell(spell, 100);
        }
    }
}

void MagicSchool::setMinTalent(unsigned int minTalent)
{
    this->minTalent = minTalent;
}

std::vector<std::shared_ptr<Agent>> MagicSchool::getTeachers() const
{
    std::vector<std::shared_ptr<Agent>> a_teachers(teachers.begin(), teachers.end());
    return a_teachers;
}

std::vector<std::shared_ptr<Agent>> MagicSchool::getStudents() const
{
    return students;
}

unsigned int MagicSchool::getMinTalent() const
{
    return minTalent;
}

void MagicSchool::addSpell(std::weak_ptr<Spell> spell)
{
    spellbook.emplace_back(spell);
}

