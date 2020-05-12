#include "C_animals.hpp"

int Animals::run()
{
    std::cout << "ID : " << getID() << std::endl;
    
    std::vector<int> probabilities = getProbabilities();

    for (int alteration = 0; alteration < 5; ++alteration){
        triggerAgent(alteration,probabilities[alteration]);
    }
    
    return 0;
}

int Animals::setLocation(std::vector<float> newLocation) {
    if (newLocation.size() != 3)
        return -1;
        
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

int Animals::setParameters(int newLength,
                  int newActionRadius,
                  int newDetectionRadius,
                  int newGrowthState) {

    length = newLength;
    actionRadius = newActionRadius;
    detectionRadius = newDetectionRadius;
    growthState = newGrowthState;

    return 0;
}

int Animals::setProbabilities(int newAriseProbability, 
                         int newMoveProbability, 
                         int newEatProbability, 
                         int newGrowthProbability, 
                         int newDeadProbability) {

    ariseProbability = newAriseProbability;
    moveProbability = newMoveProbability;
    eatProbability = newEatProbability;
    growthProbability = newGrowthProbability;
    deadProbability = newDeadProbability;
    

    return 0;
}

std::vector<int> Animals::getProbabilities() {

    std::vector<int> probabilities = {ariseProbability, moveProbability, eatProbability, growthProbability, deadProbability};
   
    return probabilities;
}

int Animals::triggerAgent(int alterationType, int associatedProbability) {
    if ((runRNG(0,100)) < associatedProbability){
        
        switch(alterationType) {
            case 0 : // arise
                std::cout << "ARISE" << std::endl;
                arise();
                return 1;
                break;
            case 1 : // move
                std::cout << "MOVE" << std::endl;
                move();
                return 1;
                break;
            case 2 : // eat
                std::cout << "EAT" << std::endl;
                eat();
                return 1;
                break;
            case 3 : // growth
                std::cout << "GROWTH" << std::endl;
                growth();
                return 1;
                break;
            case 4 : // dead
                std::cout << "DEAD" << std::endl;
                dead();
                return 1;
                break;
        }
    }
    return 0;
}

int Animals::arise()
{
    return 0;
}

int Animals::move()
{
    std::vector<float> location;
    int locationOffset = 0;
    location = getLocation();

    for(int i=0; i<3; ++i){
        locationOffset = runRNG(0,actionRadius);
        satietyIndex -= locationOffset;
        
        if(satietyIndex <= 0){
            if(triggerAgent(2,eatProbability) == 0)
                dead();
        }
        
        location[i] += locationOffset;
    }
    
    setLocation(location);
    
    return 0;
}

int Animals::eat()
{
    int eatAmount = runRNG(1,25);
    satietyIndex = (satietyIndex + eatAmount) % 100;
   
    return 0;
}

int Animals::growth()
{
    
    if(satietyIndex > 80){
        growthState += 1;
        if(growthState >= 3){dead();}
    }
    
    return 0;
}

int Animals::dead()
{
    std::cout << "DEAD" << std::endl;
    return 0;
}

int Leucorrhinia::run(){
    std::cout << "Leucorrhinia" << std::endl;
    
    std::vector<int> probabilities = getProbabilities();
     
    for (int alteration = 0; alteration < 5; ++alteration){
        triggerAgent(alteration,probabilities[alteration]);
    }
    
    return 0;
}

// int Hyla::run(){
//     std::cout << "Hyla" << std::endl;
//     return 0;
// }
// 
// int Phengaris::run(){
//     std::cout << "Phengaris" << std::endl;
//     return 0;
// }
// 
// int Zootoca::run(){
//     std::cout << "Zootoca" << std::endl;
//     return 0;
// }
// 
// int Vipera::run(){
//     std::cout << "Vipera" << std::endl;
//     return 0;
// }

