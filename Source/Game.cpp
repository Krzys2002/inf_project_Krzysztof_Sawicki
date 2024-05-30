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
    window = std::make_unique<sf::RenderWindow>(sf::VideoMode(800, 600), "Game");

    worldCreationThread = std::thread([&](){
        gameTime = new TimeSpace::GameTimeSystem(TimeSpace::GameTime(0, TimeSpace::Months::February, 0,
                                                                     TimeSpace::Days::Monday));

        createWorld();

        for (auto& instance : instances)
        {
            instance->ready();
        }

        std::vector<std::weak_ptr<GameObject>> gameObjects(instances.begin(), instances.end());

        uiManager = std::make_unique<UIManager>(this, window.get());
        uiManager->start();
        std::string title = "test";
        uiManager->ListGameObjectsOnPanel(MainPanelIndex::LEFT, title, gameObjects);
        uiManager->setPanelToViewObjectInfoFor(MainPanelIndex::LEFT, MainPanelIndex::RIGHT);

        isWorldCreated = true;
    });


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
    auto worldCreationTextGui = std::unique_ptr<tgui::Gui>(new tgui::Gui(*window));
    worldCreationTextGui->setTarget(*window);
    auto worldCreationText = tgui::Label::create();
    worldCreationText->setText("Creating world...");
    worldCreationText->setPosition("35%", "40%");
    worldCreationText->setTextSize(24);
    worldCreationText->getRenderer()->setTextColor(sf::Color::White);
    worldCreationTextGui->add(worldCreationText);

    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();

            if (isWorldCreated)
            {
                uiManager->getGui().handleEvent(event);
            }
        }

        if(!isNextRoundThreadRunning && nextRoundThread.joinable())
        {
            nextRoundThread.join();
            uiManager->unlockGui();
        }

        window->clear();
        if(isWorldCreated)
        {
            if(worldCreationThread.joinable())
            {
                worldCreationTextGui->removeAllWidgets();
                worldCreationTextGui.reset();
                worldCreationThread.join();
            }
            uiManager->getGui().draw();
        } else
        {
            worldCreationTextGui->draw();
        }
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
