#include <iostream>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include "Headers/Game.h"
#include "Headers/WorldSettings.h"



int main()
{
    Game game;
    sf::RenderWindow window(sf::VideoMode(800, 600), "Settings");
    bool startGame = false;
    float maxSliderValue = 10.0f;

    std::cout << WorldSettings::GetCityPopulationModifier() << std::endl;

    tgui::Gui gui{window};

    tgui::ScrollablePanel::Ptr panel = tgui::ScrollablePanel::create();
    panel->setSize("100%", "100%");
    panel->setPosition(0, 0);
    gui.add(panel);

    //Create a label for the city population modifier
    auto cityPopulationModifierLabel = tgui::Label::create();
    cityPopulationModifierLabel->setText("City Population Modifier");
    cityPopulationModifierLabel->setPosition("10%", "5%");
    panel->add(cityPopulationModifierLabel);

    // Create a slider for the city population modifier
    auto cityPopulationModifierSlider = tgui::Slider::create();
    cityPopulationModifierSlider->setMinimum(0.1f);
    cityPopulationModifierSlider->setMaximum(maxSliderValue);
    cityPopulationModifierSlider->setStep(0.1f);
    cityPopulationModifierSlider->setValue(WorldSettings::GetCityPopulationModifier());
    cityPopulationModifierSlider->setPosition("10%", "10%");
    panel->add(cityPopulationModifierSlider);

    // Create a label for the city population modifier value
    auto cityPopulationModifierValueLabel = tgui::Label::create();
    cityPopulationModifierValueLabel->setPosition("60%", "10%");
    cityPopulationModifierValueLabel->setText(std::to_string(WorldSettings::GetCityPopulationModifier()));
    panel->add(cityPopulationModifierValueLabel);

    // Update the label whenever the slider value changes
    cityPopulationModifierSlider->onValueChange([=](){
        cityPopulationModifierValueLabel->setText(std::to_string(cityPopulationModifierSlider->getValue()));
    });

    // Create a label for the tavern population Modifier
    auto tavernPopulationLabel = tgui::Label::create();
    tavernPopulationLabel->setText("Tavern Population Modifier");
    tavernPopulationLabel->setPosition("10%", "15%");
    panel->add(tavernPopulationLabel);

    // Create a slider for the tavern population Modifier
    auto tavernPopulationSlider = tgui::Slider::create();
    tavernPopulationSlider->setMinimum(0.1f);
    tavernPopulationSlider->setMaximum(maxSliderValue);
    tavernPopulationSlider->setStep(0.1f);
    tavernPopulationSlider->setValue(WorldSettings::GetTavernPopulationModifier());
    tavernPopulationSlider->setPosition("10%", "20%");
    panel->add(tavernPopulationSlider);

    // Create a label for the tavern population modifier value
    auto tavernPopulationModifierValueLabel = tgui::Label::create();
    tavernPopulationModifierValueLabel->setPosition("60%", "20%");
    tavernPopulationModifierValueLabel->setText(std::to_string(WorldSettings::GetTavernPopulationModifier()));
    panel->add(tavernPopulationModifierValueLabel);

    // Update the label whenever the slider value changes
    tavernPopulationSlider->onValueChange([=](){
        tavernPopulationModifierValueLabel->setText(std::to_string(tavernPopulationSlider->getValue()));
    });

    // Create a label for the square population Modifier
    auto squarePopulationLabel = tgui::Label::create();
    squarePopulationLabel->setText("Square Population Modifier");
    squarePopulationLabel->setPosition("10%", "25%");
    panel->add(squarePopulationLabel);

    // Create a slider for the square population Modifier
    auto squarePopulationSlider = tgui::Slider::create();
    squarePopulationSlider->setMinimum(0.1f);
    squarePopulationSlider->setMaximum(maxSliderValue);
    squarePopulationSlider->setStep(0.1f);
    squarePopulationSlider->setValue(WorldSettings::GetSquarePopulationModifier());
    squarePopulationSlider->setPosition("10%", "30%");
    panel->add(squarePopulationSlider);

    // Create a label for the square population modifier value
    auto squarePopulationModifierValueLabel = tgui::Label::create();
    squarePopulationModifierValueLabel->setPosition("60%", "30%");
    squarePopulationModifierValueLabel->setText(std::to_string(WorldSettings::GetSquarePopulationModifier()));
    panel->add(squarePopulationModifierValueLabel);

    // Update the label whenever the slider value changes
    squarePopulationSlider->onValueChange([=](){
        squarePopulationModifierValueLabel->setText(std::to_string(squarePopulationSlider->getValue()));
    });

    // Create a label for the square count Modifier
    auto squareCountLabel = tgui::Label::create();
    squareCountLabel->setText("Square Count Modifier");
    squareCountLabel->setPosition("10%", "35%");
    panel->add(squareCountLabel);

    // Create a slider for the square count Modifier
    auto squareCountSlider = tgui::Slider::create();
    squareCountSlider->setMinimum(0.1f);
    squareCountSlider->setMaximum(maxSliderValue);
    squareCountSlider->setStep(0.1f);
    squareCountSlider->setValue(WorldSettings::GetSquareCountModifier());
    squareCountSlider->setPosition("10%", "40%");
    panel->add(squareCountSlider);

    // Create a label for the square count modifier value
    auto squareCountModifierValueLabel = tgui::Label::create();
    squareCountModifierValueLabel->setPosition("60%", "40%");
    squareCountModifierValueLabel->setText(std::to_string(WorldSettings::GetSquareCountModifier()));
    panel->add(squareCountModifierValueLabel);

    // Update the label whenever the slider value changes
    squareCountSlider->onValueChange([=](){
        squareCountModifierValueLabel->setText(std::to_string(squareCountSlider->getValue()));
    });

    // Create a label for the tavern count Modifier
    auto tavernCountLabel = tgui::Label::create();
    tavernCountLabel->setText("Tavern Count Modifier");
    tavernCountLabel->setPosition("10%", "45%");
    panel->add(tavernCountLabel);

    // Create a slider for the tavern count Modifier
    auto tavernCountSlider = tgui::Slider::create();
    tavernCountSlider->setMinimum(0.1f);
    tavernCountSlider->setMaximum(maxSliderValue);
    tavernCountSlider->setStep(0.1f);
    tavernCountSlider->setValue(WorldSettings::GetTavernCountModifier());
    tavernCountSlider->setPosition("10%", "50%");
    panel->add(tavernCountSlider);

    // Create a label for the tavern count modifier value
    auto tavernCountModifierValueLabel = tgui::Label::create();
    tavernCountModifierValueLabel->setPosition("60%", "50%");
    tavernCountModifierValueLabel->setText(std::to_string(WorldSettings::GetTavernCountModifier()));
    panel->add(tavernCountModifierValueLabel);

    // Update the label whenever the slider value changes
    tavernCountSlider->onValueChange([=](){
        tavernCountModifierValueLabel->setText(std::to_string(tavernCountSlider->getValue()));
    });


    // Create a label for the enemy school count
    auto enemySchoolCountLabel = tgui::Label::create();
    enemySchoolCountLabel->setText("Enemy School Count");
    enemySchoolCountLabel->setPosition("10%", "55%");
    panel->add(enemySchoolCountLabel);

    // Create a slider for the enemy school count
    auto enemySchoolCountSlider = tgui::Slider::create();
    enemySchoolCountSlider->setMinimum(1);
    enemySchoolCountSlider->setMaximum(10);
    enemySchoolCountSlider->setStep(1);
    enemySchoolCountSlider->setValue(3);
    enemySchoolCountSlider->setPosition("10%", "60%");
    panel->add(enemySchoolCountSlider);

    // Create a label for the enemy school count value
    auto enemySchoolCountValueLabel = tgui::Label::create();
    enemySchoolCountValueLabel->setPosition("60%", "60%");
    enemySchoolCountValueLabel->setText("3");
    panel->add(enemySchoolCountValueLabel);

    // Update the label whenever the slider value changes
    enemySchoolCountSlider->onValueChange([=](){
        enemySchoolCountValueLabel->setText(std::to_string(enemySchoolCountSlider->getValue()));
    });

    // Text box for the player hero name
    auto playerHeroNameLabel = tgui::Label::create();
    playerHeroNameLabel->setText("Player Hero Name");
    playerHeroNameLabel->setPosition("10%", "65%");
    panel->add(playerHeroNameLabel);

    auto playerHeroNameTextBox = tgui::EditBox::create();
    playerHeroNameTextBox->setPosition("10%", "70%");
    playerHeroNameTextBox->setSize("80%", "5%");
    playerHeroNameTextBox->setDefaultText("Hero");
    panel->add(playerHeroNameTextBox);

    // Text box for the player magic school name
    auto playerMagicSchoolNameLabel = tgui::Label::create();
    playerMagicSchoolNameLabel->setText("Player Magic School Name");
    playerMagicSchoolNameLabel->setPosition("10%", "75%");
    panel->add(playerMagicSchoolNameLabel);

    auto playerMagicSchoolNameTextBox = tgui::EditBox::create();
    playerMagicSchoolNameTextBox->setPosition("10%", "80%");
    playerMagicSchoolNameTextBox->setSize("80%", "5%");
    playerMagicSchoolNameTextBox->setDefaultText("Magic School");
    panel->add(playerMagicSchoolNameTextBox);

    // list box for the player hero spell
    auto playerHeroSpellLabel = tgui::Label::create();
    playerHeroSpellLabel->setText("Player Hero Spell");
    playerHeroSpellLabel->setPosition("10%", "85%");
    panel->add(playerHeroSpellLabel);

    auto playerHeroSpellListBox = tgui::ListBox::create();
    playerHeroSpellListBox->setPosition("10%", "90%");
    playerHeroSpellListBox->setSize("80%", "15%");
    panel->add(playerHeroSpellListBox);

    for(auto& spell : GameLoudObject::GetSpells())
    {
        playerHeroSpellListBox->addItem(spell->getName());
    }

    playerHeroSpellListBox->onItemSelect([=](){
        WorldSettings::SetPlayerHeroSpell(GameLoudObject::GetSpellByName(playerHeroSpellListBox->getSelectedItem().toStdString()));
    });


    // Creating Seed Label
    auto seedLabel = tgui::Label::create();
    seedLabel->setText("Seed");
    seedLabel->setPosition("10%", "105%");
    panel->add(seedLabel);

    // Creating Seed TextBox
    auto seedTextBox = tgui::EditBox::create();
    seedTextBox->setPosition("10%", "110%");
    seedTextBox->setSize("80%", "5%");
    seedTextBox->setDefaultText("0");
    panel->add(seedTextBox);


    // Create a button to start the game
    auto startGameButton = tgui::Button::create();
    startGameButton->setText("Start Game");
    startGameButton->setPosition("10%", "120%");
    startGameButton->setSize("80%", "10%");
    startGameButton->onClick([&](){
        if(playerHeroSpellListBox->getSelectedItem().empty())
        {
            return;
        }
        WorldSettings::SetCityPopulationModifier(cityPopulationModifierSlider->getValue());
        WorldSettings::SetTavernPopulationModifier(tavernPopulationSlider->getValue());
        WorldSettings::SetSquarePopulationModifier(squarePopulationSlider->getValue());
        WorldSettings::SetSquareCountModifier(squareCountSlider->getValue());
        WorldSettings::SetTavernCountModifier(tavernCountSlider->getValue());
        WorldSettings::SetNumberOfEnemiesSchools(enemySchoolCountSlider->getValue());
        WorldSettings::SetPlayerHeroName(playerHeroNameTextBox->getText().toStdString());
        WorldSettings::SetPlayerMagicSchoolName(playerMagicSchoolNameTextBox->getText().toStdString());
        if(!seedTextBox->getText().empty())
        {
            WorldSettings::SetSeed(std::stoi(seedTextBox->getText().toStdString()));
        } else
        {
            WorldSettings::SetSeed(0);
        }

        startGame = true;
        window.close();
    });

    panel->add(startGameButton);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            gui.handleEvent(event);
        }

        window.clear(sf::Color::White);

        gui.draw();
        window.display();
    }

    if(!startGame)
    {
        return 0;
    }
    WorldSettings::SetPlayerHeroSpell(GameLoudObject::GetSpellByName("fireBall"));
    //std::weak_ptr<Spell> spell = WorldSettings::GetPlayerHeroSpell();
    WorldSettings::ApplyModifiers();
    game.start();
    game.run();

    return 0;
}


