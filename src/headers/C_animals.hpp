#ifndef __C_ANIMALS_H_INCLUDED__
#define __C_ANIMALS_H_INCLUDED__

#include <string>
#include <vector>

class Animals {
public :
    Animals(int id = 0){idSaved = id;};
    ~Animals(void){};
    
    virtual int run() = 0;
    
    int getID(){return idSaved;}
    
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
    
    int idSaved = 0;
    
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
public :
    Leucorrhinia(int id = 0):Animals(id) {}
    int run();
};
    
class Hyla: public Animals {
public :
    Hyla(int id = 1):Animals(id) {}
    int run();
};
    
class Phengaris: public Animals {
public :
    Phengaris(int id = 2):Animals(id) {}
    int run();
};
    
class Zootoca: public Animals {
public :
    Zootoca(int id = 3):Animals(id) {}
    
    int run();
};
    
class Vipera: public Animals {
public :
    Vipera(int id = 4):Animals(id) {}
    
    int run();
};

#endif // __C_ANIMALS_H_INCLUDED__
