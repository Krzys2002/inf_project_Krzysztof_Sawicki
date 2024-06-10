//
// Created by Krzysztof Sawicki on 19/05/2024.
//

#ifndef INF_PROJECT_GAME_H
#define INF_PROJECT_GAME_H

#include <iostream>
#include <memory>
#include <thread>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <utility>
#include <vector>
#include <functional>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <nlohmann/json.hpp>
#include <fstream>
#include "TimeSpace.h"
#include "Agent.h"
#include "Instance.h"
#include "../UI/Headers/ListItem.h"
#include "../UI/Headers/UIManager.h"
#include "GameNameHolder.h"
#include "WorldSettings.h"
#include "City.h"


using json = nlohmann::json;

class UIManager;
class Instance;
class Agent;
class GameObject;
class MagicSchool;


class Game : public std::enable_shared_from_this<Game>
{
public:
    class GameEvent;

private:
    static std::vector<Game::GameEvent> gameEventsInRound;
    std::unique_ptr<sf::RenderWindow> window;
    std::unique_ptr<UIManager> uiManager;
    std::vector<std::shared_ptr<Instance>> instances;
    std::vector<std::shared_ptr<Agent>> agents;
    TimeSpace::GameTimeSystem* gameTime;
    std::thread nextRoundThread;
    bool isNextRoundThreadRunning = false;
    std::thread worldCreationThread;
    bool isWorldCreated = false;
    bool stopFlag = false;

    std::shared_ptr<City> city;
    std::shared_ptr<Instance> playerMagicSchool;

    void createWorld();

public:

    class GameEvent
    {
    private:
        std::function<void(Game*)> func;
        std::shared_ptr<GameObject> gameObject;

    public:
        GameEvent(std::function<void(Game*)> func, std::shared_ptr<GameObject> gameObject)
                : func(func), gameObject(std::move(gameObject)) {}

        void execute(Game* game);

        std::weak_ptr<GameObject> from();
    };

    static void emitGameEvent(Game::GameEvent& event);

    Game();
    ~Game();

    std::shared_ptr<City> getCity();
    std::shared_ptr<Instance> getPlayerMagicSchool();

    bool isWorldCreatedFlag();
    bool isNextRoundThreadRunningFlag();

    void start();
    void NextRound();
    void run();
    std::vector<Game::GameEvent> getGameEventsInRound();
};


#endif //INF_PROJECT_GAME_H
