//
// Created by Krzysztof Sawicki on 30/05/2024.
//

#ifndef INF_PROJECT_WORLDSETTINGS_H
#define INF_PROJECT_WORLDSETTINGS_H


class WorldSettings
{
    unsigned int seed = 0;
    unsigned int cityPopulation = 10000;
    float cityPopulationModifier = 1.0f;
    unsigned int tavernCount = 15;
    unsigned int tavernPopulation = 20;
    float tavernPopulationModifier = 1.0f;
    float tavernCountModifier = 1.0f;
    unsigned int squareCount = 5;
    unsigned int squarePopulation = 50;
    float squarePopulationModifier = 1.0f;
    float squareCountModifier = 1.0f;

    float aberration = 0.1f;

public:
    WorldSettings() = default;
    WorldSettings(unsigned int seed, unsigned int cityPopulation, float cityPopulationModifier, unsigned int tavernCount, unsigned int tavernPopulation, float tavernPopulationModifier, float tavernCountModifier, unsigned int squareCount, unsigned int squarePopulation, float squarePopulationModifier, float squareCountModifier);
    unsigned int getSeed() const;
    unsigned int getCityPopulation() const;
    float getCityPopulationModifier() const;
    unsigned int getTavernCount() const;
    unsigned int getTavernPopulation() const;
    float getTavernPopulationModifier() const;
    float getTavernCountModifier() const;
    unsigned int getSquareCount() const;
    unsigned int getSquarePopulation() const;
    float getSquarePopulationModifier() const;
    float getSquareCountModifier() const;
    float getAberration() const;
    void setSeed(unsigned int seed);
    void setCityPopulation(unsigned int cityPopulation);
    void setCityPopulationModifier(float cityPopulationModifier);
    void setTavernCount(unsigned int tavernCount);
    void setTavernPopulation(unsigned int tavernPopulation);
    void setTavernPopulationModifier(float tavernPopulationModifier);
    void setTavernCountModifier(float tavernCountModifier);
    void setSquareCount(unsigned int squareCount);
    void setSquarePopulation(unsigned int squarePopulation);
    void setSquarePopulationModifier(float squarePopulationModifier);
    void setSquareCountModifier(float squareCountModifier);
    void setAberration(float aberration);
    ~WorldSettings();

    void ApplyModifiers();
};


#endif //INF_PROJECT_WORLDSETTINGS_H
