#include <iostream>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include "Headers/TimeSpace.h"
#include "Headers/Agent.h"
#include "Headers/Instance.h"
#include "UI/Headers/ListItem.h"
#include "Headers/Game.h"
#include "Headers/WorldSettings.h"



int main()
{
    Game game;
    sf::RenderWindow window(sf::VideoMode(800, 600), "Settings");
    WorldSettings* worldSettings = new WorldSettings();
    bool startGame = false;
    float maxSliderValue = 5.0f;

    std::cout << worldSettings->getCityPopulationModifier() << std::endl;

    tgui::Gui gui{window};
    //Create a label for the city population modifier
    auto cityPopulationModifierLabel = tgui::Label::create();
    cityPopulationModifierLabel->setText("City Population Modifier");
    cityPopulationModifierLabel->setPosition("10%", "5%");
    gui.add(cityPopulationModifierLabel);

    // Create a slider for the city population modifier
    auto cityPopulationModifierSlider = tgui::Slider::create();
    cityPopulationModifierSlider->setMinimum(0.1f);
    cityPopulationModifierSlider->setMaximum(maxSliderValue);
    cityPopulationModifierSlider->setStep(0.1f);
    cityPopulationModifierSlider->setValue(worldSettings->getCityPopulationModifier());
    cityPopulationModifierSlider->setPosition("10%", "10%");
    gui.add(cityPopulationModifierSlider);

    // Create a label for the city population modifier value
    auto cityPopulationModifierValueLabel = tgui::Label::create();
    cityPopulationModifierValueLabel->setPosition("60%", "10%");
    cityPopulationModifierValueLabel->setText(std::to_string(worldSettings->getCityPopulationModifier()));
    gui.add(cityPopulationModifierValueLabel);

    // Update the label whenever the slider value changes
    cityPopulationModifierSlider->onValueChange([=](){
        cityPopulationModifierValueLabel->setText(std::to_string(cityPopulationModifierSlider->getValue()));
    });

    // Create a label for the tavern population Modifier
    auto tavernPopulationLabel = tgui::Label::create();
    tavernPopulationLabel->setText("Tavern Population Modifier");
    tavernPopulationLabel->setPosition("10%", "15%");
    gui.add(tavernPopulationLabel);

    // Create a slider for the tavern population Modifier
    auto tavernPopulationSlider = tgui::Slider::create();
    tavernPopulationSlider->setMinimum(0.1f);
    tavernPopulationSlider->setMaximum(maxSliderValue);
    tavernPopulationSlider->setStep(0.1f);
    tavernPopulationSlider->setValue(worldSettings->getTavernPopulationModifier());
    tavernPopulationSlider->setPosition("10%", "20%");
    gui.add(tavernPopulationSlider);

    // Create a label for the tavern population modifier value
    auto tavernPopulationModifierValueLabel = tgui::Label::create();
    tavernPopulationModifierValueLabel->setPosition("60%", "20%");
    tavernPopulationModifierValueLabel->setText(std::to_string(worldSettings->getTavernPopulationModifier()));
    gui.add(tavernPopulationModifierValueLabel);

    // Update the label whenever the slider value changes
    tavernPopulationSlider->onValueChange([=](){
        tavernPopulationModifierValueLabel->setText(std::to_string(tavernPopulationSlider->getValue()));
    });

    // Create a label for the square population Modifier
    auto squarePopulationLabel = tgui::Label::create();
    squarePopulationLabel->setText("Square Population Modifier");
    squarePopulationLabel->setPosition("10%", "25%");
    gui.add(squarePopulationLabel);

    // Create a slider for the square population Modifier
    auto squarePopulationSlider = tgui::Slider::create();
    squarePopulationSlider->setMinimum(0.1f);
    squarePopulationSlider->setMaximum(maxSliderValue);
    squarePopulationSlider->setStep(0.1f);
    squarePopulationSlider->setValue(worldSettings->getSquarePopulationModifier());
    squarePopulationSlider->setPosition("10%", "30%");
    gui.add(squarePopulationSlider);

    // Create a label for the square population modifier value
    auto squarePopulationModifierValueLabel = tgui::Label::create();
    squarePopulationModifierValueLabel->setPosition("60%", "30%");
    squarePopulationModifierValueLabel->setText(std::to_string(worldSettings->getSquarePopulationModifier()));
    gui.add(squarePopulationModifierValueLabel);

    // Update the label whenever the slider value changes
    squarePopulationSlider->onValueChange([=](){
        squarePopulationModifierValueLabel->setText(std::to_string(squarePopulationSlider->getValue()));
    });

    // Create a label for the square count Modifier
    auto squareCountLabel = tgui::Label::create();
    squareCountLabel->setText("Square Count Modifier");
    squareCountLabel->setPosition("10%", "35%");
    gui.add(squareCountLabel);

    // Create a slider for the square count Modifier
    auto squareCountSlider = tgui::Slider::create();
    squareCountSlider->setMinimum(0.1f);
    squareCountSlider->setMaximum(maxSliderValue);
    squareCountSlider->setStep(0.1f);
    squareCountSlider->setValue(worldSettings->getSquareCountModifier());
    squareCountSlider->setPosition("10%", "40%");
    gui.add(squareCountSlider);

    // Create a label for the square count modifier value
    auto squareCountModifierValueLabel = tgui::Label::create();
    squareCountModifierValueLabel->setPosition("60%", "40%");
    squareCountModifierValueLabel->setText(std::to_string(worldSettings->getSquareCountModifier()));
    gui.add(squareCountModifierValueLabel);

    // Update the label whenever the slider value changes
    squareCountSlider->onValueChange([=](){
        squareCountModifierValueLabel->setText(std::to_string(squareCountSlider->getValue()));
    });

    // Create a label for the tavern count Modifier
    auto tavernCountLabel = tgui::Label::create();
    tavernCountLabel->setText("Tavern Count Modifier");
    tavernCountLabel->setPosition("10%", "45%");
    gui.add(tavernCountLabel);

    // Create a slider for the tavern count Modifier
    auto tavernCountSlider = tgui::Slider::create();
    tavernCountSlider->setMinimum(0.1f);
    tavernCountSlider->setMaximum(maxSliderValue);
    tavernCountSlider->setStep(0.1f);
    tavernCountSlider->setValue(worldSettings->getTavernCountModifier());
    tavernCountSlider->setPosition("10%", "50%");
    gui.add(tavernCountSlider);

    // Create a label for the tavern count modifier value
    auto tavernCountModifierValueLabel = tgui::Label::create();
    tavernCountModifierValueLabel->setPosition("60%", "50%");
    tavernCountModifierValueLabel->setText(std::to_string(worldSettings->getTavernCountModifier()));
    gui.add(tavernCountModifierValueLabel);

    // Update the label whenever the slider value changes
    tavernCountSlider->onValueChange([=](){
        tavernCountModifierValueLabel->setText(std::to_string(tavernCountSlider->getValue()));
    });


    // Create a button to start the game
    auto startGameButton = tgui::Button::create();
    startGameButton->setText("Start Game");
    startGameButton->setPosition("10%", "90%");
    startGameButton->setSize("80%", "10%");
    startGameButton->onClick([&](){
        worldSettings->setCityPopulationModifier(cityPopulationModifierSlider->getValue());
        worldSettings->setTavernPopulationModifier(tavernPopulationSlider->getValue());
        worldSettings->setSquarePopulationModifier(squarePopulationSlider->getValue());
        worldSettings->setSquareCountModifier(squareCountSlider->getValue());
        worldSettings->setTavernCountModifier(tavernCountSlider->getValue());
        startGame = true;
        window.close();
    });

    gui.add(startGameButton);

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
    worldSettings->ApplyModifiers();
    game.setWorldSettings(worldSettings);
    game.start();
    game.run();

    return 0;
}


