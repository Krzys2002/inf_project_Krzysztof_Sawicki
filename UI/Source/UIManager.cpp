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

}


void UIManager::start()
{
    // Create the mask panel
    panelMask = tgui::Panel::create();
    panelMask->setSize("100%", "100%");
    panelMask->setPosition(0, 0);
    panelMask->getRenderer()->setBackgroundColor(sf::Color(0, 0, 0, 100));
    panelMask->setVisible(false);
    gui.add(panelMask);

    // Create the label for the mask panel
    tgui::Label::Ptr label = tgui::Label::create();
    label->setOrigin(0.5f, 0.5f);
    label->setPosition("50%", "50%");
    label->setTextSize(30);
    label->getRenderer()->setTextColor(sf::Color::White);
    label->setWidgetName("Massage");
    label->setText("Creating world...");
    panelMask->add(label);


    if(game->isWorldCreatedFlag() || game->isNextRoundThreadRunningFlag())
    {
        lockGui("Creating world...");
    }
}

void UIManager::update(sf::Time deltaTime)
{
    static sf::Time time = sf::Time::Zero;

    time += deltaTime;
    // Check if the world is created
    if(!game->isWorldCreatedFlag())
    {
        if(!isGuiLocked)
        {
            lockGui("Creating world");
        } else
        {
            std::string text = "Creating world";
            for(int i = 0; i <= static_cast<int>(time.asSeconds()) % 3; i++)
            {
                text += ".";
            }
            panelMask->get<tgui::Label>("Massage")->setText(text);
        }
    } // Check if the next round thread is running
    else if(game->isNextRoundThreadRunningFlag())
    {
        if(!isGuiLocked)
        {
            lockGui("Next round");
        } else
        {
            std::string text = "Next round";
            for(int i = 0; i <= static_cast<int>(time.asSeconds()) % 3; i++)
            {
                text += ".";
            }
            panelMask->get<tgui::Label>("Massage")->setText(text);
        }
    }
    else
    {
        // Check if the GUI is locked of the main panel is null
        if(isGuiLocked || mainPanel == nullptr)
        {
            // remove the main panel from the GUI
            if(mainPanel != nullptr)
            {
                gui.remove(mainPanel);
            }
            // Check the current main panel index
            switch (currentMainPanelIndex)
            {
                case MainPanelIndex::Recruit:
                    mainPanel = recruitPanel();
                    break;

                case MainPanelIndex::AcceptTask:
                    mainPanel = taskAcceptPanel();
                    break;

                case MainPanelIndex::Distribut:
                    mainPanel = taskDistributionPanel();
                    break;
            }

            if(mainPanel == nullptr)
            {
                return;
            }
            gui.add(mainPanel);
            int goldInRound = 0;
            int manaStoneInRound = 0;

            std::vector<Game::GameEvent> events = game->getGameEventsInRound();

            //acuumulate gold and MS
            for(auto& event : events)
            {
                auto task = std::dynamic_pointer_cast<Task>(event.from().lock());
                goldInRound += task->getReward()[static_cast<int>(GameLoudObject::ResourceType::Gold)];
                manaStoneInRound += task->getReward()[static_cast<int>(GameLoudObject::ResourceType::MagicStone)];
            }
            // add message on screen
            std::string text = "Gold: +" + std::to_string(goldInRound) + " Magic Stones: +" + std::to_string(manaStoneInRound);
            tgui::Panel::Ptr massage = massageWin(text);

            massage->moveToFront();
            mainPanel->add(massage);

            unlockGui();
        }
    }

}

tgui::Gui& UIManager::getGui()
{
    return gui;
}

//void UIManager::viewAgentInfo(MainPanelIndex indexOfPanel, std::weak_ptr<Agent> agent)
//{
//    InfoPanel::Ptr temp = InfoPanel::create(5,0, 0);
//    temp->setLabel(0, "ID: " + std::to_string(agent.lock()->getID()));
//    temp->setLabel(1, "Name: " + agent.lock()->getName());
//    temp->setLabel(2, "Current Instance: " + agent.lock()->getCurrentInstance()->getName());
//    temp->setLabel(3, "Main Profession: " + professionToString(agent.lock()->getMainProfession()));
//    temp->setLabel(4, "Description: " + agent.lock()->getDescription());
//    temp->setTitle("Agent Info");
//
//    switch (indexOfPanel)
//    {
//        case MainPanelIndex::LEFT:
//            // Remove the old panelLeft from the GUI
//            gui.remove(panelLeft);
//            // Assign temp to panelLeft
//            panelLeft = temp;
//            // Add the new panelLeft to the GUI
//            gui.add(panelLeft);
//            configLeft(panelLeft);
//            break;
//        case MainPanelIndex::RIGHT:
//            // Remove the old panelLeft from the GUI
//            gui.remove(panelRight);
//            // Assign temp to panelLeft
//            panelRight = temp;
//            // Add the new panelLeft to the GUI
//            gui.add(panelRight);
//            configRight(panelRight);
//            break;
//        case MainPanelIndex::MIDDLE:
//            // Remove the old panelLeft from the GUI
//            gui.remove(panelMiddle);
//            // Assign temp to panelLeft
//            panelMiddle = temp;
//            // Add the new panelLeft to the GUI
//            gui.add(panelMiddle);
//            configMiddle(panelMiddle);
//            break;
//    }
//}

//void UIManager::viewInstanceInfo(MainPanelIndex indexOfPanel, std::weak_ptr<Instance> instance)
//{
//    InfoPanel::Ptr temp = InfoPanel::create(5,2, 2);
//    temp->setLabel(0, "ID: " + std::to_string(instance.lock()->getID()));
//    temp->setLabel(1, "Name: " + instance.lock()->getName());
//    temp->setLabel(2, "Parent Instance: " + (instance.lock()->getParentInstance() == nullptr ? "None" : instance.lock()->getParentInstance()->getName()));
//    temp->setLabel(3, "Description: " + instance.lock()->getDescription());
//    temp->setListBox(0, "Children Instances");
//    temp->setButton(0, "View Children Instances");
//    temp->setButtonCallback(0, [this, instance](){
//        std::vector<std::weak_ptr<GameObject>> children;
//        std::vector<std::shared_ptr<Instance>> childrenInstances = instance.lock()->getChildrenInstances();
//        for(auto& child : childrenInstances)
//        {
//            children.push_back(child);
//        }
//        this->ListGameObjectsOnPanel(MainPanelIndex::MIDDLE, "Children Instances", children);
//        this->setPanelToViewObjectInfoFor(MainPanelIndex::MIDDLE, MainPanelIndex::RIGHT);
//    });
//    temp->setButton(1, "View Busy Agents");
//    temp->setButtonCallback(1, [this, instance](){
//        std::vector<std::weak_ptr<GameObject>> agents;
//        std::vector<std::shared_ptr<Agent>> busyAgents = instance.lock()->getBusyAgents();
//        for(auto& agent : busyAgents)
//        {
//            agents.push_back(agent);
//        }
//        this->ListGameObjectsOnPanel(MainPanelIndex::MIDDLE, "Busy Agents", agents);
//        this->setPanelToViewObjectInfoFor(MainPanelIndex::MIDDLE, MainPanelIndex::RIGHT);
//    });
//    std::vector<std::shared_ptr<Instance>> children = instance.lock()->getChildrenInstances();
//    for(auto& child : children)
//    {
//        temp->addItemToListBox(0, std::make_shared<GameObject>(*child));
//    }
//    temp->setListBox(1, "Busy Agents");
//    std::vector<std::shared_ptr<Agent>> busyAgents = instance.lock()->getBusyAgents();
//    for(auto& agent : busyAgents)
//    {
//        temp->addItemToListBox(1, std::make_shared<GameObject>(*agent));
//    }
//    temp->setTitle("Instance Info");
//
//    switch (indexOfPanel)
//    {
//        case MainPanelIndex::LEFT:
//            // Remove the old panelLeft from the GUI
//            gui.remove(panelLeft);
//            // Assign temp to panelLeft
//            panelLeft = temp;
//            // Add the new panelLeft to the GUI
//            gui.add(panelLeft);
//            configLeft(panelLeft);
//            break;
//        case MainPanelIndex::RIGHT:
//            // Remove the old panelLeft from the GUI
//            gui.remove(panelRight);
//            // Assign temp to panelLeft
//            panelRight = temp;
//            // Add the new panelLeft to the GUI
//            gui.add(panelRight);
//            configRight(panelRight);
//            break;
//        case MainPanelIndex::MIDDLE:
//            // Remove the old panelLeft from the GUI
//            gui.remove(panelMiddle);
//            // Assign temp to panelLeft
//            panelMiddle = temp;
//            // Add the new panelLeft to the GUI
//            gui.add(panelMiddle);
//            configMiddle(panelMiddle);
//            break;
//    }
//}

void UIManager::lockGui(std::string message)
{
    isGuiLocked = true;
    if(mainPanel != nullptr)
    {
        mainPanel->setEnabled(false);
    }
    panelMask->setVisible(true);
    panelMask->get<tgui::Label>("Massage")->setText(message);
    panelMask->moveToFront();
}


void UIManager::unlockGui()
{
    isGuiLocked = false;
    if(mainPanel != nullptr)
    {
        mainPanel->setEnabled(true);
    }
    panelMask->setVisible(false);
}

tgui::Panel::Ptr UIManager::recruitPanel()
{
    if(!game->isWorldCreatedFlag() || game->isNextRoundThreadRunningFlag())
    {
        return nullptr;
    }

    std::vector<std::shared_ptr<Tavern>> sharedTaverns = game->getCity()->getTaverns();
    std::map<unsigned int, std::weak_ptr<MagicSchool>> magicSchoolInTavern;
    std::vector<std::weak_ptr<Tavern>> taverns;

    for (const auto& sharedTavern : sharedTaverns)
    {
        taverns.emplace_back(sharedTavern);
    }
    sharedTaverns.clear();

    std::vector<std::shared_ptr<MagicSchool>> sharedMagicSchools = game->getCity()->getMagicSchools();


    for(auto& magicSchool : sharedMagicSchools)
    {
        std::vector<std::shared_ptr<Agent>> sharedTeachers = magicSchool->getTeachers();
        for(auto& teacher : sharedTeachers)
        {
            std::weak_ptr<Tavern> tavern = std::dynamic_pointer_cast<Tavern>(teacher->getCurrentInstance());
            if(tavern.lock() != nullptr)
            {
                magicSchoolInTavern[tavern.lock()->getID()] = magicSchool;
            }
        }
    }

    sharedMagicSchools.clear();


    tgui::Panel::Ptr recruitPanel = tgui::Panel::create();
    recruitPanel->setWidgetName("RecruitPanel");

    tgui::Panel::Ptr instancePanel = tgui::Panel::create();
    instancePanel->setSize("100%", "100%");
    instancePanel->setPosition(0, 0);
    recruitPanel->add(instancePanel);

    tgui::Panel::Ptr viewPanel = tgui::Panel::create();
    viewPanel->setSize("100%", "90%");
    viewPanel->setPosition(0, 0);
    instancePanel->add(viewPanel);

    ListPanel::Ptr listOfTaverns = ListPanel::create();
    listOfTaverns->setSize("50%", "100%");
    listOfTaverns->setPosition("0%", "0%");
    viewPanel->add(listOfTaverns);

    InfoPanel::Ptr tavernInfo = InfoPanel::create(3, 0, 0);
    tavernInfo->setSize("50%", "100%");
    tavernInfo->setPosition("50%", "0%");
    viewPanel->add(tavernInfo);
    tavernInfo->setTitle("Tavern Info");

    listOfTaverns->setTitle("Taverns");

    for(auto& tavern : taverns)
    {
        std::string item = "Name: " + tavern.lock()->getName();

        if(magicSchoolInTavern.find(tavern.lock()->getID()) != magicSchoolInTavern.end())
        {
            item += " (" + magicSchoolInTavern[tavern.lock()->getID()].lock()->getName() + ")";
        }

        listOfTaverns->addItem(tavern ,item);
    }

    std::function<void(std::weak_ptr<GameObject>)> tavernCallback = [tavernInfo](std::weak_ptr<GameObject> object)
    {
        auto tavern = std::dynamic_pointer_cast<Tavern>(object.lock());
        if(tavern == nullptr)
        {
            return;
        }
        tavernInfo->setLabel(0, "ID: " + std::to_string(tavern->getID()));
        tavernInfo->setLabel(1, "Name: " + tavern->getName());
        tavernInfo->setLabel(2, "Description: " + tavern->getDescription());
    };

    listOfTaverns->addFunctionOnSelected(tavernCallback);

    tgui::Panel::Ptr instanceBottomPanel = tgui::Panel::create();
    instanceBottomPanel->setSize("100%", "10%");
    instanceBottomPanel->setPosition(0, "90%");
    instancePanel->add(instanceBottomPanel);

    auto resousePanel = resorrcePanel();
    instanceBottomPanel->add(resousePanel);

    tgui::Button::Ptr toInToTavernButton = tgui::Button::create();
    toInToTavernButton->setSize("20%", "100%");
    toInToTavernButton->setAutoLayout(tgui::AutoLayout::Right);
    toInToTavernButton->setText("Enter Tavern");
    instanceBottomPanel->add(toInToTavernButton);

    tgui::Panel::Ptr AgentPanel = tgui::Panel::create();
    AgentPanel->setSize("100%", "100%");
    AgentPanel->setPosition(0, 0);
    recruitPanel->add(AgentPanel);
    AgentPanel->setVisible(false);

    tgui::Panel::Ptr AgentViewPanel = tgui::Panel::create();
    AgentViewPanel->setSize("100%", "90%");
    AgentViewPanel->setPosition(0, 0);
    AgentPanel->add(AgentViewPanel);

    ListPanel::Ptr listOfAgents = ListPanel::create();
    listOfAgents->setSize("50%", "100%");
    listOfAgents->setPosition("0%", "0%");
    AgentViewPanel->add(listOfAgents);
    listOfAgents->setTitle("Agents");

    InfoPanel::Ptr agentInfo = InfoPanel::create(6, 0, 0);
    agentInfo->setSize("50%", "100%");
    agentInfo->setPosition("50%", "0%");
    AgentViewPanel->add(agentInfo);
    agentInfo->setTitle("Agent Info");

    std::function<void(std::weak_ptr<GameObject>)> agentCallback = [agentInfo](std::weak_ptr<GameObject> object)
    {
        auto agent = std::dynamic_pointer_cast<Agent>(object.lock());
        if(agent == nullptr)
        {
            return;
        }
        agentInfo->setLabel(0, "ID: " + std::to_string(agent->getID()));
        agentInfo->setLabel(1, "Name: " + agent->getName());
        agentInfo->setLabel(2, "Current Instance: " + agent->getCurrentInstance()->getName());
        agentInfo->setLabel(3, "Main Profession: " + professionToString(agent->getMainProfession()));
        agentInfo->setLabel(4, "Description: " + agent->getDescription());
        agentInfo->setLabel(5, "Talent: " + std::to_string(agent->getMagicAbility()->getTalent()));
    };

    listOfAgents->addFunctionOnSelected(agentCallback);

    tgui::Panel::Ptr agentBottomPanel = tgui::Panel::create();
    agentBottomPanel->setSize("100%", "10%");
    agentBottomPanel->setPosition(0, "90%");
    AgentPanel->add(agentBottomPanel);

    resousePanel = resorrcePanel();
    agentBottomPanel->add(resousePanel);

    std::function<void()> toInToTavernButtonCallback = [AgentPanel, instancePanel, listOfTaverns, listOfAgents]()
    {
        std::shared_ptr<Tavern> tavern = std::dynamic_pointer_cast<Tavern>(listOfTaverns->getSelected().lock());
        if(tavern == nullptr)
        {
            return;
        }

        for(auto& agent : tavern->getBusyAgents())
        {
            std::string text = "Name: " + agent->getName();

            listOfAgents->addItem(agent, text);
        }

        AgentPanel->setVisible(true);
        instancePanel->setVisible(false);
    };

    tgui::Button::Ptr recruitButton = tgui::Button::create();
    recruitButton->setSize("20%", "100%");
    recruitButton->setAutoLayout(tgui::AutoLayout::Right);
    recruitButton->setText("Recruit");
    agentBottomPanel->add(recruitButton);

    tgui::Button::Ptr toTaskMenuButton = tgui::Button::create();
    toTaskMenuButton->setSize("20%", "100%");
    toTaskMenuButton->setAutoLayout(tgui::AutoLayout::Rightmost);
    toTaskMenuButton->setText("Go to Squer!");
    agentBottomPanel->add(toTaskMenuButton);

    std::function<void()> recruitButtonCallback = [this, listOfAgents, agentBottomPanel]()
    {
        std::weak_ptr<PlayerMagicSchool> playerMagicSchool = std::dynamic_pointer_cast<PlayerMagicSchool>(game->getPlayerMagicSchool());
        std::weak_ptr<Agent> newStudent = std::dynamic_pointer_cast<Agent>(listOfAgents->getSelected().lock());
        if(newStudent.lock() == nullptr)
        {
            return;
        }
        if(playerMagicSchool.lock()->getResources()[static_cast<int>(GameLoudObject::ResourceType::Gold)] < 10)
        {
            std::string text = "To lite Gold!";
            this->massageWin(text);
            return;
        }
        playerMagicSchool.lock()->addStudent(newStudent.lock());
        playerMagicSchool.lock()->addResource(static_cast<int>(GameLoudObject::ResourceType::Gold), -10);

        agentBottomPanel->remove(agentBottomPanel->get<tgui::Panel>("ResourcePanel"));
        auto resousePanel = resorrcePanel();
        agentBottomPanel->add(resousePanel);
        listOfAgents->removeItem(newStudent);
    };

    std::function<void()> toAcceptTaskButtonCallback = [this, instancePanel, AgentPanel]()
    {
        gui.remove(mainPanel);
        mainPanel = taskAcceptPanel();
        currentMainPanelIndex = MainPanelIndex::AcceptTask;
        if(mainPanel != nullptr)
        {
            gui.add(mainPanel);
        }
    };

    toInToTavernButton->onClick(toInToTavernButtonCallback);
    recruitButton->onClick(recruitButtonCallback);
    toTaskMenuButton->onClick(toAcceptTaskButtonCallback);

    return recruitPanel;
}

tgui::Panel::Ptr UIManager::taskAcceptPanel()
{
    if(!game->isWorldCreatedFlag() || game->isNextRoundThreadRunningFlag())
    {
        return nullptr;
    }

    std::vector<std::shared_ptr<Square>> sharedTaverns = game->getCity()->getSquares();
    std::vector<std::weak_ptr<Square>> squers;

    for (const auto& sharedTavern : sharedTaverns)
    {
        squers.emplace_back(sharedTavern);
    }
    sharedTaverns.clear();


    tgui::Panel::Ptr taskPanel = tgui::Panel::create();
    taskPanel->setWidgetName("TaskPanel");

    tgui::Panel::Ptr instancePanel = tgui::Panel::create();
    instancePanel->setSize("100%", "100%");
    instancePanel->setPosition(0, 0);
    taskPanel->add(instancePanel);

    tgui::Panel::Ptr viewPanel = tgui::Panel::create();
    viewPanel->setSize("100%", "90%");
    viewPanel->setPosition(0, 0);
    instancePanel->add(viewPanel);

    ListPanel::Ptr listOfSquer = ListPanel::create();
    listOfSquer->setSize("50%", "100%");
    listOfSquer->setPosition("0%", "0%");
    viewPanel->add(listOfSquer);

    InfoPanel::Ptr squerInfo = InfoPanel::create(3, 0, 0);
    squerInfo->setSize("50%", "100%");
    squerInfo->setPosition("50%", "0%");
    viewPanel->add(squerInfo);
    squerInfo->setTitle("Tavern Info");

    listOfSquer->setTitle("Taverns");

    for(auto& squer: squers)
    {
        std::string item = "Name: " + squer.lock()->getName();

        listOfSquer->addItem(squer , item);
    }

    std::function<void(std::weak_ptr<GameObject>)> squerCallback = [squerInfo](std::weak_ptr<GameObject> object)
    {
        auto square = std::dynamic_pointer_cast<Square>(object.lock());
        if(square == nullptr)
        {
            return;
        }
        squerInfo->setLabel(0, "ID: " + std::to_string(square->getID()));
        squerInfo->setLabel(1, "Name: " + square->getName());
        squerInfo->setLabel(2, "Description: " + square->getDescription());
    };

    listOfSquer->addFunctionOnSelected(squerCallback);

    tgui::Panel::Ptr instanceBottomPanel = tgui::Panel::create();
    instanceBottomPanel->setSize("100%", "10%");
    instanceBottomPanel->setPosition(0, "90%");
    instancePanel->add(instanceBottomPanel);

    auto resousePanel = resorrcePanel();
    instanceBottomPanel->add(resousePanel);

    tgui::Button::Ptr toInToTavernButton = tgui::Button::create();
    toInToTavernButton->setSize("20%", "100%");
    toInToTavernButton->setAutoLayout(tgui::AutoLayout::Right);
    toInToTavernButton->setText("Enter Squer");
    instanceBottomPanel->add(toInToTavernButton);

    tgui::Panel::Ptr tasksPanel = tgui::Panel::create();
    tasksPanel->setSize("100%", "100%");
    tasksPanel->setPosition(0, 0);
    taskPanel->add(tasksPanel);
    tasksPanel->setVisible(false);

    tgui::Panel::Ptr taskViewPanel = tgui::Panel::create();
    taskViewPanel->setSize("100%", "90%");
    taskViewPanel->setPosition(0, 0);
    tasksPanel->add(taskViewPanel);

    ListPanel::Ptr listOfTask = ListPanel::create();
    listOfTask->setSize("50%", "100%");
    listOfTask->setPosition("0%", "0%");
    taskViewPanel->add(listOfTask);
    listOfTask->setTitle("Agents");

    InfoPanel::Ptr taskInfo = InfoPanel::create(6, 0, 0);
    taskInfo->setSize("50%", "100%");
    taskInfo->setPosition("50%", "0%");
    taskViewPanel->add(taskInfo);
    taskInfo->setTitle("Agent Info");

    std::function<void(std::weak_ptr<GameObject>)> taskCallback = [taskInfo](std::weak_ptr<GameObject> object)
    {
        auto task = std::dynamic_pointer_cast<Task>(object.lock());
        if(task == nullptr)
        {
            return;
        }
        taskInfo->setLabel(0, "ID: " + std::to_string(task->getID()));
        taskInfo->setLabel(1, "Name: " + task->getName());
        taskInfo->setLabel(2, "Requarird spell: " + task->getRequiredSpell().lock()->getName());
        taskInfo->setLabel(3, "level of spell: " + std::to_string(task->getDifficulty()));
        taskInfo->setLabel(4, "Gold Reword: " + std::to_string(task->getReward()[static_cast<int>(GameLoudObject::ResourceType::Gold)]));
        taskInfo->setLabel(5, "Magic Stone Reword: " + std::to_string(task->getReward()[static_cast<int>(GameLoudObject::ResourceType::MagicStone)]));
    };

    listOfTask->addFunctionOnSelected(taskCallback);

    tgui::Panel::Ptr taskBottomPanel = tgui::Panel::create();
    taskBottomPanel->setSize("100%", "10%");
    taskBottomPanel->setPosition(0, "90%");
    tasksPanel->add(taskBottomPanel);

    resousePanel = resorrcePanel();
    taskBottomPanel->add(resousePanel);

    tgui::Button::Ptr acceptButton = tgui::Button::create();
    acceptButton->setSize("20%", "100%");
    acceptButton->setAutoLayout(tgui::AutoLayout::Right);
    acceptButton->setText("Accept Task");
    taskBottomPanel->add(acceptButton);

    tgui::Button::Ptr toTaskMenuButton = tgui::Button::create();
    toTaskMenuButton->setSize("20%", "100%");
    toTaskMenuButton->setAutoLayout(tgui::AutoLayout::Rightmost);
    toTaskMenuButton->setText("Go to Squer!");
    taskBottomPanel->add(toTaskMenuButton);

    std::function<void()> acceptButtonCallback = [this, listOfTask, taskBottomPanel]()
    {
        std::weak_ptr<PlayerMagicSchool> playerMagicSchool = std::dynamic_pointer_cast<PlayerMagicSchool>(game->getPlayerMagicSchool());
        std::weak_ptr<Task> newTask = std::dynamic_pointer_cast<Task>(listOfTask->getSelected().lock());
        if(newTask.lock() == nullptr)
        {
            return;
        }

        bool canAccept = false;

        // Check if player can accept the task
        for(auto& student : playerMagicSchool.lock()->getStudents())
        {
            if(student->getMagicAbility()->getSpellProficiency(newTask.lock()->getRequiredSpell()) > newTask.lock()->getDifficulty())
            {
                canAccept = true;
                break;
            }
        }

        playerMagicSchool.lock()->addTask(newTask.lock());
        listOfTask->removeItem(newTask);
    };

    std::function<void()> toDistributeTaskButtonCallback = [this, instancePanel, tasksPanel]()
    {
        gui.remove(mainPanel);
        mainPanel = taskDistributionPanel();
        currentMainPanelIndex = MainPanelIndex::Distribut;
        if(mainPanel != nullptr)
        {
            gui.add(mainPanel);
        }
    };

    std::function<void()> toInToSquereButtonCallback = [tasksPanel, instancePanel, listOfSquer, listOfTask, toDistributeTaskButtonCallback]()
    {
        std::shared_ptr<Square> square = std::dynamic_pointer_cast<Square>(listOfSquer->getSelected().lock());
        if(square == nullptr)
        {
            return;
        }

        std::vector<std::weak_ptr<Task>> tasks = square->getTasks();
        std::sort(tasks.begin(), tasks.end(), [](std::weak_ptr<Task> a, std::weak_ptr<Task> b)
        { return a.lock()->getDifficulty() < b.lock()->getDifficulty(); });

        if(tasks.size() == 0)
        {
            toDistributeTaskButtonCallback();
            return;
        }

        for(auto& task : tasks)
        {
            if(task.lock() == nullptr)
            {
                continue;
            }
            std::string text = "Name: " + task.lock()->getName() + " Spell: " + task.lock()->getRequiredSpell().lock()->getName() + " Proficiency: " + std::to_string(task.lock()->getDifficulty());

            listOfTask->addItem(task, text);
        }

        tasksPanel->setVisible(true);
        instancePanel->setVisible(false);
    };

    toInToTavernButton->onClick(toInToSquereButtonCallback);
    acceptButton->onClick(acceptButtonCallback);
    toTaskMenuButton->onClick(toDistributeTaskButtonCallback);

    return taskPanel;
}

tgui::Panel::Ptr UIManager::resorrcePanel()
{
    tgui::Panel::Ptr resourcePanel = tgui::Panel::create();
    resourcePanel->setSize("50%", "100%");
    resourcePanel->setPosition("0%", "0%");
    resourcePanel->setWidgetName("ResourcePanel");

    std::vector<unsigned int> resources = std::dynamic_pointer_cast<PlayerMagicSchool>(
            game->getPlayerMagicSchool())->getResources();

    tgui::Label::Ptr goldLabel = tgui::Label::create();
    goldLabel->setText("Gold: " + std::to_string(resources[static_cast<int>(GameLoudObject::ResourceType::Gold)]));
    goldLabel->setAutoSize(true);
    goldLabel->setAutoLayout(tgui::AutoLayout::Left);
    resourcePanel->add(goldLabel);

    tgui::Label::Ptr mSLabel = tgui::Label::create();
    mSLabel->setText("MS: " + std::to_string(resources[static_cast<int>(GameLoudObject::ResourceType::MagicStone)]));
    mSLabel->setAutoSize(true);
    mSLabel->setAutoLayout(tgui::AutoLayout::Left);
    resourcePanel->add(mSLabel);

    tgui::Label::Ptr stuLabel = tgui::Label::create();
    stuLabel->setText("Students: " + std::to_string(std::dynamic_pointer_cast<PlayerMagicSchool>(
            game->getPlayerMagicSchool())->getStudents().size()));
    stuLabel->setAutoSize(true);
    stuLabel->setAutoLayout(tgui::AutoLayout::Left);
    resourcePanel->add(stuLabel);

    return resourcePanel;
}

tgui::Panel::Ptr UIManager::taskDistributionPanel()
{
    std::weak_ptr<PlayerMagicSchool> playerMagicSchool = std::dynamic_pointer_cast<PlayerMagicSchool>(game->getPlayerMagicSchool());
    std::vector<std::shared_ptr<Task>> tasks = playerMagicSchool.lock()->getTasks();

    tgui::Panel::Ptr taskDistributionPanel = tgui::Panel::create();
    taskDistributionPanel->setWidgetName("TaskDistributionPanel");

    tgui::Panel::Ptr taskAccepetedPanel = tgui::Panel::create();
    taskAccepetedPanel->setSize("100%", "100%");
    taskAccepetedPanel->setPosition(0, 0);
    taskDistributionPanel->add(taskAccepetedPanel);

    tgui::Panel::Ptr viewTas = tgui::Panel::create();
    viewTas->setSize("100%", "90%");
    viewTas->setPosition(0, 0);
    taskAccepetedPanel->add(viewTas);

    ListPanel::Ptr listOfTask = ListPanel::create();
    listOfTask->setSize("50%", "100%");
    listOfTask->setPosition("0%", "0%");
    viewTas->add(listOfTask);

    // add task to listBox
    for(auto& task : tasks)
    {
        std::string item = "Name: " + task->getName() + " Spell: " + task->getRequiredSpell().lock()->getName() + " Proficiency: " + std::to_string(task->getDifficulty());

        listOfTask->addItem(task , item);
    }

    InfoPanel::Ptr taskInfo = InfoPanel::create(6, 0, 0);
    taskInfo->setSize("50%", "100%");
    taskInfo->setPosition("50%", "0%");
    taskAccepetedPanel->add(taskInfo);
    taskInfo->setTitle("Agent Info");

    std::function<void(std::weak_ptr<GameObject>)> taskCallback = [taskInfo](std::weak_ptr<GameObject> object)
    {
        auto task = std::dynamic_pointer_cast<Task>(object.lock());
        if(task == nullptr)
        {
            return;
        }
        taskInfo->setLabel(0, "ID: " + std::to_string(task->getID()));
        taskInfo->setLabel(1, "Name: " + task->getName());
        taskInfo->setLabel(2, "Requarird spell: " + task->getRequiredSpell().lock()->getName());
        taskInfo->setLabel(3, "level of spell: " + std::to_string(task->getDifficulty()));
        taskInfo->setLabel(4, "Gold Reword: " + std::to_string(task->getReward()[static_cast<int>(GameLoudObject::ResourceType::Gold)]));
        taskInfo->setLabel(5, "Magic Stone Reword: " + std::to_string(task->getReward()[static_cast<int>(GameLoudObject::ResourceType::MagicStone)]));
    };

    listOfTask->addFunctionOnSelected(taskCallback);

    tgui::Panel::Ptr resourcePanel = resorrcePanel();

    tgui::Panel::Ptr taskBottomPanel = tgui::Panel::create();
    taskBottomPanel->setSize("100%", "10%");
    taskBottomPanel->setPosition(0, "90%");
    taskAccepetedPanel->add(taskBottomPanel);

    taskBottomPanel->add(resourcePanel);

    tgui::Button::Ptr toDistributeTaskButton = tgui::Button::create();
    toDistributeTaskButton->setSize("20%", "100%");
    toDistributeTaskButton->setAutoLayout(tgui::AutoLayout::Right);
    toDistributeTaskButton->setText("Distribute Task");
    taskBottomPanel->add(toDistributeTaskButton);

    tgui::Button::Ptr toNextTurnButton = tgui::Button::create();
    toNextTurnButton->setSize("20%", "100%");
    toNextTurnButton->setAutoLayout(tgui::AutoLayout::Rightmost);
    toNextTurnButton->setText("Next Turn");
    taskBottomPanel->add(toNextTurnButton);



    tgui::Panel::Ptr AgentPanel = tgui::Panel::create();
    AgentPanel->setSize("100%", "100%");
    AgentPanel->setPosition(0, 0);
    taskDistributionPanel->add(AgentPanel);
    AgentPanel->setVisible(false);

    tgui::Panel::Ptr AgentViewPanel = tgui::Panel::create();
    AgentViewPanel->setSize("100%", "90%");
    AgentViewPanel->setPosition(0, 0);
    AgentPanel->add(AgentViewPanel);

    ListPanel::Ptr listOfAgents = ListPanel::create();
    listOfAgents->setSize("50%", "100%");
    listOfAgents->setPosition("0%", "0%");
    AgentViewPanel->add(listOfAgents);
    listOfAgents->setTitle("Agents");



    InfoPanel::Ptr agentInfo = InfoPanel::create(8, 0, 0);
    agentInfo->setSize("50%", "100%");
    agentInfo->setPosition("50%", "0%");
    AgentViewPanel->add(agentInfo);
    agentInfo->setTitle("Agent Info");

    std::function<void(std::weak_ptr<GameObject>)> agentCallback = [agentInfo](std::weak_ptr<GameObject> object)
    {
        auto agent = std::dynamic_pointer_cast<Agent>(object.lock());
        if(agent == nullptr)
        {
            return;
        }
        agentInfo->setLabel(0, "ID: " + std::to_string(agent->getID()));
        agentInfo->setLabel(1, "Name: " + agent->getName());
        agentInfo->setLabel(2, "Current Instance: " + agent->getCurrentInstance()->getName());
        agentInfo->setLabel(3, "Main Profession: " + professionToString(agent->getMainProfession()));
        agentInfo->setLabel(4, "Description: " + agent->getDescription());
        agentInfo->setLabel(5, "Talent: " + std::to_string(agent->getMagicAbility()->getTalent()));
        agentInfo->setLabel(6, "Spell: " + agent->getMagicAbility()->getLearnedSpells()[0].lock()->getName());
        agentInfo->setLabel(7, "Profisency: " + std::to_string(agent->getMagicAbility()->getSpellProficiency(agent->getMagicAbility()->getLearnedSpells()[0])));
    };

    listOfAgents->addFunctionOnSelected(agentCallback);

    tgui::Panel::Ptr agentBottomPanel = tgui::Panel::create();
    agentBottomPanel->setSize("100%", "10%");
    agentBottomPanel->setPosition(0, "90%");
    AgentPanel->add(agentBottomPanel);

    resourcePanel = resorrcePanel();
    agentBottomPanel->add(resourcePanel);

    tgui::Button::Ptr assineButton = tgui::Button::create();
    assineButton->setSize("20%", "100%");
    assineButton->setAutoLayout(tgui::AutoLayout::Right);
    assineButton->setText("Assine Task");
    agentBottomPanel->add(assineButton);

    tgui::Button::Ptr toTaskMenuButton = tgui::Button::create();
    toTaskMenuButton->setSize("20%", "100%");
    toTaskMenuButton->setAutoLayout(tgui::AutoLayout::Rightmost);
    toTaskMenuButton->setText("back to tasks");
    agentBottomPanel->add(toTaskMenuButton);

    std::function<void()> toDistributeTaskButtonCallback = [this, listOfAgents, AgentPanel, listOfTask, taskAccepetedPanel, playerMagicSchool]()
    {
        listOfAgents->clearItems();
        std::vector<std::shared_ptr<Agent>> students = playerMagicSchool.lock()->getStudents();
        std::weak_ptr<Task> task = std::dynamic_pointer_cast<Task>(listOfTask->getSelected().lock());
        std::map<std::shared_ptr<Agent>, std::shared_ptr<Task>> agentsWithTasks = playerMagicSchool.lock()->getTaskAssignment();

        if(task.lock() == nullptr)
        {
            return;
        }

        for(auto& student : students)
        {
            if(agentsWithTasks.find(student) != agentsWithTasks.end())
            {
                continue;
            } else if(student->getMagicAbility()->getSpellProficiency(task.lock()->getRequiredSpell()) > task.lock()->getDifficulty())
            {
                std::string text = "Name: " + student->getName();
                listOfAgents->addItem(student, text);
            }
        }

        AgentPanel->setVisible(true);
        taskAccepetedPanel->setVisible(false);
    };

    std::function<void()> assineButtonCallback = [this, listOfAgents, AgentPanel, listOfTask, playerMagicSchool, taskAccepetedPanel]()
    {
        std::weak_ptr<PlayerMagicSchool> playerMagicSchool = std::dynamic_pointer_cast<PlayerMagicSchool>(game->getPlayerMagicSchool());
        std::weak_ptr<Agent> newStudent = std::dynamic_pointer_cast<Agent>(listOfAgents->getSelected().lock());
        std::weak_ptr<Task> task = std::dynamic_pointer_cast<Task>(listOfTask->getSelected().lock());

        if(newStudent.lock() == nullptr || task.lock() == nullptr)
        {
            return;
        }
        task.lock()->acceptTask(newStudent.lock());
        playerMagicSchool.lock()->assignTask(newStudent.lock(), task.lock());

        listOfTask->removeItem(task);

        AgentPanel->setVisible(false);
        taskAccepetedPanel->setVisible(true);
    };

    std::function<void()> toNextTurn = [this]()
    {
        gui.remove(mainPanel);
        mainPanel = recruitPanel();
        currentMainPanelIndex = MainPanelIndex::Recruit;
        game->NextRound();
        if(mainPanel != nullptr)
        {
            gui.add(mainPanel);
        }
    };

    std::function<void()> backToTaskButtonCallback = [taskAccepetedPanel, AgentPanel]()
    {
        AgentPanel->setVisible(false);
        taskAccepetedPanel->setVisible(true);
    };

    toDistributeTaskButton->onClick(toDistributeTaskButtonCallback);
    assineButton->onClick(assineButtonCallback);
    toNextTurnButton->onClick(toNextTurn);
    toTaskMenuButton->onClick(backToTaskButtonCallback);

    if(tasks.size() == 0)
    {
        toNextTurn();
        return nullptr;
    }

    return taskDistributionPanel;
}

tgui::Panel::Ptr UIManager::massageWin(std::string &message)
{


    tgui::Panel::Ptr massageWin = tgui::Panel::create();
    massageWin->setOrigin(0.5f, 0.5f);
    massageWin->setSize("80%", "50%");
    massageWin->setPosition("50%", "50%");
    massageWin->setWidgetName("messageWin");
    massageWin->getRenderer()->setBorders(2);

    tgui::Label::Ptr massage = tgui::Label::create(message);
    massage->setOrigin(0.5f, 0.5f);
    massage->setPosition("50%", "50%");
    massage->setTextSize(20);
    massageWin->add(massage);

    tgui::Button::Ptr okButton = tgui::Button::create();
    okButton->setOrigin(0.5f, 0.5f);
    okButton->setPosition("50%", "85%");
    okButton->setSize("20%", "10%");
    okButton->setTextSize(20);
    okButton->setText("OK");
    massageWin->add(okButton);

    std::function<void()> okButtonCallback = [this, massageWin](){
        this->mainPanel->remove(massageWin);
    };

    okButton->onClick(okButtonCallback);

    return massageWin;
}

