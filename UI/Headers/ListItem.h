//
// Created by Krzysztof Sawicki on 18/05/2024.
//

#ifndef LISTITEM_HPP
#define LISTITEM_HPP

#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include "CustomClickableWidget.h"

class ListItem : public tgui::Panel
{
public:
    typedef std::shared_ptr<ListItem> Ptr;

    ListItem(const std::string& text, const std::vector<std::function<void()>>& buttonCallbacks, const std::function<void()>& labelCallback);

    static Ptr create(const std::string& text, const std::vector<std::function<void()>>& buttonCallbacks, const std::function<void()>& labelCallback)
    {
        return std::make_shared<ListItem>(text, buttonCallbacks, labelCallback);
    }
};

#endif // LISTITEM_HPP
