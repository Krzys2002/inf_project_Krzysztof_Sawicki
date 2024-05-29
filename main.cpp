#include <iostream>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include "Headers/TimeSpace.h"
#include "Headers/Agent.h"
#include "Headers/Instance.h"
#include "UI/Headers/ListItem.h"
#include "Headers/Game.h"



tgui::Panel::Ptr CreatePanel()
{
    auto rightPanel = tgui::Panel::create();
    rightPanel->setSize({"34%", "100%"});
    rightPanel->setPosition({"66%", "0%"});

    // Create the label for the right panel
    auto rightPanelTitleLabel = tgui::Label::create();
    rightPanelTitleLabel->setText("N/A");
    rightPanelTitleLabel->setPosition({0, 0});
    rightPanelTitleLabel->setSize({"100%", 44});
    rightPanelTitleLabel->setTextSize(16);
    // set name to widget
    rightPanelTitleLabel->setWidgetName("TitleLabel");
    // center the text
    rightPanelTitleLabel->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);
    rightPanelTitleLabel->setVerticalAlignment(tgui::Label::VerticalAlignment::Center);

    rightPanel->add(rightPanelTitleLabel);

    // Create the label for the right panel
    auto rightPanelNameLabel = tgui::Label::create();
    rightPanelNameLabel->setText("");
    rightPanelNameLabel->setPosition({2, 48});
    rightPanelNameLabel->setTextSize(12);
    // set name to widget
    rightPanelNameLabel->setWidgetName("NameLabel");
    // vertical center the text
    rightPanelNameLabel->setVerticalAlignment(tgui::Label::VerticalAlignment::Center);

    rightPanel->add(rightPanelNameLabel);

    // Create the label for the right panel
    auto rightPanelIDLabel = tgui::Label::create();
    rightPanelIDLabel->setText("");
    rightPanelIDLabel->setPosition({2, 64});
    rightPanelIDLabel->setTextSize(12);
    // set name to widget
    rightPanelIDLabel->setWidgetName("IDLabel");
    // vertical center the text
    rightPanelIDLabel->setVerticalAlignment(tgui::Label::VerticalAlignment::Center);

    rightPanel->add(rightPanelIDLabel);

    // Create the label for the right panel
    auto rightPanelInstanceLabel = tgui::Label::create();
    rightPanelInstanceLabel->setText("");
    rightPanelInstanceLabel->setPosition({2, 80});
    rightPanelInstanceLabel->setTextSize(12);
    // set name to widget
    rightPanelInstanceLabel->setWidgetName("InstanceLabel");
    // vertical center the text
    rightPanelInstanceLabel->setVerticalAlignment(tgui::Label::VerticalAlignment::Center);

    rightPanel->add(rightPanelInstanceLabel);

    // Create the label for the right panel
    auto rightPanelParentLabel = tgui::Label::create();
    rightPanelParentLabel->setText("");
    rightPanelParentLabel->setPosition({2, 96});
    rightPanelParentLabel->setTextSize(12);
    // set name to widget
    rightPanelParentLabel->setWidgetName("BoxLabel");
    // vertical center the text
    rightPanelParentLabel->setVerticalAlignment(tgui::Label::VerticalAlignment::Center);

    rightPanel->add(rightPanelParentLabel);

    // Create the ListBox for the right panel
    auto rightPanelListBox = tgui::ListBox::create();
    rightPanelListBox->setSize({"100%", 16 * 5});
    rightPanelListBox->setPosition({0, 112});
    rightPanelListBox->setItemHeight(16);
    // set name to widget
    rightPanelListBox->setWidgetName("ListBox");
    rightPanelListBox->setVisible(false);

    rightPanel->add(rightPanelListBox);

    auto button = tgui::Button::create();
    button->setText("Button 1");
    button->setPosition({"2%", 16 * 5 + 112});
    button->setSize({"22%", 32});
    button->setVisible(false);
    // set name to widget
    button->setWidgetName("Button1");

    rightPanel->add(button);

    button = tgui::Button::create();
    button->setText("Button 2");
    button->setPosition({"26%", 16 * 5 + 112});
    button->setSize({"22%", 32});
    button->setVisible(false);
    // set name to widget
    button->setWidgetName("Button2");

    rightPanel->add(button);

    button = tgui::Button::create();
    button->setText("Button 3");
    button->setPosition({"50%", 16 * 5 + 112});
    button->setSize({"22%", 32});
    button->setVisible(false);
    // set name to widget
    button->setWidgetName("Button3");

    rightPanel->add(button);

    button = tgui::Button::create();
    button->setText("Button 4");
    button->setPosition({"74%", 16 * 5 + 112});
    button->setSize({"22%", 32});
    button->setVisible(false);
    // set name to widget
    button->setWidgetName("Button4");

    rightPanel->add(button);

    return rightPanel;
}

// reset right panel
void ResetPanel(tgui::Panel::Ptr rightPanel)
{
    // empty all labels
    auto label = rightPanel->get<tgui::Label>("TitleLabel");
    label->setText("N/A");
    label = rightPanel->get<tgui::Label>("NameLabel");
    label->setText("");
    label = rightPanel->get<tgui::Label>("IDLabel");
    label->setText("");
    label = rightPanel->get<tgui::Label>("InstanceLabel");
    label->setText("");
    label = rightPanel->get<tgui::Label>("BoxLabel");
    label->setText("");
    auto listBox = rightPanel->get<tgui::ListBox>("ListBox");
    listBox->setVisible(false);
    auto button = rightPanel->get<tgui::Button>("Button1");
    button->setVisible(false);
    button = rightPanel->get<tgui::Button>("Button2");
    button->setVisible(false);
    button = rightPanel->get<tgui::Button>("Button3");
    button->setVisible(false);
    button = rightPanel->get<tgui::Button>("Button4");
    button->setVisible(false);
}

void RefreshListBox(tgui::ListBox::Ptr listBox, std::vector<GameObject*> objects)
{
    listBox->removeAllItems();
    for(auto object : objects)
    {
        std::string item = "Name: " + object->getName() + ", ID: " + std::to_string(object->getID());
        listBox->addItem(item);
    }
}

bool RemoveNullptrs(std::vector<Instance*>& objects)
{
    objects.erase(std::remove(objects.begin(), objects.end(), nullptr), objects.end());
}

bool RemoveNullptrs(std::vector<Agent*>& objects)
{
    int count = objects.size();
    objects.erase(std::remove(objects.begin(), objects.end(), nullptr), objects.end());
}

int main()
{
    Game game;
    game.start();
    game.run();

//    sf::RenderWindow window(sf::VideoMode(800, 600), "Game Time");
//    tgui::Gui gui(window);
//    GameObject* selectedObject = nullptr;
//    Instance* lastSelectedInstance = nullptr;
//
////    auto scrollablePanel = tgui::ScrollablePanel::create();
//
////    auto listItem = ListItem::create("Test", {}, [](){std::cout << "Test" << std::endl;});
////    scrollablePanel->add(listItem);
////    gui.add(scrollablePanel);
//
////    auto listItem2 = ListItem::create("Test2", {}, [](){std::cout << "Test2" << std::endl;});
////    gui.add(listItem2);
//
//
//    // Create the list for instances
//    auto instanceList = tgui::ListBox::create();
//    instanceList->setSize({"33%", "100%"});
//    instanceList->setPosition({"0%", "0%"});
//    gui.add(instanceList);
//
//    // Create the list for agents
//    auto agentList = tgui::ListBox::create();
//    agentList->setSize({"33%", "100%"});
//    agentList->setPosition({"33%", "0%"});
//    gui.add(agentList);
//
//    // Create the panel for the right side of the screen
//    auto rightPanel = CreatePanel();
////    rightPanel->add(scrollablePanel);
////    scrollablePanel->setSize({"50%", "50%"});
////    scrollablePanel->setPosition({"0%", "50%"});
//    gui.add(rightPanel);
//
//    std::vector<Instance*> instances;
//    instances.emplace_back(new Instance(0, "Instance 1", nullptr, true));
//    instances.emplace_back(new Instance(1, "Instance 2", instances[0], false));
//    instances.emplace_back(new Instance(2, "Instance 3", instances[0], false));
//    std::vector<Agent*> agents = {};
//    for(auto& instance : instances)
//    {
//        for (int i = 0; i < 25; i++)
//        {
//            Agent* agent = instance->getFreeRandomAgent(0);
//            if(agent != nullptr)
//            {
//                agents.push_back(agent);
//            }
//        }
//    }
//
//
//    // Add instances to the instance list
//    RefreshListBox(instanceList, std::vector<GameObject*>(instances.begin(), instances.end()));
//
//    instanceList->onItemSelect([=, &lastSelectedInstance, &selectedObject](int index)
//                               {
//        if(index == -1)
//        {
//            lastSelectedInstance = nullptr;
//
//            agentList->removeAllItems();
//            for(auto agent : agents)
//            {
//                std::string item = "Name: " + agent->getName() + ", ID: " + std::to_string(agent->getID());
//                agentList->addItem(item);
//            }
//            return;
//        } else
//        {
//            selectedObject = instances[index];
//            lastSelectedInstance = instances[index];
//            agentList->removeAllItems();
//            for(auto agent : instances[index]->getBusyAgents())
//            {
//                std::string item = "Name: " + agent->getName() + ", ID: " + std::to_string(agent->getID());
//                agentList->addItem(item);
//            }
//        }
//
//        //update the labels in the right panel
//        auto instanceTitleLabel = rightPanel->get<tgui::Label>("TitleLabel");
//        instanceTitleLabel->setText("Instance Info");
//
//        auto instanceNameLabel = rightPanel->get<tgui::Label>("NameLabel");
//        instanceNameLabel->setText("Name: " + instances[index]->getName());
//
//        auto instanceIDLabel = rightPanel->get<tgui::Label>("IDLabel");
//        instanceIDLabel->setText("ID: " + std::to_string(instances[index]->getID()));
//
//        auto instanceParentLabel = rightPanel->get<tgui::Label>("InstanceLabel");
//        Instance* parentInstance = instances[index]->GetParentInstance();
//        if(parentInstance != nullptr)
//        {
//            instanceParentLabel->setText("Parent: " + parentInstance->getName());
//        } else
//        {
//            instanceParentLabel->setText("Parent: None");
//        }
//
//        auto instanceLabelBox = rightPanel->get<tgui::Label>("BoxLabel");
//        instanceLabelBox->setText("Children: ");
//
//        auto instanceListBox = rightPanel->get<tgui::ListBox>("ListBox");
//        instanceListBox->removeAllItems();
//        if(instances[index]->getChildrenInstances().empty())
//        {
//            instanceListBox->setVisible(false);
//            return;
//        }
//        instanceListBox->setVisible(true);
//        for(auto childInstance : instances[index]->getChildrenInstances())
//        {
//            std::string item = "Name: " + childInstance->getName() + ", ID: " + std::to_string(childInstance->getID());
//            instanceListBox->addItem(item);
//        }
//
//        // Show the button1 with text "delete" and add action to it
//        auto button1 = rightPanel->get<tgui::Button>("Button1");
//        button1->setVisible(true);
//        button1->setText("Delete");
//        button1->onClick([=]()
//        {
//            ResetPanel(rightPanel);
//
//            delete instances[index];
//
//            //RefreshListBox(instanceList, std::vector<GameObject*>(instances.begin(), instances.end()));
//
//        });
//    });
//
//    agentList->onItemSelect([agents, rightPanel, &selectedObject, &lastSelectedInstance](int index)
//    {
//        Agent *agent;
//        if(index == -1)
//            return;
//
//        if(lastSelectedInstance != nullptr)
//        {
//            agent = lastSelectedInstance->getBusyAgents()[index];
//        }
//        else
//        {
//            agent = agents[index];
//        }
//
//        if(agent == nullptr)
//            return;
//
//        selectedObject = agent;
//
//        // Update the labels in the right panel
//        auto instanceTitleLabel = rightPanel->get<tgui::Label>("TitleLabel");
//        instanceTitleLabel->setText("Agent Info");
//
//        auto agentNameLabel = rightPanel->get<tgui::Label>("NameLabel");
//        agentNameLabel->setText("Agent Name: " + agent->getName());
//
//        auto agentIDLabel = rightPanel->get<tgui::Label>("IDLabel");
//        agentIDLabel->setText("Agent ID: " + std::to_string(agent->getID()));
//
//        auto agentInstanceLabel = rightPanel->get<tgui::Label>("InstanceLabel");
//        agentInstanceLabel->setText("Instance: " + agent->GetCurrentInstance()->getName());
//
//        auto agentParentLabel = rightPanel->get<tgui::Label>("BoxLabel");
//        agentParentLabel->setVisible(false);
//
//        auto agentListBox = rightPanel->get<tgui::ListBox>("ListBox");
//        agentListBox->setVisible(false);
//    });
//
//    // Add agents to the agent list
//    for (const auto& agent : agents)  // Replace with your agents
//    {
//        std::string item = "Name: " + agent->getName() + ", ID: " + std::to_string(agent->getID());
//        agentList->addItem(item);
//    }
//
//
//
//    while (window.isOpen())
//    {
//        sf::Event event;
//        while (window.pollEvent(event))
//        {
//            if (event.type == sf::Event::Closed)
//                window.close();
//
//            gui.handleEvent(event);
//        }
//
////        RemoveNullptrs(instances);
////        RemoveNullptrs(agents);
////        RefreshListBox(instanceList, std::vector<GameObject*>(instances.begin(), instances.end()));
////        RefreshListBox(agentList, std::vector<GameObject*>(agents.begin(), agents.end()));
//
//        window.clear();
//        gui.draw();
//        window.display();
//    }
//
//    return 0;
}


