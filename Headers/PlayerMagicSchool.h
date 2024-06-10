//
// Created by Krzysztof Sawicki on 05/06/2024.
//

#ifndef INF_PROJECT_PLAYERMAGICSCHOOL_H
#define INF_PROJECT_PLAYERMAGICSCHOOL_H


#include "MagicSchool.h"

class Game;
class MagicSchool;

class PlayerMagicSchool : public MagicSchool
{
    // list of non assined tasks
    std::vector<std::shared_ptr<Task>> taskTable;
    // list of assined tasks to the students
    std::map<std::shared_ptr<Agent>, std::shared_ptr<Task>> taskAssignment;
    // resources of the player
    std::vector<unsigned int> resources;
    // Player Hero
    std::shared_ptr<Agent> hero;

public:
    // Constructor
    PlayerMagicSchool(unsigned int seed, std::string name, std::shared_ptr<Instance> parentInstance = nullptr);

    // RoundUpdate call on every round
    void roundUpdate(TimeSpace::GameTimeSystem& gameTime) override;

    // Method to get all tasks from the instance
    std::vector<std::shared_ptr<Task>> getTasks();
    // Method to get all tasks from the instance
    std::map<std::shared_ptr<Agent>, std::shared_ptr<Task>> getTaskAssignment();

    // Method to get all resources from the instance
    std::vector<unsigned int> getResources();

    // Method to get hero from the instance
    std::shared_ptr<Agent> getHero();
    // Method to set hero from the instance
    void setHero(std::shared_ptr<Teacher>& hero);

    // Method to get all spells from the instance
    void addSpell(std::weak_ptr<Spell> spell) override;

    // Method to get all spells from the instance
    void addResource(int resource ,unsigned int amaunt);

    //
    void addStudent(std::shared_ptr<Agent> student);

    // Method to get all spells from the instance
    void addTask(std::shared_ptr<Task> task);

    // Method to assign task to the student
    void assignTask(std::shared_ptr<Agent> student, std::shared_ptr<Task> task);
};


#endif //INF_PROJECT_PLAYERMAGICSCHOOL_H
