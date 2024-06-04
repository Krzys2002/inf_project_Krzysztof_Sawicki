//
// Created by Krzysztof Sawicki on 19/05/2024.
//

#include "../Headers/Game.h"

std::vector<Game::GameEvent> Game::gameEventsInRound;
std::vector<std::shared_ptr<Spell>> Game::GameLoudObject::Spells;

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
    RandomNumberGenerator rng(WorldSettings::GetSeed());

    std::shared_ptr<City> city = std::make_shared<City>(WorldSettings::GetSeed(), GameNameHolder::getRandomCityName(
            WorldSettings::GetSeed()));
    instances.emplace_back(city);

    int tempCount = WorldSettings::GetTavernCount() + WorldSettings::GetTavernCount()
                                                      * rng.generateFloat(-WorldSettings::GetAberration(),
                                                                          WorldSettings::GetAberration());
    // Create taverns in the city
    for (int i = 0; i < tempCount; ++i)
    {
        instances.emplace_back(city->CreateTavern());
    }

    tempCount = WorldSettings::GetSquareCount() + WorldSettings::GetSquareCount()
                                                  * rng.generateFloat(-WorldSettings::GetAberration(),
                                                                      WorldSettings::GetAberration());
    // Create squares in the city
    for (int i = 0; i < tempCount; ++i)
    {
        instances.emplace_back(city->CreateSquare());
    }

    //Create MagicSchool
    for (int i = 0; i < WorldSettings::GetNumberOfEnemiesSchools(); i++)
    {
        instances.emplace_back(city->CreateMagicSchool());
    }

}

void Game::emitGameEvent(Game::GameEvent &event)
{
    gameEventsInRound.push_back(event);
}

void Game::GameEvent::execute(std::shared_ptr<Game> game)
{
    func(game);
}

std::weak_ptr<GameObject> Game::GameEvent::from()
{
    return gameObject.lock();
}

void Game::GameLoudObject::LoudSpellsFromFile(std::string &path)
{
    // Open the JSON file
    std::ifstream file(path);

    // Parse the JSON file
    json j;
    file >> j;

    // Get the spells category
    auto spells = j.at("spells");

    // Loop over the spells in the JSON file
    for (const auto& spell : spells)
    {
        // Get the type of the spell
        std::string type = spell.at("type").get<std::string>();

        // Create the appropriate spell based on the type
        if (type == "attack")
        {
            Spells.push_back(std::make_shared<AttackSpell>(spell));
        }
        else if (type == "healing")
        {
            Spells.push_back(std::make_shared<HealingSpell>(spell));
        }
        else if (type == "defense")
        {
            Spells.push_back(std::make_shared<DefenseSpell>(spell));
        }
    }
}

std::vector<std::shared_ptr<Spell>>& Game::GameLoudObject::GetSpells()
{
    return Spells;
}

std::shared_ptr<Spell> Game::GameLoudObject::GetRandomSpell()
{
    return Spells[RandomNumberGenerator::Generate(0, Spells.size() - 1)];
}

std::shared_ptr<Spell> Game::GameLoudObject::GetSpellByName(std::string &name)
{
    auto findAt = std::find_if(Spells.begin(), Spells.end(), [&name](std::shared_ptr<Spell> spell){
        return spell->getName() == name;
    });

    if(findAt != Spells.end())
    {
        return *findAt;
    }

    return nullptr;
}


