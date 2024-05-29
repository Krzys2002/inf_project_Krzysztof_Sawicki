//
// Created by Krzysztof Sawicki on 19/05/2024.
//

#include "../Headers/ListPanel.h"


ListPanel::ListPanel()
{
    listBox = tgui::ListBox::create();
    listBox->setSize("100%", "90%");
    listBox->setAutoLayout(tgui::AutoLayout::Bottom);
    listBox->setPosition(0, 0);
    listBox->setTextSize(12);
    listBox->setItemHeight(20);
    add(listBox);

    Title = tgui::Label::create();
    Title->setTextSize(20);
    Title->setPosition(0, 0);
    Title->setSize("100%", "10%");
    Title->setText("Title");
    Title->getRenderer()->setBackgroundColor(sf::Color(200, 200, 200));
    Title->getRenderer()->setTextColor(sf::Color::Black);
    Title->getRenderer()->setBorders({ 1 });
    Title->getRenderer()->setBorderColor(sf::Color::Black);
    Title->setVerticalAlignment( tgui::Label::VerticalAlignment::Center); // Center the text in the label
    Title->setHorizontalAlignment( tgui::Label::HorizontalAlignment::Center); // Center the text in the label
    add(Title);
}

void ListPanel::setTitleSize(unsigned int size)
{
    Title->setTextSize(size);
}

void ListPanel::setTitleBordSize(tgui::Layout size)
{
    Title->setSize("100%", size);
    listBox->setSize("100%", "100%" - size);
}

void ListPanel::addItem(std::shared_ptr<GameObject>& item)
{
    std::string text = "Name: " + item->getName() + " ID: " + std::to_string(item->getID());
    listBox->addItem(text);
    items.push_back(item);
}

void ListPanel::setTitle(const std::string& title)
{
    Title->setText(title);
    this->title = title;
}

void ListPanel::clearItems()
{
    listBox->removeAllItems();
    items.clear();
}

ListPanel::Ptr ListPanel::create()
{
    return std::make_shared<ListPanel>();
}

void ListPanel::addFunctionOnSelected(std::function<void(std::shared_ptr<GameObject>)> function)
{
    listBox->onItemSelect([this, function](int index){
        if(index < 0 || index >= items.size())
            return;
        function(items[index]);
    });
}