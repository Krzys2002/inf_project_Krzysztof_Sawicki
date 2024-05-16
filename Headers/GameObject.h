//
// Created by Krzysztof Sawicki on 14/05/2024.
//

#ifndef INF_PROJECT_GAMEOBJECT_H
#define INF_PROJECT_GAMEOBJECT_H

#include "../Headers/TimeSpace.h"


class GameObject
{
public:
    GameObject();

    // call on the start of the game
    virtual void Ready();

    // call every frame
    virtual void Update(double deltaTime);

    // call every round (day)
    virtual void RoundUpdate(const TimeSpace::GameTime& gameTime);
    ~GameObject();
};


#endif //INF_PROJECT_GAMEOBJECT_H
