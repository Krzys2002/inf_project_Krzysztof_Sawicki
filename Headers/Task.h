//
// Created by Krzysztof Sawicki on 01/06/2024.
//

#ifndef INF_PROJECT_TASK_H
#define INF_PROJECT_TASK_H


#include "Agent.h"
#include "MagicAbility.h"
#include "Spell.h"
#include "GameObject.h"

class Agent;
class GameObject;
class Game;

class Task : public GameObject, public std::enable_shared_from_this<Task>
{
    // whether the task is completed
    bool Completed = false;
    // whether the task is accepted
    bool Accepted = false;
    // the spell required to complete the task
    std::weak_ptr<Spell> requiredSpell;
    // the proficiency required to complete the task
    int requiredProficiency;
    // the complexity of the task
    int complexity;
    // the progress made on the task
    int progress = 0;
    // the agent that created the task
    std::weak_ptr<Agent> fromAgent;
    // the agent that accepted the task
    std::weak_ptr<Agent> acceptedByAgent;
    // Reword for completing the task
    std::vector<int> reward;
    // the day the task was created
    unsigned int creationDay;

public:
    Task(std::weak_ptr<Agent> fromAgent, unsigned int seed, const std::string& name, unsigned int dayNumber);

    std::weak_ptr<Spell> getRequiredSpell();
    int getDifficulty() const;
    int getComplexity() const;
    unsigned int getCreationDay() const;

    std::vector<int> getReward() const;

    bool isCompleted() const;
    bool isAccepted() const;

    void makeProgress(std::weak_ptr<MagicAbility> ability);

    bool canAcceptTask(const std::weak_ptr<MagicAbility>& ability);

    void acceptTask(const std::shared_ptr<Agent>& agent);
};


#endif //INF_PROJECT_TASK_H
