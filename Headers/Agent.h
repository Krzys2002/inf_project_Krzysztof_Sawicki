//
// Created by Krzysztof Sawicki on 17/05/2024.
//

#ifndef INF_PROJECT_AGENT_H
#define INF_PROJECT_AGENT_H

#include "Task.h"
#include "GameObject.h"
#include "Instance.h"
#include "MagicAbility.h"

class Instance;  // Forward declaration of Instance
class Task;  // Forward declaration of Task
class MagicAbility;  // Forward declaration of MagicAbility
class Teacher;  // Forward declaration of Teacher

class Agent : public GameObject, public std::enable_shared_from_this<Agent>
{
protected:
    std::shared_ptr<Instance> currentInstance;
    const unsigned int seed;
    // Description of the agent
    std::string description;

    // Main professions of Agent
    Professions mainProfession;
    // Secondary professions of Agent
    Professions secondaryProfession;

    // task tant this agent created
    std::shared_ptr<Task> createdTask;

    // magic ability of the agent
    std::shared_ptr<MagicAbility> magicAbility;

    // day number
    unsigned int dayNumber = 0;

public:
    static std::shared_ptr<Agent> null;

    // Constructor
    Agent(unsigned int seed, std::string name, std::shared_ptr<Instance> currentInstance);
    Agent(unsigned int ID, unsigned int seed, std::string name, std::shared_ptr<Instance> currentInstance);
    Agent(const Agent& agent);

    // Destructor
    ~Agent();

    // Update every Round
    void roundUpdate(TimeSpace::GameTimeSystem& gameTime) override;

    // Get the current instance
    std::shared_ptr<Instance> getCurrentInstance() const;
    // get the seed of the agent
    unsigned int getSeed() const;
    bool hasTask() const;
    // get magic ability of the agent
    std::shared_ptr<MagicAbility> getMagicAbility() const;

    // Set the current instance
    void setInstance(std::shared_ptr<Instance> newInstance);

    // Get the main profession of the agent
    Professions getMainProfession() const;
    // Get the secondary profession of the agent
    Professions getSecondaryProfession() const;

    // Set the main profession of the agent
    void setMainProfession(Professions profession);
    // Set the secondary profession of the agent
    void setSecondaryProfession(Professions profession);

    // Get the description of the agent
    std::string getDescription() const;

    // Create a task from the agent
    std::shared_ptr<Task> createTask();


    // Create a Magic Ability for the agent
    void createMagicAbility();

    // Transform to Teacher
    std::shared_ptr<Teacher> transformToTeacher();
};


#endif //INF_PROJECT_AGENT_H
