//
// Created by Krzysztof Sawicki on 19/05/2024.
//

#include "../Headers/InfoPanel.h"

InfoPanel::InfoPanel(unsigned int numberOfLabels, unsigned int numberOfListBoxes, unsigned int numberOfButtons)
{
    titleLabel = tgui::Label::create();
    titleLabel->setTextSize(20);
    titleLabel->setAutoLayout(tgui::AutoLayout::Top);
    titleLabel->setSize("100%", "10%");
    titleLabel->setText("Title");
    titleLabel->getRenderer()->setBackgroundColor(sf::Color(200, 200, 200));
    titleLabel->getRenderer()->setTextColor(sf::Color::Black);
    titleLabel->getRenderer()->setBorders({ 1 });
    titleLabel->getRenderer()->setBorderColor(sf::Color::Black);
    titleLabel->setVerticalAlignment( tgui::Label::VerticalAlignment::Center); // Center the text in the label
    titleLabel->setHorizontalAlignment( tgui::Label::HorizontalAlignment::Center); // Center the text in the label
    getRenderer()->setBorders({ 1 });
    add(titleLabel);


    labels.resize(numberOfLabels);
    for (unsigned int i = 0; i < numberOfLabels; ++i)
    {
        labels[i] = tgui::Label::create();
        labels[i]->setTextSize(12);
        labels[i]->setAutoLayout(tgui::AutoLayout::Top);
        labels[i]->setSize("90%", 18); // Reduce the width to 90% to make room for the margin

        labels[i]->setText("Label " + std::to_string(i));
        labels[i]->getRenderer()->setBorderColor(sf::Color::Black);
        labels[i]->setVerticalAlignment( tgui::Label::VerticalAlignment::Center); // Center the text in the label
        add(labels[i]);
    }

    listBoxes.resize(numberOfListBoxes);
    for (unsigned int i = 0; i < numberOfListBoxes; ++i)
    {
        listBoxes[i] = ListPanel::create();
        listBoxes[i]->setSize("90%", "30%");
        listBoxes[i]->setAutoLayout(tgui::AutoLayout::Top);
        listBoxes[i]->setTitle("List Box " + std::to_string(i));
        listBoxes[i]->setTitleSize(12);
        listBoxes[i]->setTitleBordSize("15%");
        add(listBoxes[i]);
    }

    buttons.resize(numberOfButtons);
    for (unsigned int i = 0; i < numberOfButtons; ++i)
    {
        buttons[i] = tgui::Button::create();
        buttons[i]->setTextSize(12);
        buttons[i]->setAutoLayout(tgui::AutoLayout::Top);
        buttons[i]->setSize("90%", "7%");
        buttons[i]->setText("Button " + std::to_string(i));
        buttons[i]->getRenderer()->setBorderColor(sf::Color::Black);
        add(buttons[i]);
    }
}

void InfoPanel::setListBox(unsigned int index, const std::string& title)
{
    if (index < listBoxes.size())
        listBoxes[index]->setTitle(title);
}

void InfoPanel::addItemToListBox(unsigned int index, std::shared_ptr<GameObject> item)
{
    if (index < listBoxes.size())
        listBoxes[index]->addItem(item);
}

void InfoPanel::setTitle(const std::string& title)
{
    titleLabel->setText(title);
}

void InfoPanel::setLabel(unsigned int index, const std::string& text)
{
    if (index < labels.size())
        labels[index]->setText(text);
}

void InfoPanel::setButton(unsigned int index, const std::string& text)
{
    if (index < buttons.size())
        buttons[index]->setText(text);
}

void InfoPanel::setButtonCallback(unsigned int index, const std::function<void()>& callback)
{
    if (index < buttons.size())
        buttons[index]->onClick(callback);
}

InfoPanel::Ptr InfoPanel::create(unsigned int numberOfLabels, unsigned int numberOfListBoxes, unsigned int numberOfButtons)
{
    return std::make_shared<InfoPanel>(numberOfLabels, numberOfListBoxes, numberOfButtons);
}