//
// Created by Krzysztof Sawicki on 05/06/2024.
//

#include "../Headers/PlayerMagicSchool.h"
#include "../Headers/MagicSchool.h"


PlayerMagicSchool::PlayerMagicSchool(unsigned int seed, std::string name, std::shared_ptr<Instance> parentInstance)
        : MagicSchool(seed, name, parentInstance)
{
    // Constructor
    resources.resize(static_cast<int>(GameLoudObject::ResourceType::Count));
}

void PlayerMagicSchool::roundUpdate(TimeSpace::GameTimeSystem &gameTime)
{
    MagicSchool::roundUpdate(gameTime);

    auto newTaskAssignment = taskAssignment;

    for(auto& task : taskAssignment)
    {
        task.second->makeProgress(task.first->getMagicAbility());

        if(task.second->isCompleted())
        {
            task.second.reset();
            newTaskAssignment.erase(task.first);
        }
    }

    taskAssignment = newTaskAssignment;
}

std::vector<std::shared_ptr<Task>> PlayerMagicSchool::getTasks()
{
    return taskTable;
}

std::map<std::shared_ptr<Agent>, std::shared_ptr<Task>> PlayerMagicSchool::getTaskAssignment()
{
    return taskAssignment;
}

std::vector<unsigned int> PlayerMagicSchool::getResources()
{
    return resources;
}

std::shared_ptr<Agent> PlayerMagicSchool::getHero()
{
    return hero;
}

void PlayerMagicSchool::setHero(std::shared_ptr<Teacher>& hero)
{
    this->hero = hero;
    teachers.emplace_back(hero);
    parentInstance->addAgentToBusy(hero);
    busyAgents.emplace_back(hero);
}

void PlayerMagicSchool::addSpell(std::weak_ptr<Spell> spell)
{
    MagicSchool::addSpell(spell);
}

void PlayerMagicSchool::addResource(int resource, unsigned int amaunt)
{
    resources[static_cast<int>(resource)] += amaunt;
}

void PlayerMagicSchool::addTask(std::shared_ptr<Task> task)
{
    taskTable.emplace_back(task);
}

void PlayerMagicSchool::addStudent(std::shared_ptr<Agent> student)
{
    busyAgents.emplace_back(student);
    student->getCurrentInstance()->transferAgent(student, std::static_pointer_cast<Instance>(shared_from_this()));
    students.emplace_back(student);

    teachers[0]->addStudent(student);
}

void PlayerMagicSchool::assignTask(std::shared_ptr<Agent> student, std::shared_ptr<Task> task)
{
    if(std::find(students.begin(), students.end(), student) != students.end() && std::find(taskTable.begin(), taskTable.end(), task) != taskTable.end())
    {
        taskTable.erase(std::remove(taskTable.begin(), taskTable.end(), task), taskTable.end());
        taskAssignment[student] = task;
    }
}


