//
// Created by Krzysztof Sawicki on 19/05/2024.
//

#include "../Headers/UIManager.h"

UIManager::UIManager(Game* game, sf::RenderWindow* window)
{
    this->game = game;
    gui.setTarget(*window);
}

UIManager::~UIManager()
{
    panelLeft.reset();
    panelMiddle.reset();
    panelRight.reset();
    panelBottom.reset();
}

void UIManager::configLeft(tgui::Panel::Ptr panel)
{
    panel->setPosition(0, "10%");
    panel->setSize("33.33%", "80%");
    MaskConfig();
}

void UIManager::configRight(tgui::Panel::Ptr panel)
{
    panel->setPosition("66.66%", "10%");
    panel->setSize("33.33%", "80%");
    MaskConfig();
}

void UIManager::configMiddle(tgui::Panel::Ptr panel)
{
    panel->setPosition("33.33%", "10%");
    panel->setSize("33.33%", "80%");
    MaskConfig();
}

void UIManager::MaskConfig()
{
    if(panelMiddle != nullptr)
        panelMiddle->moveToBack();

    if(panelRight != nullptr)
        panelRight->moveToFront();

    if(panelLeft != nullptr)
        panelLeft->moveToFront();
}



void UIManager::start()
{
    panelLeft = ListPanel::create();
    configLeft(panelLeft);
    gui.add(panelLeft);


    panelRight = ListPanel::create();
    configRight(panelRight);
    gui.add(panelRight);

    panelMiddle = InfoPanel::create(3,0, 3);
    configMiddle(panelMiddle);
    gui.add(panelMiddle);

    panelBottom = tgui::Panel::create();
    panelBottom->setPosition(0, "90%");
    panelBottom->setSize("100%", "10%");
    gui.add(panelBottom);

    auto button = tgui::Button::create();
    button->setText("Next Round");
    button->setPosition("10%", "10%");
    button->setSize("10%", "80%");
    button->onClick( [this](){
        game->NextRound();
    });
    panelBottom->add(button);

    panelTop = tgui::Panel::create();
    panelTop->setPosition(0, 0);
    panelTop->setSize("100%", "10%");
    gui.add(panelTop);

    panelMiddle->moveToBack();
    panelRight->moveToFront();
    panelLeft->moveToFront();


}

tgui::Gui& UIManager::getGui()
{
    return gui;
}

void UIManager::ListGameObjectsOnPanel(MainPanelIndex panelIndex, std::string title, std::vector<std::shared_ptr<GameObject>>& gameObjects)
{
    // Create a new ListPanel and add items to it
    ListPanel::Ptr temp = ListPanel::create();
    temp->setTitle(title);
    for (auto& gameObject : gameObjects)
    {
        temp->addItem(gameObject);
    }


    switch (panelIndex)
    {
        case MainPanelIndex::LEFT:
            // Remove the old panelLeft from the GUI
            gui.remove(panelLeft);
            // Assign temp to panelLeft
            panelLeft = temp;
            // Add the new panelLeft to the GUI
            gui.add(panelLeft);
            configLeft(panelLeft);
            break;
        case MainPanelIndex::RIGHT:
            // Remove the old panelLeft from the GUI
            gui.remove(panelRight);
            // Assign temp to panelLeft
            panelRight = temp;
            // Add the new panelLeft to the GUI
            gui.add(panelRight);
            configRight(panelRight);
            break;
        case MainPanelIndex::MIDDLE:
            // Remove the old panelLeft from the GUI
            gui.remove(panelMiddle);
            // Assign temp to panelLeft
            panelMiddle = temp;
            // Add the new panelLeft to the GUI
            gui.add(panelMiddle);
            configMiddle(panelMiddle);
            break;
    }
}

void UIManager::viewObjectInfo(MainPanelIndex indexOfPanel, std::shared_ptr<GameObject> &gameObject)
{
    Instance* instance = dynamic_cast<Instance*>(gameObject.get());

    if(instance != nullptr)
    {
        viewInstanceInfo(indexOfPanel, instance);
        return;
    }

    Agent* agent = dynamic_cast<Agent*>(gameObject.get());

    if(agent != nullptr)
    {
        viewAgentInfo(indexOfPanel, agent);
        return;
    }

    viewGameObjectInfo(indexOfPanel, gameObject.get());
}

void UIManager::viewGameObjectInfo(MainPanelIndex indexOfPanel, GameObject *gameObject)
{
    InfoPanel::Ptr temp = InfoPanel::create(3,0, 0);
    temp->setLabel(0, "ID: " + std::to_string(gameObject->getID()));
    temp->setLabel(1, "Name: " + gameObject->getName());
    temp->setTitle("GameObject Info");

    switch (indexOfPanel)
    {
        case MainPanelIndex::LEFT:
            // Remove the old panelLeft from the GUI
            gui.remove(panelLeft);
            // Assign temp to panelLeft
            panelLeft = temp;
            // Add the new panelLeft to the GUI
            gui.add(panelLeft);
            configLeft(panelLeft);
            break;
        case MainPanelIndex::RIGHT:
            // Remove the old panelLeft from the GUI
            gui.remove(panelRight);
            // Assign temp to panelLeft
            panelRight = temp;
            // Add the new panelLeft to the GUI
            gui.add(panelRight);
            configRight(panelRight);
            break;
        case MainPanelIndex::MIDDLE:
            // Remove the old panelLeft from the GUI
            gui.remove(panelMiddle);
            // Assign temp to panelLeft
            panelMiddle = temp;
            // Add the new panelLeft to the GUI
            gui.add(panelMiddle);
            configMiddle(panelMiddle);
            break;
    }
}

void UIManager::viewAgentInfo(MainPanelIndex indexOfPanel, Agent *agent)
{
    InfoPanel::Ptr temp = InfoPanel::create(3,0, 0);
    temp->setLabel(0, "ID: " + std::to_string(agent->getID()));
    temp->setLabel(1, "Name: " + agent->getName());
    temp->setLabel(2, "Current Instance: " + agent->GetCurrentInstance()->getName());
    temp->setTitle("Agent Info");

    switch (indexOfPanel)
    {
        case MainPanelIndex::LEFT:
            // Remove the old panelLeft from the GUI
            gui.remove(panelLeft);
            // Assign temp to panelLeft
            panelLeft = temp;
            // Add the new panelLeft to the GUI
            gui.add(panelLeft);
            configLeft(panelLeft);
            break;
        case MainPanelIndex::RIGHT:
            // Remove the old panelLeft from the GUI
            gui.remove(panelRight);
            // Assign temp to panelLeft
            panelRight = temp;
            // Add the new panelLeft to the GUI
            gui.add(panelRight);
            configRight(panelRight);
            break;
        case MainPanelIndex::MIDDLE:
            // Remove the old panelLeft from the GUI
            gui.remove(panelMiddle);
            // Assign temp to panelLeft
            panelMiddle = temp;
            // Add the new panelLeft to the GUI
            gui.add(panelMiddle);
            configMiddle(panelMiddle);
            break;
    }
}

void UIManager::viewInstanceInfo(MainPanelIndex indexOfPanel, Instance *instance)
{
    InfoPanel::Ptr temp = InfoPanel::create(3,2, 2);
    temp->setLabel(0, "ID: " + std::to_string(instance->getID()));
    temp->setLabel(1, "Name: " + instance->getName());
    temp->setLabel(2, "Parent Instance: " + (instance->GetParentInstance() == nullptr ? "None" : instance->GetParentInstance()->getName()));
    temp->setListBox(0, "Children Instances");
    temp->setButton(0, "View Children Instances");
    temp->setButtonCallback(0, [this, instance](){
        std::vector<std::shared_ptr<GameObject>> children;
        std::vector<std::shared_ptr<Instance>> childrenInstances = instance->getChildrenInstances();
        for(auto& child : childrenInstances)
        {
            children.push_back(child);
        }
        this->ListGameObjectsOnPanel(MainPanelIndex::MIDDLE, "Children Instances", children);
        this->setPanelToViewObjectInfoFor(MainPanelIndex::MIDDLE, MainPanelIndex::RIGHT);
    });
    temp->setButton(1, "View Busy Agents");
    temp->setButtonCallback(1, [this, instance](){
        std::vector<std::shared_ptr<GameObject>> agents;
        std::vector<std::shared_ptr<Agent>> busyAgents = instance->getBusyAgents();
        for(auto& agent : busyAgents)
        {
            agents.push_back(agent);
        }
        this->ListGameObjectsOnPanel(MainPanelIndex::MIDDLE, "Busy Agents", agents);
        this->setPanelToViewObjectInfoFor(MainPanelIndex::MIDDLE, MainPanelIndex::RIGHT);
    });
    std::vector<std::shared_ptr<Instance>> children = instance->getChildrenInstances();
    for(auto& child : children)
    {
        temp->addItemToListBox(0, std::make_shared<GameObject>(*child));
    }
    temp->setListBox(1, "Busy Agents");
    std::vector<std::shared_ptr<Agent>> busyAgents = instance->getBusyAgents();
    for(auto& agent : busyAgents)
    {
        temp->addItemToListBox(1, std::make_shared<GameObject>(*agent));
    }
    temp->setTitle("Instance Info");

    switch (indexOfPanel)
    {
        case MainPanelIndex::LEFT:
            // Remove the old panelLeft from the GUI
            gui.remove(panelLeft);
            // Assign temp to panelLeft
            panelLeft = temp;
            // Add the new panelLeft to the GUI
            gui.add(panelLeft);
            configLeft(panelLeft);
            break;
        case MainPanelIndex::RIGHT:
            // Remove the old panelLeft from the GUI
            gui.remove(panelRight);
            // Assign temp to panelLeft
            panelRight = temp;
            // Add the new panelLeft to the GUI
            gui.add(panelRight);
            configRight(panelRight);
            break;
        case MainPanelIndex::MIDDLE:
            // Remove the old panelLeft from the GUI
            gui.remove(panelMiddle);
            // Assign temp to panelLeft
            panelMiddle = temp;
            // Add the new panelLeft to the GUI
            gui.add(panelMiddle);
            configMiddle(panelMiddle);
            break;
    }
}

void UIManager::setPanelToViewObjectInfoFor(MainPanelIndex formIndex, MainPanelIndex toIndex)
{
    tgui::Panel::Ptr panel = nullptr;

    switch (formIndex)
    {
        case MainPanelIndex::LEFT:
            panel = panelLeft;
            break;
        case MainPanelIndex::MIDDLE:
            panel = panelMiddle;
            break;
        case MainPanelIndex::RIGHT:
            panel = panelRight;
            break;
    }

    ListPanel* listPanel = dynamic_cast<ListPanel*>(panel.get());

    if(listPanel == nullptr)
        return;

    std::function<void(std::shared_ptr<GameObject>)> function = [this, toIndex](std::shared_ptr<GameObject> object){
        this->viewObjectInfo(toIndex, object);
    };

    listPanel->addFunctionOnSelected(function);
}