#include <iostream>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include "Headers/TimeSpace.h"
#include "Headers/Agent.h"
#include "Headers/Instance.h"
#include "UI/Headers/ListItem.h"



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

    return rightPanel;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Game Time");
    tgui::Gui gui(window);
    GameObject* selectedObject = nullptr;
    Instance* lastSelectedInstance = nullptr;

//    auto scrollablePanel = tgui::ScrollablePanel::create();

//    auto listItem = ListItem::create("Test", {}, [](){std::cout << "Test" << std::endl;});
//    scrollablePanel->add(listItem);
//    gui.add(scrollablePanel);

//    auto listItem2 = ListItem::create("Test2", {}, [](){std::cout << "Test2" << std::endl;});
//    gui.add(listItem2);


    // Create the list for instances
    auto instanceList = tgui::ListBox::create();
    instanceList->setSize({"33%", "100%"});
    instanceList->setPosition({"0%", "0%"});
    gui.add(instanceList);

    // Create the list for agents
    auto agentList = tgui::ListBox::create();
    agentList->setSize({"33%", "100%"});
    agentList->setPosition({"33%", "0%"});
    gui.add(agentList);

    // Create the panel for the right side of the screen
    auto rightPanel = CreatePanel();
//    rightPanel->add(scrollablePanel);
//    scrollablePanel->setSize({"50%", "50%"});
//    scrollablePanel->setPosition({"0%", "50%"});
    gui.add(rightPanel);

    std::vector<Instance*> instances;
    instances.emplace_back(new Instance(0, "Instance 1", nullptr, true));
    instances.emplace_back(new Instance(1, "Instance 2", instances[0], false));
    instances.emplace_back(new Instance(2, "Instance 3", instances[0], false));
    std::vector<Agent*> agents = {};
    for(auto& instance : instances)
    {
        for (int i = 0; i < 25; i++)
        {
            Agent* agent = instance->getFreeRandomAgent(0);
            if(agent != nullptr)
            {
                agents.push_back(agent);
            }
        }
    }


    // Add instances to the instance list
    for (const auto& instance : instances)  // Replace with your instances
    {
        std::string item = "Name: " + instance->getName() + ", ID: " + std::to_string(instance->getID());
        instanceList->addItem(item);
    }

    instanceList->onItemSelect([instances, agentList, rightPanel, agents, &lastSelectedInstance, &selectedObject](int index)
    {
        if(index == -1)
        {
            lastSelectedInstance = nullptr;

            agentList->removeAllItems();
            for(auto agent : agents)
            {
                std::string item = "Name: " + agent->getName() + ", ID: " + std::to_string(agent->getID());
                agentList->addItem(item);
            }
            return;
        } else
        {
            selectedObject = instances[index];
            lastSelectedInstance = instances[index];
            agentList->removeAllItems();
            for(auto agent : instances[index]->getBusyAgents())
            {
                std::string item = "Name: " + agent->getName() + ", ID: " + std::to_string(agent->getID());
                agentList->addItem(item);
            }
        }

        //update the labels in the right panel
        auto instanceTitleLabel = rightPanel->get<tgui::Label>("TitleLabel");
        instanceTitleLabel->setText("Instance Info");

        auto instanceNameLabel = rightPanel->get<tgui::Label>("NameLabel");
        instanceNameLabel->setText("Name: " + instances[index]->getName());

        auto instanceIDLabel = rightPanel->get<tgui::Label>("IDLabel");
        instanceIDLabel->setText("ID: " + std::to_string(instances[index]->getID()));

        auto instanceParentLabel = rightPanel->get<tgui::Label>("InstanceLabel");
        Instance* parentInstance = instances[index]->GetParentInstance();
        if(parentInstance != nullptr)
        {
            instanceParentLabel->setText("Parent: " + parentInstance->getName());
        } else
        {
            instanceParentLabel->setText("Parent: None");
        }
    });

    agentList->onItemSelect([agents, rightPanel, &selectedObject, &lastSelectedInstance](int index)
    {
        Agent *agent;
        if(index == -1)
            return;

        if(lastSelectedInstance != nullptr)
        {
            agent = lastSelectedInstance->getBusyAgents()[index];
        }
        else
        {
            agent = agents[index];
        }

        if(agent == nullptr)
            return;

        selectedObject = agent;

        // Update the labels in the right panel
        auto instanceTitleLabel = rightPanel->get<tgui::Label>("TitleLabel");
        instanceTitleLabel->setText("Agent Info");

        auto agentNameLabel = rightPanel->get<tgui::Label>("NameLabel");
        agentNameLabel->setText("Agent Name: " + agent->getName());

        auto agentIDLabel = rightPanel->get<tgui::Label>("IDLabel");
        agentIDLabel->setText("Agent ID: " + std::to_string(agent->getID()));

        auto agentInstanceLabel = rightPanel->get<tgui::Label>("InstanceLabel");
        agentInstanceLabel->setText("Instance: " + agent->GetCurrentInstance()->getName());
    });

    // Add agents to the agent list
    for (const auto& agent : agents)  // Replace with your agents
    {
        std::string item = "Name: " + agent->getName() + ", ID: " + std::to_string(agent->getID());
        agentList->addItem(item);
    }



    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            gui.handleEvent(event);
        }

        window.clear();
        gui.draw();
        window.display();
    }

    return 0;
}


