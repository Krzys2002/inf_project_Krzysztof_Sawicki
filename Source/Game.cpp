//
// Created by Krzysztof Sawicki on 19/05/2024.
//

#include "../Headers/Game.h"

std::vector<Game::GameEvent> Game::gameEventsInRound;

Game::Game()
{
    std::string path = "spells.json";
    GameLoudObject::LoudSpellsFromFile(path);


//    uiManager->ListGameObjectsOnPanel(MainPanelIndex::MIDDLE, title, gameObjects);
//    uiManager->ListGameObjectsOnPanel(MainPanelIndex::RIGHT, title, gameObjects);
}

Game::~Game()
{
    //uiManager.reset();
    stopFlag = true;
    if(worldCreationThread.joinable())
    {
        worldCreationThread.join();
    }

    if(nextRoundThread.joinable())
    {
        nextRoundThread.join();
    }
}

void Game::start()
{
    window = std::make_unique<sf::RenderWindow>(sf::VideoMode(800, 600), "Game");
    window->setFramerateLimit(60);

    worldCreationThread = std::thread([&](){
        gameTime = new TimeSpace::GameTimeSystem(TimeSpace::GameTime(0, TimeSpace::Months::February, 0,
                                                                     TimeSpace::Days::Monday));

        createWorld();

        for (auto& instance : instances)
        {
            if(stopFlag)
            {
                break;
            }
            instance->ready();
        }


        isWorldCreated = true;
    });

    uiManager = std::make_unique<UIManager>(this, window.get());
    uiManager->start();

}

void Game::NextRound()
{

    nextRoundThread = std::thread([&](){

        isNextRoundThreadRunning = true;
        gameTime->NextDay();

        for (auto& instance : instances)
        {
            if(stopFlag)
            {
                break;
            }
            instance->roundUpdate(*gameTime);
        }

        for(auto& event : gameEventsInRound)
        {
            if(stopFlag)
            {
                break;
            }
            event.execute(this);
        }

        isNextRoundThreadRunning = false;
    });
}

void Game::run()
{
    sf::Clock clock;

    while (window->isOpen())
    {
        sf::Time deltaTime = clock.restart();

        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();

            uiManager->getGui().handleEvent(event);
        }

        window->clear();
        if(!isNextRoundThreadRunning && nextRoundThread.joinable())
        {
            nextRoundThread.join();
        }
        if(isWorldCreated && worldCreationThread.joinable())
        {
            worldCreationThread.join();
        }
        uiManager->update(deltaTime);
        uiManager->getGui().draw();
        window->display();
    }
}

void Game::createWorld()
{
    RandomNumberGenerator rng(WorldSettings::GetSeed());

    city = std::make_shared<City>(WorldSettings::GetSeed(), GameNameHolder::getRandomCityName(
            WorldSettings::GetSeed()));
    instances.emplace_back(city);

    int tempCount = WorldSettings::GetTavernCount() + WorldSettings::GetTavernCount()
                                                      * rng.generateFloat(-WorldSettings::GetAberration(),
                                                                          WorldSettings::GetAberration());
    // Create taverns in the city
    for (int i = 0; i < tempCount; ++i)
    {
        if(stopFlag)
        {
            break;
        }
        instances.emplace_back(city->CreateTavern());
    }

    tempCount = WorldSettings::GetSquareCount() + WorldSettings::GetSquareCount()
                                                  * rng.generateFloat(-WorldSettings::GetAberration(),
                                                                      WorldSettings::GetAberration());
    // Create squares in the city
    for (int i = 0; i < tempCount; ++i)
    {
        if(stopFlag)
        {
            break;
        }
        instances.emplace_back(city->CreateSquare());
    }

    //Create MagicSchool
    for (int i = 0; i < WorldSettings::GetNumberOfEnemiesSchools(); i++)
    {
        if(stopFlag)
        {
            break;
        }
        instances.emplace_back(city->CreateMagicSchool());
    }

    //Create PlayerMagicSchool

    playerMagicSchool = city->CreatePlayerMagicSchool();
    instances.emplace_back(playerMagicSchool);

}

void Game::emitGameEvent(Game::GameEvent &event)
{
    gameEventsInRound.push_back(event);
}

std::shared_ptr<City> Game::getCity()
{
    return city;
}

std::shared_ptr<Instance> Game::getPlayerMagicSchool()
{
    return playerMagicSchool;
}

bool Game::isWorldCreatedFlag()
{

    return isWorldCreated;
}

bool Game::isNextRoundThreadRunningFlag()
{
    return isNextRoundThreadRunning;
}

std::vector<Game::GameEvent> Game::getGameEventsInRound()
{
    return gameEventsInRound;
}

void Game::GameEvent::execute(Game* game)
{
    func(game);
}

std::weak_ptr<GameObject> Game::GameEvent::from()
{
    return gameObject;
}




