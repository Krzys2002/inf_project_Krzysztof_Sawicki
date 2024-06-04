//
// Created by Krzysztof Sawicki on 30/05/2024.
//

#include "../Headers/WorldSettings.h"


unsigned int WorldSettings::seed = 0;
unsigned int WorldSettings::cityPopulation = 10000;
float WorldSettings::cityPopulationModifier = 1.0f;
unsigned int WorldSettings::tavernCount = 15;
unsigned int WorldSettings::tavernPopulation = 20;
float WorldSettings::tavernPopulationModifier = 1.0f;
float WorldSettings::tavernCountModifier = 1.0f;
unsigned int WorldSettings::squareCount = 5;
unsigned int WorldSettings::squarePopulation = 50;
float WorldSettings::squarePopulationModifier = 1.0f;
float WorldSettings::squareCountModifier = 1.0f;
unsigned int WorldSettings::taskExpireTime = 7;
unsigned int WorldSettings::minTalentForSchool = 5;
unsigned int WorldSettings::numberOfEnemiesSchools = 3;

float WorldSettings::aberration = 0.1f;


void WorldSettings::SetSeed(unsigned int seed)
{
    WorldSettings::seed = seed;
}

void WorldSettings::SetCityPopulation(unsigned int cityPopulation)
{
    WorldSettings::cityPopulation = cityPopulation;
}

void WorldSettings::SetCityPopulationModifier(float cityPopulationModifier)
{
    WorldSettings::cityPopulationModifier = cityPopulationModifier;
}

void WorldSettings::SetTavernCount(unsigned int tavernCount)
{
    WorldSettings::tavernCount = tavernCount;
}

void WorldSettings::SetTavernPopulation(unsigned int tavernPopulation)
{
    WorldSettings::tavernPopulation = tavernPopulation;
}

void WorldSettings::SetTavernPopulationModifier(float tavernPopulationModifier)
{
    WorldSettings::tavernPopulationModifier = tavernPopulationModifier;
}

void WorldSettings::SetTavernCountModifier(float tavernCountModifier)
{
    WorldSettings::tavernCountModifier = tavernCountModifier;
}

void WorldSettings::SetSquareCount(unsigned int squareCount)
{
    WorldSettings::squareCount = squareCount;
}

void WorldSettings::SetSquarePopulation(unsigned int squarePopulation)
{
    WorldSettings::squarePopulation = squarePopulation;
}

void WorldSettings::SetSquarePopulationModifier(float squarePopulationModifier)
{
    WorldSettings::squarePopulationModifier = squarePopulationModifier;
}

void WorldSettings::SetSquareCountModifier(float squareCountModifier)
{
    WorldSettings::squareCountModifier = squareCountModifier;
}

void WorldSettings::SetAberration(float aberration)
{
    WorldSettings::aberration = aberration;
}

unsigned int WorldSettings::GetSeed()
{
    return seed;
}

unsigned int WorldSettings::GetCityPopulation()
{
    return cityPopulation;
}

float WorldSettings::GetCityPopulationModifier()
{
    return cityPopulationModifier;
}

unsigned int WorldSettings::GetTavernCount()
{
    return tavernCount;
}

unsigned int WorldSettings::GetTavernPopulation()
{
    return tavernPopulation;
}

float WorldSettings::GetTavernPopulationModifier()
{
    return tavernPopulationModifier;
}

float WorldSettings::GetTavernCountModifier()
{
    return tavernCountModifier;
}

unsigned int WorldSettings::GetSquareCount()
{
    return squareCount;
}

unsigned int WorldSettings::GetSquarePopulation()
{
    return squarePopulation;
}

float WorldSettings::GetSquarePopulationModifier()
{
    return squarePopulationModifier;
}

float WorldSettings::GetSquareCountModifier()
{
    return squareCountModifier;
}

unsigned int WorldSettings::GetMinTalentForSchool()
{
    return minTalentForSchool;
}

void WorldSettings::SetMinTalentForSchool(unsigned int minTalentForSchool)
{
    WorldSettings::minTalentForSchool = minTalentForSchool;
}

unsigned int WorldSettings::GetNumberOfEnemiesSchools()
{
    return numberOfEnemiesSchools;
}

void WorldSettings::SetNumberOfEnemiesSchools(unsigned int numberOfEnemiesSchools)
{
    WorldSettings::numberOfEnemiesSchools = numberOfEnemiesSchools;
}

float WorldSettings::GetAberration()
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

void WorldSettings::SetTaskExpireTime(unsigned int taskExpireTime)
{
    WorldSettings::taskExpireTime = taskExpireTime;
}

unsigned int WorldSettings::GetTaskExpireTime()
{
    return taskExpireTime;
}
