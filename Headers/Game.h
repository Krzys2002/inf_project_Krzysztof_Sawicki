//
// Created by Krzysztof Sawicki on 19/05/2024.
//

#ifndef INF_PROJECT_GAME_H
#define INF_PROJECT_GAME_H

#include <iostream>
#include <memory>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include "TimeSpace.h"
#include "Agent.h"
#include "Instance.h"
#include "../UI/Headers/ListItem.h"
#include "../UI/Headers/UIManager.h"
#include "City.h"

class UIManager;

class Game
{
    std::unique_ptr<sf::RenderWindow> window;
    std::unique_ptr<UIManager> uiManager;
    std::vector<std::shared_ptr<Instance>> instances;
    std::vector<std::shared_ptr<Agent>> agents;
    TimeSpace::GameTimeSystem* gameTime;

public:
    Game();
    ~Game();

    void start();
    void NextRound();
    void run();


};


#endif //INF_PROJECT_GAME_H
