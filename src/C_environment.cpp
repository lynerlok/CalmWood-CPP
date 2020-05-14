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
        containGentiana,
        containTrees,
        containAnthropization,
        containWetland
    };
}

int Cell::addAnimal(int ID, Animals * animal)
{
    CellContent.emplace(ID,animal);

    return 0;
}

int Cell::removeAnimal(int ID, Animals * animal)
{
    umit it = CellContent.begin();

    for(it ; it != CellContent.end(); it++)
    {
        if((it->second) == animal)
        {
            CellContent.erase(it);
            break;
        }
    }

    return 0;
}

// Just a test to get cell content : REWORK NEEDED !
int Cell::getCellContent()
{
    std::cout << "Viability : " << viability << std::endl;
    std::cout << "Gentiana : " << containGentiana << std::endl;
    std::cout << "Trees : " << containTrees << std::endl;
    std::cout << "Anthropization : " << containAnthropization << std::endl;
    std::cout << "Wetland : " << containWetland << std::endl;
    
    for (int i = 0; i < 4; ++i){
        std::cout << "Number of " << i << " : " << CellContent.count(i) << std::endl;
    }
    return 0;
}


int Cell::toggleGentiana()
{
    containGentiana = ! containGentiana;
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

Cell Environment::getCell(int x, int y)
{
    return map[x][y];
}
