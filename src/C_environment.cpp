#include "headers/C_environment.hpp"

int Cell::setViability(bool newViability)
{
    viability = newViability;
    return 0;

}

bool Cell::getViabilityBoolean()
{
    return viability;
}

std::vector<bool> Cell::getInfoBoolean()
{
    return std::vector<bool> {
        containTrees,
        containAnthropization,
        containWetland
    };
}

int Cell::addAnimal(int ID, Animals * animal)
{

    AnimalCellContent.emplace(ID,animal);
    
    return 0;
}

int Cell::addPlant(int ID, Plants * plant)
{
    PlantCellContent.emplace(std::make_pair(ID,plant));

    return 0;
}

int Cell::removeAnimal(int ID, Animals * animal)
{
    Aumit it = AnimalCellContent.begin();

    for(it ; it != AnimalCellContent.end(); it++)
    {
        if((it->second) == animal)
        {
            AnimalCellContent.erase(it);
            break;
        }
    }

    return 0;
}

int Cell::removePlant(int ID, Plants * plant)
{
    Pumit it = PlantCellContent.begin();

    for(it ; it != PlantCellContent.end(); it++)
    {
        if((it->second) == plant)
        {
            PlantCellContent.erase(it);
            break;
        }
    }

    return 0;
}

// Just a test to get cell content : REWORK NEEDED !
int Cell::getCellContent()
{
    std::cout << "Viability : " << viability << std::endl;
    std::cout << "Trees : " << containTrees << std::endl;
    std::cout << "Anthropization : " << containAnthropization << std::endl;
    std::cout << "Wetland : " << containWetland << std::endl;
    
    std::cout << "Size of Animals : " << AnimalCellContent.size() << std::endl;
    std::cout << "Size of Plants : " << PlantCellContent.size() << std::endl;
    
    for (int i = 0; i < 4; ++i){ // NUMBER OF SPECIES
        std::cout << "Number of " << i << " : " << AnimalCellContent.count(i) << std::endl;
    }
    
    std::cout << "Number of Gentiana : " << PlantCellContent.count(0) << std::endl;
    
    return 0;
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

int Environment::setTemperature(float newTemperature) {
    temperature = newTemperature;
    return 0;
}

int Environment::setHygrometry(float newHygrometry) {
    if( newHygrometry < 0 || newHygrometry > 1.0 ) {
        std::cout << "[DEBUG] hygrometry percentage value between 0 and 1" << std::endl;
        return -1;
    }
    hygrometry = newHygrometry;
    return 0;
}

int Environment::setAntropization(float newAntropizationRate) {

    if( newAntropizationRate < 0 || newAntropizationRate > 1.0 ) {
        std::cout << "[DEBUG] antropizationRate are percentage value between 0 and 1" << std::endl;
        return -1;
    }

    antropizationRate = newAntropizationRate;

    return 0;
}

int Environment::setEnvironmentParameters(float newTemperature,
        float newHygrometry,
        float newAntropizationRate) {

    if (newHygrometry < 0.0 || newHygrometry > 1.0 ||
            newAntropizationRate < 0.0 || newAntropizationRate > 1.0) {
        std::cout << "[DEBUG] hygrometry and antropizationRate are percentage value between 0 and 1" << std::endl;
        return -1;
    }

    temperature = newTemperature;
    hygrometry = newHygrometry;
    antropizationRate = newAntropizationRate;

    return 0;
}

std::vector<float> Environment::getEnvironmentParameters() {

    std::vector<float> parameters {temperature,hygrometry,antropizationRate};

    std::cout << "[DEBUG] Returning environment parameters : " << std::endl;

    for(const auto& x: parameters)
        std::cout << x << std::endl;

    return parameters;
}

const unsigned int Environment::getMapLength()
{
    return mapLength;
}

Cell * Environment::getCell(int x, int y)
{
    return map[x][y];
}

