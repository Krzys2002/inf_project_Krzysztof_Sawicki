//
// Created by Krzysztof Sawicki on 14/05/2024.
//

#ifndef INF_PROJECT_GAMEOBJECT_H
#define INF_PROJECT_GAMEOBJECT_H

#include "TimeSpace.h"
#include "../Source/RandomNumberGenerator.cpp"
#include <string>
#include "GameNameHolder.h"


class GameObject
{
protected:
    static unsigned int newID;
    const unsigned int ID;
    std::string name;
public:
    GameObject(const std::string& name);
    GameObject(unsigned int ID, const std::string& name);

    // get the ID of the object
    int getID() const;

    std::string getName() const;

    // call on the start of the game
    virtual void ready();

    // call every frame
    virtual void update(double deltaTime);

    // call every round (day)
    virtual void roundUpdate(TimeSpace::GameTimeSystem& gameTime);
    ~GameObject();
};


#endif //INF_PROJECT_GAMEOBJECT_H
