#include "headers/C_animals.hpp"

int Animals::getID()
{
    return id;
}

int Animals::run(Environment * environment)
{
    std::cout << "ID : " << getID() << std::endl;

    std::vector<int> probabilities = getProbabilities();
    
    detection(environment);
    
    for (int alteration = 0; alteration < 5; ++alteration) {
        triggerAgent(environment,alteration,probabilities[alteration]);
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

int Animals::triggerAgent(Environment * environment, int alterationType, int associatedProbability) {
    if ((runRNG(0,100)) < associatedProbability) {

        switch(alterationType) {
        case 0 : // arise
            std::cout << "ARISE" << std::endl;
            arise();
            break;
        case 1 : // move
            std::cout << "MOVE" << std::endl;
            move(environment);
            break;
        case 2 : // eat
            std::cout << "EAT" << std::endl;
            eat(environment);
            break;
        case 3 : // growth
            std::cout << "GROWTH" << std::endl;
            growth();
            break;
        case 4 : // dead
            std::cout << "DEAD" << std::endl;
            dead();
            break;
        }
    }
    
    
    return 0;
}

int Animals::detection(Environment * environment)
{
   int x = getLocation()[0];
   int y = getLocation()[1];
   
   std::cout << x << " | " << y << std::endl;
   
   environment->getCell(x,y)->getCellContent();
   
   return 0;
}


int Animals::arise()
{
    return 0;
}

int Animals::move(Environment * environment)
{
    std::vector<float> location(3);
    std::vector<float> newLocation(3);
    
    int locationOffset = 0;
    int orientation = 0;
    
    const unsigned int mapLength = environment->getMapLength();

    location = getLocation();
    environment->getCell(location[0],location[1])->removeAnimal(id, this);

    do {
        location = getLocation();

        for(int i=0; i<2; ++i) {
            locationOffset = runRNG(0,actionRadius);
            orientation = runRNG(0,1);
            
            satietyIndex -= locationOffset;

            if(satietyIndex <= 0) {
                if(triggerAgent(environment,2,eatProbability) == 0)
                    dead();
            }
            
            if ( orientation ) {
                newLocation[i] = location[i] + locationOffset;
                if (newLocation[i] < mapLength ){
                    location[i] = newLocation[i];
                }
                
            }
            
            if ( ! orientation ) {
                newLocation[i] = location[i] - locationOffset;
                if (newLocation[i] > 0 ){
                    location[i] = newLocation[i];
                }
            }
        }
    }
    while(! environment->getCell(location[0],location[1])->getViabilityBoolean());

    setLocation(location);
    environment->getCell(location[0],location[1])->addAnimal(id, this);
    
    detection(environment);
    
    return 0;
}

int Animals::eat(Environment * environment)
{
    
    detection(environment);
    
    int eatAmount = runRNG(1,25);
    satietyIndex = (satietyIndex + eatAmount) % 100;

    return 0;
}

int Animals::growth()
{

    if(satietyIndex > 80) {
        growthState += 1;
        if(growthState >= 3) {
            dead();
        }
    }

    return 0;
}

int Animals::dead()
{
    std::cout << "DEAD" << std::endl;
    return 0;
}
