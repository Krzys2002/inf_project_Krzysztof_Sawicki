//
// Created by Krzysztof Sawicki on 19/05/2024.
//

#ifndef INF_PROJECT_INFOPANEL_H
#define INF_PROJECT_INFOPANEL_H

#include <TGUI/TGUI.hpp>
#include "ListPanel.h"

class InfoPanel : public tgui::ScrollablePanel
{
    tgui::Label::Ptr titleLabel;
    std::vector<tgui::Label::Ptr> labels;
    std::vector<ListPanel::Ptr> listBoxes;
    std::vector<tgui::Button::Ptr> buttons;

public:
    typedef std::shared_ptr<InfoPanel> Ptr;

    InfoPanel(unsigned int numberOfLabels,unsigned int numberOfListBoxes, unsigned int numberOfButtons);

    void setTitle(const std::string& title);
    void setLabel(unsigned int index, const std::string& text);
    void setListBox(unsigned int index, const std::string& title);
    void addItemToListBox(unsigned int index, std::shared_ptr<GameObject> item);
    void setButton(unsigned int index, const std::string& text);
    void setButtonCallback(unsigned int index, const std::function<void()>& callback);

    static Ptr create(unsigned int numberOfLabels, unsigned int numberOfListBoxes, unsigned int numberOfButtons);
};


#endif //INF_PROJECT_INFOPANEL_H
