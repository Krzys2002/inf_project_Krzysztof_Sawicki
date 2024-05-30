//
// Created by Krzysztof Sawicki on 19/05/2024.
//

#include "../Headers/Game.h"


Game::Game()
{



//    uiManager->ListGameObjectsOnPanel(MainPanelIndex::MIDDLE, title, gameObjects);
//    uiManager->ListGameObjectsOnPanel(MainPanelIndex::RIGHT, title, gameObjects);
}

Game::~Game()
{
    //uiManager.reset();
}

void Game::start()
{
    gameTime = new TimeSpace::GameTimeSystem(TimeSpace::GameTime(0, TimeSpace::Months::February, 0,
                                                                 TimeSpace::Days::Monday));

    window = std::make_unique<sf::RenderWindow>(sf::VideoMode(800, 600), "Game");

    uiManager = std::make_unique<UIManager>(this, window.get());
    uiManager->start();

    createWorld();

    for (auto& instance : instances)
    {
        instance->ready();
    }

    std::vector<std::weak_ptr<GameObject>> gameObjects(instances.begin(), instances.end());

    std::string title = "test";
    uiManager->ListGameObjectsOnPanel(MainPanelIndex::LEFT, title, gameObjects);
    uiManager->setPanelToViewObjectInfoFor(MainPanelIndex::LEFT, MainPanelIndex::RIGHT);
}

void Game::NextRound()
{
    nextRoundThread = std::thread([&](){
        isNextRoundThreadRunning = true;
        gameTime->NextDay();
        for (auto& instance : instances)
        {
            instance->roundUpdate(*gameTime);
        }
        isNextRoundThreadRunning = false;
    });

    uiManager->lockGui();
}

void Game::run()
{
    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();

            uiManager->getGui().handleEvent(event);
        }

        if(!isNextRoundThreadRunning && nextRoundThread.joinable())
        {
            nextRoundThread.join();
            uiManager->unlockGui();
        }

        window->clear();
        uiManager->getGui().draw();
        window->display();
    }
}

void Game::createWorld()
{
    if(worldSettings == nullptr)
    {
        worldSettings = std::make_unique<WorldSettings>();
    }

    RandomNumberGenerator rng(worldSettings->getSeed());

    std::shared_ptr<City> city = std::make_shared<City>(worldSettings->getSeed(), *worldSettings, GameNameHolder::getRandomCityName(worldSettings->getSeed()));
    instances.emplace_back(city);

    int tempCount = worldSettings->getTavernCount() + worldSettings->getTavernCount()
            * rng.generateFloat(-worldSettings->getAberration(), worldSettings->getAberration());
    // Create taverns in the city
    for (int i = 0; i < tempCount; ++i)
    {
        instances.emplace_back(city->CreateTavern());
    }

    tempCount = worldSettings->getSquareCount() + worldSettings->getSquareCount()
            * rng.generateFloat(-worldSettings->getAberration(), worldSettings->getAberration());
    // Create squares in the city
    for (int i = 0; i < tempCount; ++i)
    {
        instances.emplace_back(city->CreateSquare());
    }
}

void Game::setWorldSettings(WorldSettings* worldSettings)
{
    this->worldSettings.reset(worldSettings);
}
