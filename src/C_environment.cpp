#include "headers/C_environment.hpp"

namespace constants
{
constexpr int numberOfSpeciesAnimal = 5;
constexpr int numberOfSpeciesPlant = 1;
}

int Cell::setViability ( bool newViability )
{
    viability = newViability;
    return 0;

}

bool Cell::getViabilityBoolean()
{
    return viability;
}

int Cell::addAnimal ( int ID, Animals * animal )
{

    AnimalCellContent.emplace ( ID,animal );

    return 0;
}

int Cell::addPlant ( int ID, Plants * plant )
{
    PlantCellContent.emplace ( std::make_pair ( ID,plant ) );

    return 0;
}

int Cell::removeAnimal ( int ID, Animals * animal )
{
    Aumit it = AnimalCellContent.begin();

    for ( it ; it != AnimalCellContent.end(); it++ )
    {
        if ( ( it->second ) == animal )
        {
            AnimalCellContent.erase ( it );
            break;
        }
    }

    return 0;
}

int Cell::removePlant ( int ID, Plants * plant )
{
    Pumit it = PlantCellContent.begin();

    for ( it ; it != PlantCellContent.end(); it++ )
    {
        if ( ( it->second ) == plant )
        {
            PlantCellContent.erase ( it );
            break;
        }
    }

    return 0;
}

std::unordered_map<int,int> Cell::getCellContentAnimals()
{

    std::unordered_map<int,int> ContentAnimals;

    for ( int i = 0; i < constants::numberOfSpeciesAnimal; ++i )
    {
        ContentAnimals.emplace ( i,AnimalCellContent.count ( i ) );
    }

    return ContentAnimals;

}

std::unordered_map<int,int> Cell::getCellContentPlants()
{

    std::unordered_map<int,int> ContentPlants;

    for ( int i = 0; i < constants::numberOfSpeciesPlant; ++i )
    {
        ContentPlants.emplace ( 0,PlantCellContent.count ( 0 ) );
    }

    return ContentPlants;

}

std::vector<int> Cell::getCellContentSpecs()
{
    return {viability,containTrees,containAnthropization,containWetland};
}

int Cell::toggleTrees()
{
    containTrees = ! containTrees;
    return 0;
}

int Cell::toggleAnthropization()
{
    containAnthropization = ! containAnthropization;
    return 0;
}

int Cell::toggleWetland()
{
    containWetland = ! containWetland;
    return 0;
}

int Environment::setTemperature ( float newTemperature )
{
    temperature = newTemperature;
    return 0;
}

int Environment::setHygrometry ( float newHygrometry )
{
    if ( newHygrometry < 0 || newHygrometry > 1.0 )
    {
        std::cout << "[DEBUG] hygrometry percentage value between 0 and 1" << std::endl;
        return -1;
    }
    hygrometry = newHygrometry;
    return 0;
}

int Environment::setAntropization ( float newAntropizationRate )
{

    if ( newAntropizationRate < 0 || newAntropizationRate > 1.0 )
    {
        std::cout << "[DEBUG] antropizationRate are percentage value between 0 and 1" << std::endl;
        return -1;
    }

    antropizationRate = newAntropizationRate;

    return 0;
}

int Environment::setEnvironmentParameters ( float newTemperature,
        float newHygrometry,
        float newAntropizationRate )
{

    if ( newHygrometry < 0.0 || newHygrometry > 1.0 ||
            newAntropizationRate < 0.0 || newAntropizationRate > 1.0 )
    {
        std::cout << "[DEBUG] hygrometry and antropizationRate are percentage value between 0 and 1" << std::endl;
        return -1;
    }

    temperature = newTemperature;
    hygrometry = newHygrometry;
    antropizationRate = newAntropizationRate;

    return 0;
}

unsigned int Environment::getTimeOfDay()
{
    return timeOfDay;
}

unsigned int Environment::setTimeOfDay ( int newTimeOfDay )
{
    timeOfDay = newTimeOfDay;
    return 0;
}

unsigned int Environment::setMonth ( int newMonthOfYear )
{
    monthOfYear = newMonthOfYear;
    return 0;
}

unsigned int Environment::getMonth()
{
    return monthOfYear;
}

unsigned int Environment::getOriginDayTime()
{
    return originTimeOfDay;
}

unsigned int Environment::getOriginMonth()
{
    return originMonth;
}

std::vector<float> Environment::getEnvironmentParameters()
{

    std::vector<float> parameters {temperature,hygrometry,antropizationRate};

    std::cout << "[DEBUG] Returning environment parameters : " << std::endl;

    for ( const auto& x: parameters )
        std::cout << x << std::endl;

    return parameters;
}

const unsigned int Environment::getMapLength()
{
    return mapLength;
}

Cell * Environment::getCell ( int x, int y )
{
    return map[x][y];
}

