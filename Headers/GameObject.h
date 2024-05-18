//
// Created by Krzysztof Sawicki on 14/05/2024.
//

#ifndef INF_PROJECT_GAMEOBJECT_H
#define INF_PROJECT_GAMEOBJECT_H

#include "../Headers/TimeSpace.h"
#include "../Source/RandomNumberGenerator.cpp"
#include <string>
#include "../Headers//GameNameHolder.h"


class GameObject
{
private:
    static unsigned int newID;
protected:
    const unsigned int ID;
    std::string name;
public:
    GameObject(const std::string& name);

    // get the ID of the object
    int getID() const;

    std::string getName() const;

    // call on the start of the game
    virtual void Ready();

    // call every frame
    virtual void Update(double deltaTime);

    // call every round (day)
    virtual void RoundUpdate(const TimeSpace::GameTimeSystem& gameTime);
    ~GameObject();
};


#endif //INF_PROJECT_GAMEOBJECT_H
