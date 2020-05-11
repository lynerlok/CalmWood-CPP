#include "C_animals.hpp"

#include <iostream>

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

int Leucorrhinia::run(){
    std::cout << "Leucorrhinia" << std::endl;
    return 0;
}

int Hyla::run(){
    std::cout << "Hyla" << std::endl;
    return 0;
}

int Phengaris::run(){
    std::cout << "Phengaris" << std::endl;
    return 0;
}

int Zootoca::run(){
    std::cout << "Zootoca" << std::endl;
    return 0;
}

int Vipera::run(){
    std::cout << "Vipera" << std::endl;
    return 0;
}

