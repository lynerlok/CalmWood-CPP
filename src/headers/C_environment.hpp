#ifndef __C_ENVIRONMENT_H_INCLUDED__
#define __C_ENVIRONMENT_H_INCLUDED__

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

#include "C_animals.hpp"

class Animals;

typedef std::unordered_multimap<int, Animals *>::iterator umit; 

class Cell {
public :
    Cell() {};
    ~Cell() {};

    int setViability(bool newViability);

    bool getViabilityBoolean();
    std::vector<bool> getInfoBoolean();
    
    int addAnimal(int ID, Animals * animal);
    int removeAnimal(int ID, Animals * animal);
    
    int getCellContent();
    
    int toggleGentiana();
    int toggleTrees();
    int toggleAnthropization();
    int toggleWetland();

protected :
    bool viability = true;
    bool containGentiana = false;
    bool containTrees = false;
    bool containAnthropization = false;
    bool containWetland = false;
    
    std::unordered_multimap<int, Animals *> CellContent;
};

class Environment {
public :
    Environment(void) {};
    ~Environment(void) {};

    int setTemperature(float newTemperature);

    int setHygrometry(float newHygrometry);

    int setAntropization(float newAntropizationRate);

    int initializeEnvironmentMAP();

    int setEnvironmentParameters(float newTemperature, float newHygrometry, float newAntropizationRate);

    std::vector<float> getEnvironmentParameters();

    Cell getCell(int x, int y);

protected :
    float temperature = 0.0;
    float hygrometry = 0.0 ;
    float antropizationRate = 0.0; // Default a super dry, cold and wild environment :)

    // map, action field

    Cell map[100][100];
    
    // u_int8_t  viability zone[][]
    // u_int8_t map[][]


};

#endif // __C_ENVIRONMENT_H_INCLUDED__
