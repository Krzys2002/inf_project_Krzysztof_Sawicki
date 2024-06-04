//
// Created by Krzysztof Sawicki on 17/05/2024.
//

#include "../Headers/Agent.h"
#include "../Headers/Teacher.h"

std::shared_ptr<Agent> Agent::null = nullptr;

Agent::Agent(unsigned int seed, std::string name, std::shared_ptr<Instance> currentInstance) : GameObject(name), seed(seed)
{
    this->currentInstance = currentInstance;
    auto rng = RandomNumberGenerator(seed);
    magicAbility.setTalent(rng.generate(1, 10));
}

Agent::Agent(const Agent& agent) : GameObject(agent), seed(agent.seed)
{
    currentInstance = agent.currentInstance;
    mainProfession = agent.mainProfession;
    secondaryProfession = agent.secondaryProfession;
    description = agent.description;
    magicAbility = agent.magicAbility;
    dayNumber = agent.dayNumber;
    createdTask = agent.createdTask;
}

Agent::Agent(unsigned int ID, unsigned int seed, std::string name, std::shared_ptr<Instance> currentInstance) : GameObject(ID, name), seed(seed)
{
    this->currentInstance = currentInstance;
}

unsigned int Agent::getSeed() const
{
    return seed;
}

Agent::~Agent()
{
    // Destructor
}

void Agent::roundUpdate(TimeSpace::GameTimeSystem& gameTime)
{
    // RoundUpdate
    dayNumber = gameTime.getDayFromStart();

    if (createdTask != nullptr)
    {
        if(!createdTask->isAccepted() && createdTask->getCreationDay() + WorldSettings::GetTaskExpireTime() < dayNumber)
        {
            createdTask.reset();
        }
    }
}

std::shared_ptr<Instance> Agent::getCurrentInstance() const
{
    return currentInstance;
}

void Agent::setInstance(std::shared_ptr<Instance> newInstance)
{
    currentInstance = newInstance;
}

Professions Agent::getMainProfession() const
{
    return mainProfession;
}

Professions Agent::getSecondaryProfession() const
{
    return secondaryProfession;
}

void Agent::setMainProfession(Professions profession)
{
    mainProfession = profession;
    description = GameNameHolder::getRandomAgentDescription(seed, mainProfession);
}

void Agent::setSecondaryProfession(Professions profession)
{
    secondaryProfession = profession;
}

std::string Agent::getDescription() const
{
    return description;
}

bool Agent::hasTask() const
{
    return createdTask != nullptr;
}

std::shared_ptr<MagicAbility> Agent::getMagicAbility() const
{
    return std::make_shared<MagicAbility>(magicAbility);
}

std::shared_ptr<Task> Agent::createTask()
{
    createdTask = std::make_shared<Task>(std::static_pointer_cast<Agent>(shared_from_this()),
            seed * dayNumber + dayNumber, "Task", dayNumber);
    return createdTask;
}

void Agent::createMagicAbility()
{
    RandomNumberGenerator rng(seed + seed);
    magicAbility = MagicAbility(rng.generate(1, 10));
}

std::shared_ptr<Teacher> Agent::transformToTeacher()
{
    return std::make_shared<Teacher>(*this);
}

