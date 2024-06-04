//
// Created by Krzysztof Sawicki on 02/06/2024.
//

#ifndef INF_PROJECT_TEACHER_H
#define INF_PROJECT_TEACHER_H

#include "Agent.h"

class Agent;

class Teacher : public Agent
{
    std::vector<std::weak_ptr<Agent>> students;

public:
    // Constructor
    Teacher(unsigned int seed, std::string name, std::shared_ptr<Instance> parentInstance = nullptr);
    Teacher(const Agent& agent);

    // Destructor
    ~Teacher();

    // Ready call on start of the game
    void ready() override;

    // RoundUpdate call on every round
    void roundUpdate(TimeSpace::GameTimeSystem& gameTime) override;

    // Add student to the teacher
    void addStudent(std::shared_ptr<Agent> student);
};


#endif //INF_PROJECT_TEACHER_H
