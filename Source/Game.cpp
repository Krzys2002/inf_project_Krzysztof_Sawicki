//
// Created by Krzysztof Sawicki on 19/05/2024.
//

#include "../Headers/Game.h"


Game::Game()
{
    gameTime = new TimeSpace::GameTimeSystem(TimeSpace::GameTime(0, TimeSpace::Months::February, 0, TimeSpace::Days::Monday));

    window = std::make_unique<sf::RenderWindow>(sf::VideoMode(800, 600), "Game");

    uiManager = std::make_unique<UIManager>(this, window.get());
    uiManager->start();

    std::shared_ptr<City> city = std::make_shared<City>(0, "City");
    instances.push_back(city->CreateTavern());
    instances.push_back(city->CreateTavern());
    instances.push_back(city->CreateTavern());
    instances.push_back(city->CreateTavern());
    instances.push_back(city);

    std::vector<std::weak_ptr<GameObject>> gameObjects(instances.begin(), instances.end());
    std::string title = "test";
    uiManager->ListGameObjectsOnPanel(MainPanelIndex::LEFT, title, gameObjects);
    uiManager->setPanelToViewObjectInfoFor(MainPanelIndex::LEFT, MainPanelIndex::RIGHT);
//    uiManager->ListGameObjectsOnPanel(MainPanelIndex::MIDDLE, title, gameObjects);
//    uiManager->ListGameObjectsOnPanel(MainPanelIndex::RIGHT, title, gameObjects);


//

    window->clear();
    uiManager->getGui().draw();
    window->display();
//    uiManager->viewObjectInfo(MainPanelIndex::RIGHT, gameObjects[0]);
//    uiManager->viewObjectInfo(MainPanelIndex::LEFT, gameObjects[1]);
//    uiManager->viewObjectInfo(MainPanelIndex::MIDDLE, gameObjects[2]);
}

Game::~Game()
{
    //uiManager.reset();
}

void Game::start()
{
    std::vector<std::shared_ptr<GameObject>> gameObjects(instances.begin(), instances.end());
    std::string title = "test";
//    uiManager->ListGameObjectsOnPanel(MainPanelIndex::LEFT, title, gameObjects);
//    uiManager->setPanelToViewObjectInfoFor(MainPanelIndex::LEFT, MainPanelIndex::RIGHT);
    std::shared_ptr<GameObject> gameObject = std::dynamic_pointer_cast<GameObject>(instances[0]);
//    uiManager->viewObjectInfo(MainPanelIndex::RIGHT, gameObject);

    for (auto& instance : instances)
    {
        instance->Ready();
    }
}

void Game::NextRound()
{
    gameTime->NextDay();
    for (auto& instance : instances)
    {
        instance->RoundUpdate(*gameTime);
    }
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

        window->clear();
        uiManager->getGui().draw();
        window->display();
    }
}
