//
// Created by Krzysztof Sawicki on 18/05/2024.
//

#ifndef CUSTOMCLICKABLEWIDGET_HPP
#define CUSTOMCLICKABLEWIDGET_HPP

#include <TGUI/TGUI.hpp>

class CustomClickableWidget : public tgui::Panel
{
public:
    typedef std::shared_ptr<CustomClickableWidget> Ptr;

    CustomClickableWidget();

    void setHoverColor(const tgui::Color& color);
    void setNormalColor(const tgui::Color& color);

private:
    tgui::Color m_hoverColor;
    tgui::Color m_normalColor;
};

#endif // CUSTOMCLICKABLEWIDGET_HPP
