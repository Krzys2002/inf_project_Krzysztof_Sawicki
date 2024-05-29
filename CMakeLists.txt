cmake_minimum_required(VERSION 3.28)
project(inf_project)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
find_package(TGUI 1.2.0 REQUIRED)

add_executable(inf_project main.cpp
        Source/GameObject.cpp
        Headers/GameObject.h
        Source/TimeSpace.cpp
        Headers/TimeSpace.h
        Source/RandomNumberGenerator.cpp
        Source/Instance.cpp
        Headers/Instance.h
        Source/Agent.cpp
        Headers/Agent.h
        Source/GameNameHolder.cpp
        Headers/GameNameHolder.h
        UI/Source/ListItem.cpp
        UI/Headers/ListItem.h
        UI/Source/CustomClickableWidget.cpp
        UI/Headers/CustomClickableWidget.h
        Source/Game.cpp
        Headers/Game.h
        UI/Source/UIManager.cpp
        UI/Headers/UIManager.h
        UI/Source/ListPanel.cpp
        UI/Headers/ListPanel.h
        UI/Source/InfoPanel.cpp
        UI/Headers/InfoPanel.h
        Source/City.cpp
        Headers/City.h
        Source/Tavern.cpp
        Headers/Tavern.h
)

target_link_libraries(inf_project PRIVATE sfml-graphics sfml-audio TGUI::TGUI)
