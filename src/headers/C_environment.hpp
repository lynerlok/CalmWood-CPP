#ifndef __C_ENVIRONMENT_H_INCLUDED__
#define __C_ENVIRONMENT_H_INCLUDED__

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

#include "C_animals.hpp"
#include "C_plants.hpp"

class Animals;

typedef std::unordered_multimap<int, Animals *>::iterator Aumit;
typedef std::unordered_multimap<int, Plants *>::iterator Pumit;

class Cell
{
public :
    Cell() {};
    ~Cell()
    {
        AnimalCellContent.clear();
        PlantCellContent.clear();
    };

    int setViability ( bool newViability );

    bool getViabilityBoolean();

    int addAnimal ( int ID, Animals * animal );
    int removePlant ( int ID, Plants * plant );
    int removeAnimal ( int ID, Animals * animal );
    int addPlant ( int ID, Plants * plant );

    std::unordered_map<int,int> getCellContentAnimals();
    std::unordered_map<int,int> getCellContentPlants();
    std::vector<int> getCellContentSpecs();

    int toggleTrees();
    int toggleAnthropization();
    int toggleWetland();

protected :
    int viability = 1;
    int containTrees = 0;
    int containAnthropization = 0;
    int containWetland = 0;
    int isWater = 0;
    
    int waterEutrophisationRate = 0;
    int waterPlantClosedRate = 0;
    int sunExpositionRate = 60;

    std::unordered_multimap<int, Animals *> AnimalCellContent;
    std::unordered_multimap<int, Plants *> PlantCellContent;

};

class Environment
{
public :
    Environment ( void )
    {
        for ( int x=0; x<mapLength; ++x )
            for ( int y=0; y<mapLength; ++y )
                map[x].push_back ( new Cell() );
    };
    ~Environment ( void )
    {
        for ( int x=0; x<mapLength; ++x )
            for ( int y=0; y<mapLength; ++y )
                delete ( map[x][y] );
    };

    int setTemperature ( float newTemperature );

    int setHygrometry ( float newHygrometry );

    int setAntropization ( float newAntropizationRate );

    int initializeEnvironmentMAP();

    int setEnvironmentParameters ( float newTemperature, float newHygrometry, float newAntropizationRate );
    
    
    unsigned int getTimeOfDay();
    
    unsigned int setTimeOfDay(int newTimeOfDay);
    
    unsigned int setMonth(int newMonthOfYear);
    
    unsigned int getMonth();
    
    unsigned int getOriginDayTime();
    
    unsigned int getOriginMonth();
    
    std::vector<float> getEnvironmentParameters();

    const unsigned int getMapLength();

    Cell * getCell ( int x, int y );
    
    const unsigned int DAYSMONTH = 4;

protected :
    float temperature = 0.0;
    float hygrometry = 0.0 ;
    float antropizationRate = 0.0; // Default a super dry, cold and wild environment :)
    int numberSpecies = 5;
    
    // map, action field
    const unsigned int mapLength = 5;

    std::vector<std::vector<Cell*>> map{mapLength};
    
    const unsigned int originTimeOfDay = 12;
    const unsigned int originMonth = 5;
    
    unsigned int timeOfDay = 12; // In hours always % 24
    unsigned int monthOfYear = 5; // Always % 12

};

#endif // __C_ENVIRONMENT_H_INCLUDED__
