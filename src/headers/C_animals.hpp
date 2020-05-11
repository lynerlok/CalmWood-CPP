#ifndef __C_ANIMALS_H_INCLUDED__
#define __C_ANIMALS_H_INCLUDED__

#include <string>
#include <vector>

class Animals {
private :
    static unsigned int count;
public :
    Animals(void){count++;};
    ~Animals(void){};
    
    static unsigned int totalAnimals(void){return count;};
    
    int run();
    
    int setLocation(std::vector<float> newLocation);
        
    std::vector <float> getLocation();
    
    int setName(std::string newName);
    std::string getName();
    
    int setParameters(float newLength,
             float newActionRadius,
             float newDetectionRadius,
             int newGrowthState);
    
    int setProbabilities(float newAriseProbability,
                     float newDeadProbability,
                     float newGrowthProbability,
                     float newMoveProbability);
    
    int alterAgent(std::string alterationType);

protected : 
    
    std::vector <float> location{0,0,0};

    std::string name;
    std::string form;

    float length = 0.0;
    float actionRadius = 0.0;
    float detectionRadius = 0.0;
    int growthState = 0;

    int detection();
    int move();
    int predation();
    int growth(int targetState);
    int arise();
    int dead();

    int ariseProbability = 0;
    int deadProbability = 0;
    int growthProbability = 0;
    int moveProbability = 0;

};

class Leucorrhinia: public Animals {
    int id = 0;
};
    
class Hyla: public Animals {
    int id = 1;
};
    
class Phengaris: public Animals {
    int id = 2;
};
    
class Zootoca: public Animals {
    int id = 3;
};
    
class Vipera: public Animals {
    int id = 4;
};

#endif // __C_ANIMALS_H_INCLUDED__
