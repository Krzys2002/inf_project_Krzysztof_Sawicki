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

void ListPanel::addItem(std::weak_ptr<GameObject> item)
{
    if(!item.lock())
        return;
    std::string text = "Name: " + item.lock()->getName() + " ID: " + std::to_string(item.lock()->getID());
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

void ListPanel::addFunctionOnSelected(std::function<void(std::weak_ptr<GameObject>)> function)
{
    listBox->onItemSelect([this, function](int index){
        if(index < 0 || index >= items.size())
            return;
        selected = index;
        function(items[index]);
    });
}

void ListPanel::addItem(std::weak_ptr<GameObject> item, const std::string &text)
{
    if(!item.lock())
        return;
    listBox->addItem(text);
    items.emplace_back(item);
}

std::weak_ptr<GameObject> ListPanel::getSelected()
{
    if(selected < 0 || selected >= items.size())
        return {};
    return items[selected];
}

void ListPanel::removeItem(std::weak_ptr<GameObject> item)
{
    for(int i = 0; i < items.size(); i++)
    {
        if(items[i].lock() == item.lock())
        {
            listBox->removeItemByIndex(i);
            items.erase(items.begin() + i);
            return;

            if(selected == i)
                selected = -1;
        }
    }
}

void ListPanel::removeItem(int index)
{
    if(index < 0 || index >= items.size())
        return;
    listBox->removeItemByIndex(index);
    items.erase(items.begin() + index);

    if(selected == index)
        selected = -1;
}
