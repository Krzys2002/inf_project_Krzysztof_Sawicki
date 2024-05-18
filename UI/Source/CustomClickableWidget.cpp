//
// Created by Krzysztof Sawicki on 18/05/2024.
//

#include "../Headers/CustomClickableWidget.h"

CustomClickableWidget::CustomClickableWidget()
{
    this->getRenderer()->setBackgroundColor(tgui::Color::White);
    this->onMouseEnter([this](){ this->getRenderer()->setBackgroundColor(m_hoverColor); });
    this->onMouseLeave([this](){ this->getRenderer()->setBackgroundColor(m_normalColor); });
}

void CustomClickableWidget::setHoverColor(const tgui::Color& color)
{
    m_hoverColor = color;
}

void CustomClickableWidget::setNormalColor(const tgui::Color& color)
{
    m_normalColor = color;
    this->getRenderer()->setBackgroundColor(color);
}