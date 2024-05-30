//
// Created by Krzysztof Sawicki on 30/05/2024.
//

#include "../Headers/WorldSettings.h"


WorldSettings::WorldSettings(unsigned int seed, unsigned int cityPopulation, float cityPopulationModifier, unsigned int tavernCount, unsigned int tavernPopulation, float tavernPopulationModifier, float tavernCountModifier, unsigned int squareCount, unsigned int squarePopulation, float squarePopulationModifier, float squareCountModifier)
{
    this->seed = seed;
    this->cityPopulation = cityPopulation;
    this->cityPopulationModifier = cityPopulationModifier;
    this->tavernCount = tavernCount;
    this->tavernPopulation = tavernPopulation;
    this->tavernPopulationModifier = tavernPopulationModifier;
    this->tavernCountModifier = tavernCountModifier;
    this->squareCount = squareCount;
    this->squarePopulation = squarePopulation;
    this->squarePopulationModifier = squarePopulationModifier;
    this->squareCountModifier = squareCountModifier;
}

WorldSettings::~WorldSettings()
{
    // Destructor
}

void WorldSettings::setSeed(unsigned int seed)
{
    this->seed = seed;
}

void WorldSettings::setCityPopulation(unsigned int cityPopulation)
{
    this->cityPopulation = cityPopulation;
}

void WorldSettings::setCityPopulationModifier(float cityPopulationModifier)
{
    this->cityPopulationModifier = cityPopulationModifier;
}

void WorldSettings::setTavernCount(unsigned int tavernCount)
{
    this->tavernCount = tavernCount;
}

void WorldSettings::setTavernPopulation(unsigned int tavernPopulation)
{
    this->tavernPopulation = tavernPopulation;
}

void WorldSettings::setTavernPopulationModifier(float tavernPopulationModifier)
{
    this->tavernPopulationModifier = tavernPopulationModifier;
}

void WorldSettings::setTavernCountModifier(float tavernCountModifier)
{
    this->tavernCountModifier = tavernCountModifier;
}

void WorldSettings::setSquareCount(unsigned int squareCount)
{
    this->squareCount = squareCount;
}

void WorldSettings::setSquarePopulation(unsigned int squarePopulation)
{
    this->squarePopulation = squarePopulation;
}

void WorldSettings::setSquarePopulationModifier(float squarePopulationModifier)
{
    this->squarePopulationModifier = squarePopulationModifier;
}

void WorldSettings::setSquareCountModifier(float squareCountModifier)
{
    this->squareCountModifier = squareCountModifier;
}

void WorldSettings::setAberration(float aberration)
{
    this->aberration = aberration;
}

unsigned int WorldSettings::getSeed() const
{
    return seed;
}

unsigned int WorldSettings::getCityPopulation() const
{
    return cityPopulation;
}

float WorldSettings::getCityPopulationModifier() const
{
    return cityPopulationModifier;
}

unsigned int WorldSettings::getTavernCount() const
{
    return tavernCount;
}

unsigned int WorldSettings::getTavernPopulation() const
{
    return tavernPopulation;
}

float WorldSettings::getTavernPopulationModifier() const
{
    return tavernPopulationModifier;
}

float WorldSettings::getTavernCountModifier() const
{
    return tavernCountModifier;
}

unsigned int WorldSettings::getSquareCount() const
{
    return squareCount;
}

unsigned int WorldSettings::getSquarePopulation() const
{
    return squarePopulation;
}

float WorldSettings::getSquarePopulationModifier() const
{
    return squarePopulationModifier;
}

float WorldSettings::getSquareCountModifier() const
{
    return squareCountModifier;
}

float WorldSettings::getAberration() const
{
    return aberration;
}

void WorldSettings::ApplyModifiers()
{
    cityPopulation = static_cast<unsigned int>(cityPopulation * cityPopulationModifier);
    cityPopulationModifier = 1.0f;
    tavernCount = static_cast<unsigned int>(tavernCount * tavernCountModifier);
    tavernCountModifier = 1.0f;
    tavernPopulation = static_cast<unsigned int>(tavernPopulation * tavernPopulationModifier);
    tavernPopulationModifier = 1.0f;
    squareCount = static_cast<unsigned int>(squareCount * squareCountModifier);
    squareCountModifier = 1.0f;
    squarePopulation = static_cast<unsigned int>(squarePopulation * squarePopulationModifier);
    squarePopulationModifier = 1.0f;
}