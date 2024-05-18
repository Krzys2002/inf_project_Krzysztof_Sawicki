//
// Created by Krzysztof Sawicki on 18/05/2024.
//

#include "../Headers/ListItem.h"

ListItem::ListItem(const std::string& text, const std::vector<std::function<void()>>& buttonCallbacks, const std::function<void()>& labelCallback)
{
    std::shared_ptr<CustomClickableWidget> label = std::make_shared<CustomClickableWidget>();
    label->setSize({"70%", "100%"});
    label->setNormalColor(tgui::Color::White);
    label->setHoverColor(tgui::Color::Green);
    this->add(label);
    auto labelText = tgui::Label::create(text);
    labelText->setTextSize(15);
    labelText->setPosition({"5%", "5%"});
    this->add(labelText);

    for (size_t i = 0; i < buttonCallbacks.size(); ++i)
    {
        auto button = tgui::Button::create("Button " + std::to_string(i + 1));
        button->setSize({"15%", "100%"});
        button->setPosition((70.f + 15.f * i) / 100.f, 0.f);
        button->onPress(buttonCallbacks[i]);
        this->add(button);
    }
}
