//
// Created by Krzysztof Sawicki on 30/05/2024.
//

#ifndef INF_PROJECT_WORLDSETTINGS_H
#define INF_PROJECT_WORLDSETTINGS_H


class WorldSettings
{
    static unsigned int seed;
    static unsigned int cityPopulation;
    static float cityPopulationModifier;
    static unsigned int tavernCount;
    static unsigned int tavernPopulation;
    static float tavernPopulationModifier;
    static float tavernCountModifier;
    static unsigned int squareCount ;
    static unsigned int squarePopulation;
    static float squarePopulationModifier;
    static float squareCountModifier;
    static unsigned int taskExpireTime;
    static unsigned int minTalentForSchool;
    static unsigned int numberOfEnemiesSchools;

    static float aberration;

public:
    static unsigned int GetSeed();
    static unsigned int GetCityPopulation();
    static float GetCityPopulationModifier();
    static unsigned int GetTavernCount();
    static unsigned int GetTavernPopulation();
    static float GetTavernPopulationModifier();
    static float GetTavernCountModifier();
    static unsigned int GetSquareCount();
    static unsigned int GetSquarePopulation();
    static float GetSquarePopulationModifier();
    static float GetSquareCountModifier();
    static unsigned int GetTaskExpireTime();
    static unsigned int GetMinTalentForSchool();
    static unsigned int GetNumberOfEnemiesSchools();
    static float GetAberration();
    static void SetSeed(unsigned int seed);
    static void SetCityPopulation(unsigned int cityPopulation);
    static void SetCityPopulationModifier(float cityPopulationModifier);
    static void SetTavernCount(unsigned int tavernCount);
    static void SetTavernPopulation(unsigned int tavernPopulation);
    static void SetTavernPopulationModifier(float tavernPopulationModifier);
    static void SetTavernCountModifier(float tavernCountModifier);
    static void SetSquareCount(unsigned int squareCount);
    static void SetSquarePopulation(unsigned int squarePopulation);
    static void SetSquarePopulationModifier(float squarePopulationModifier);
    static void SetSquareCountModifier(float squareCountModifier);
    static void SetTaskExpireTime(unsigned int taskExpireTime);
    static void SetMinTalentForSchool(unsigned int minTalentForSchool);
    static void SetNumberOfEnemiesSchools(unsigned int numberOfEnemiesSchools);
    static void SetAberration(float aberration);

    static void ApplyModifiers();


};


#endif //INF_PROJECT_WORLDSETTINGS_H
