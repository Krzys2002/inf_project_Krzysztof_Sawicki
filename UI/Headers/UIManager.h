//
// Created by Krzysztof Sawicki on 19/05/2024.
//

#ifndef INF_PROJECT_UIMANAGER_H
#define INF_PROJECT_UIMANAGER_H

#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include "../../Headers/Game.h"
#include "ListPanel.h"
#include "InfoPanel.h"
#include <map>


enum MainPanelIndex
{
    LEFT = 0,
    MIDDLE = 1,
    RIGHT = 2,
};

class Game;

class UIManager
{
    tgui::Gui gui;
    Game* game;
    tgui::ScrollablePanel::Ptr panelLeft;
    tgui::ScrollablePanel::Ptr panelMiddle;
    tgui::ScrollablePanel::Ptr panelRight;
    tgui::Panel::Ptr panelBottom;
    tgui::Panel::Ptr panelTop;
    tgui::Panel::Ptr panelMask;

    //
    void configLeft(tgui::Panel::Ptr panel);
    void configRight(tgui::Panel::Ptr panel);
    void configMiddle(tgui::Panel::Ptr panel);

    void MaskConfig();


public:
    UIManager(Game* game, sf::RenderWindow* window);
    ~UIManager();

    void start();
    void ListGameObjectsOnPanel(MainPanelIndex panelIndex, std::string title, std::vector<std::weak_ptr<GameObject>>& gameObjects);

    void viewObjectInfo(MainPanelIndex indexOfPanel, std::weak_ptr<GameObject> gameObject);
    void viewGameObjectInfo(MainPanelIndex indexOfPanel, std::weak_ptr<GameObject> gameObject);
    void viewAgentInfo(MainPanelIndex indexOfPanel, std::weak_ptr<Agent> agent);
    void viewInstanceInfo(MainPanelIndex indexOfPanel, std::weak_ptr<Instance> instance);

    void setPanelToViewObjectInfoFor(MainPanelIndex formIndex, MainPanelIndex toIndex);

    tgui::Gui& getGui();

    // lock the gui for the next round
    void lockGui();
    // unlock the gui after the next round
    void unlockGui();
};


#endif //INF_PROJECT_UIMANAGER_H
