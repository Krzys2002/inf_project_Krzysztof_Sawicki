//
// Created by Krzysztof Sawicki on 01/06/2024.
//

#include "../Headers/Task.h"
#include "../Headers/Game.h"

int Task::getDifficulty() const
{
    return requiredProficiency;
}

int Task::getComplexity() const
{
    return complexity;
}

bool Task::isCompleted() const
{
    return Completed;
}

bool Task::isAccepted() const
{
    return Accepted;
}

std::weak_ptr<Spell> Task::getRequiredSpell()
{
    return requiredSpell;
}

void Task::makeProgress(std::weak_ptr<MagicAbility> ability)
{
    if (auto sharedAbility = ability.lock())
    {
        if (sharedAbility->canCastSpell(requiredSpell.lock()) && sharedAbility->getSpellProficiency(requiredSpell.lock()) > requiredProficiency)
        {
            progress += sharedAbility->getSpellProficiency(requiredSpell.lock()) - requiredProficiency;
        }
    }

    if(progress >= complexity)
    {
        Completed = true;


        std::function<void(Game*)> func = [this](Game* game){
            std::cout << "Task completed by " << acceptedByAgent.lock()->getName() << std::endl;
            auto player = std::dynamic_pointer_cast<PlayerMagicSchool>(game->getPlayerMagicSchool());
            player->addResource(static_cast<int>(GameLoudObject::ResourceType::Gold), reward[static_cast<int>(GameLoudObject::ResourceType::Gold)]);
            player->addResource(static_cast<int>(GameLoudObject::ResourceType::MagicStone), reward[static_cast<int>(GameLoudObject::ResourceType::MagicStone)]);
        };
        Game::GameEvent event = Game::GameEvent(func, std::static_pointer_cast<Task>(shared_from_this()));
        Game::emitGameEvent(event);
    }
}

bool Task::canAcceptTask(const std::weak_ptr<MagicAbility>& ability)
{
    if (auto sharedAbility = ability.lock())
    {
        if (sharedAbility->canCastSpell(requiredSpell.lock()) && sharedAbility->getSpellProficiency(requiredSpell.lock()) > requiredProficiency)
        {
            return true;
        }
    }

    return false;
}

void Task::acceptTask(const std::shared_ptr<Agent>& agent)
{
    if(agent != nullptr)
    {
        acceptedByAgent = agent;
        Accepted = true;
    }
}

unsigned int Task::getCreationDay() const
{
    return creationDay;
}

std::vector<int> Task::getReward() const
{
    return reward;
}

Task::Task(std::weak_ptr<Agent> fromAgent, unsigned int seed, const std::string& name, unsigned int dayNumber) : GameObject(name), reward(static_cast<int>(GameLoudObject::ResourceType::Count), 0)
{
    this->fromAgent = fromAgent;
    RandomNumberGenerator rng(seed);
    requiredProficiency = rng.generate(5, 95);
    complexity = rng.generate(5, 50);
    creationDay = dayNumber;
    requiredSpell = GameLoudObject::GetRandomSpell();
    int calculatedReward = requiredProficiency * complexity/10;

    for (int i = 0; i < reward.size(); ++i)
    {
        if(i == reward.size() - 1)
        {
            reward[i] = calculatedReward;
        }
        else
        {
            reward[i] = rng.generate(0, calculatedReward);
            calculatedReward -= reward[i];
        }

        if(calculatedReward <= 0)
        {
            break;
        }
    }
}
