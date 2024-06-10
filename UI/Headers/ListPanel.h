//
// Created by Krzysztof Sawicki on 19/05/2024.
//

#ifndef INF_PROJECT_LISTPANEL_H
#define INF_PROJECT_LISTPANEL_H

#include <TGUI/TGUI.hpp>
#include "../../Headers/GameObject.h"

class ListPanel : public tgui::ScrollablePanel
{
    tgui::ListBox::Ptr listBox;
    tgui::Label::Ptr Title;
    std::vector<std::weak_ptr<GameObject>> items;
    int selected = -1;
    std::string title;

public:
    typedef std::shared_ptr<ListPanel> Ptr;

    ListPanel();

    void addItem(std::weak_ptr<GameObject> item);
    void addItem(std::weak_ptr<GameObject> item, const std::string& text);
    void removeItem(std::weak_ptr<GameObject> item);
    void removeItem(int index);
    void setTitle(const std::string& title);
    void setTitleSize(unsigned int size);
    void setTitleBordSize(tgui::Layout size);
    void clearItems();

    std::weak_ptr<GameObject> getSelected();

    void addFunctionOnSelected(std::function<void(std::weak_ptr<GameObject>)> function);

    static Ptr create();
};


#endif //INF_PROJECT_LISTPANEL_H
