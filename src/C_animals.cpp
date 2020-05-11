#include "C_animals.hpp"

#include <iostream>

//static unsigned int Animals::totalAnimals(void){
//    return count;
//}
    
int Animals::run(){
    return 0;
}
    
int Animals::setLocation(std::vector<float> newLocation) {
    if (newLocation.size() != 3) {
        return -1;
    }
    location = newLocation;
    return 0;
}

std::vector <float> Animals::getLocation() {
    return location;
}

int Animals::setName(std::string newName) {
    name = newName;
    return 0;
}

std::string Animals::getName() {
    return name;
}

int Animals::setParameters(float newLength,
                  float newActionRadius,
                  float newDetectionRadius,
                  int newGrowthState) {

    length = newLength;
    actionRadius = newActionRadius;
    detectionRadius = newDetectionRadius;
    growthState = newGrowthState;

    return 0;
}

int Animals::setProbabilities(float newAriseProbability,
                     float newDeadProbability,
                     float newGrowthProbability,
                     float newMoveProbability) {

    ariseProbability = newAriseProbability;
    deadProbability = newDeadProbability;
    growthProbability = newGrowthProbability;
    moveProbability = newMoveProbability;

    return 0;
}

int Animals::alterAgent(std::string alterationType) {
   // bool applyAlteration = (runRNG(0,100)) < ariseProbability;
  //  std::cout << "Alterate agent ? : " << applyAlteration << std::endl;
    return 0;
}
