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
    Recruit = 0,
    AcceptTask = 1,
    Distribut = 2,
};

class Game;
class Agent;
class Instance;

class UIManager
{
    tgui::Gui gui;
    Game* game;
    tgui::Panel::Ptr mainPanel;
//    tgui::ScrollablePanel::Ptr panelLeft;
//    tgui::ScrollablePanel::Ptr panelMiddle;
//    tgui::ScrollablePanel::Ptr panelRight;
//    tgui::Panel::Ptr panelBottom;
//    tgui::Panel::Ptr panelTop;
    tgui::Panel::Ptr panelMask;

    MainPanelIndex currentMainPanelIndex = MainPanelIndex::Recruit;

    bool isGuiLocked = false;

    //
//    void configLeft(tgui::Panel::Ptr panel);
//    void configRight(tgui::Panel::Ptr panel);
//    void configMiddle(tgui::Panel::Ptr panel);

    tgui::Panel::Ptr recruitPanel();
    tgui::Panel::Ptr taskAcceptPanel();
    tgui::Panel::Ptr taskDistributionPanel();

    tgui::Panel::Ptr resorrcePanel();
    tgui::Panel::Ptr massageWin(std::string &message);


public:
    UIManager(Game* game, sf::RenderWindow* window);
    ~UIManager();

    void start();
    void update(sf::Time deltaTime);

    tgui::Gui& getGui();

    // lock the gui for the next round
    void lockGui(std::string message);
    // unlock the gui after the next round
    void unlockGui();
};


#endif //INF_PROJECT_UIMANAGER_H
