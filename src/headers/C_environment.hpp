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
    std::vector<bool> getInfoBoolean();

    int addAnimal ( int ID, Animals * animal );
    int removePlant ( int ID, Plants * plant );
    int removeAnimal ( int ID, Animals * animal );
    int addPlant ( int ID, Plants * plant );

    int getCellContent();

    int toggleTrees();
    int toggleAnthropization();
    int toggleWetland();

protected :
    bool viability = true;
    bool containTrees = false;
    bool containAnthropization = false;
    bool containWetland = false;
    bool isWater = false;
    
    int waterEutrophisationRate = 0;
    int waterPlantClosedRate = 0;

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
    
    int getTimeOfDay(){
        return timeOfDay;
    }
    
    int setTimeOfDay(int newTimeOfDay){
        timeOfDay = newTimeOfDay;
        return 0;
    }
    
    int getMonth(int newMonthOfYear){
        monthOfYear = newMonthOfYear;
        return 0;
    }

    std::vector<float> getEnvironmentParameters();

    const unsigned int getMapLength();

    Cell * getCell ( int x, int y );

protected :
    float temperature = 0.0;
    float hygrometry = 0.0 ;
    float antropizationRate = 0.0; // Default a super dry, cold and wild environment :)

    // map, action field
    const unsigned int mapLength = 5;

    std::vector<std::vector<Cell*>> map{mapLength};
    
    int timeOfDay = 12; // In hours
    int monthOfYear = 05;

};

#endif // __C_ENVIRONMENT_H_INCLUDED__
