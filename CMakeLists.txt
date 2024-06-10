cmake_minimum_required(VERSION 3.28)
project(inf_project)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
find_package(TGUI 1.2.0 REQUIRED)
find_package(nlohmann_json 3.2.0 REQUIRED)

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
        Source/Square.cpp
        Headers/Square.h
        Source/Profession.cpp
        Headers/Profession.h
        Source/WorldSettings.cpp
        Headers/WorldSettings.h
        Source/Task.cpp
        Headers/Task.h
        Source/MagicAbility.cpp
        Headers/MagicAbility.h
        Source/Spell.cpp
        Headers/Spell.h
        Source/MagicSchool.cpp
        Headers/MagicSchool.h
        Source/Teacher.cpp
        Headers/Teacher.h
        Source/PlayerMagicSchool.cpp
        Headers/PlayerMagicSchool.h
        Source/GameLoudObjects.cpp
        Headers/GameLoudObjects.h
)

target_link_libraries(inf_project PRIVATE sfml-graphics sfml-audio TGUI::TGUI nlohmann_json::nlohmann_json)
