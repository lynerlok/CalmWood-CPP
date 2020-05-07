#ifndef __MAS_H_INCLUDED__
#define __MAS_H_INCLUDED__

#include <string>
#include <vector>

#include "randomUtils.h"

// Perlin noise to choose the agent !
 
// struct MAP {
//     int LevelNumber;
//     std::vector<std::vector<int>> mapArray;
// } map;

class Environment {
public :
    Environment(void){};
    ~Environment(void){};
    
    int setTemperature(float newTemperature){
        temperature = newTemperature;
        return 0;
    }
    
    int setHygtometry(float newHygrometry){
        if( newHygrometry < 0 || newHygrometry > 1.0 ){
            std::cout << "[DEBUG] hygrometry percentage value between 0 and 1" << std::endl;
            return -1;
        }
        hygrometry = newHygrometry;
        return 0;
    }
    
    int setAntropization(float newAntropizationRate){
        
        if( newAntropizationRate < 0 || newAntropizationRate > 1.0 ){
            std::cout << "[DEBUG] antropizationRate are percentage value between 0 and 1" << std::endl;
            return -1;
        }
        
        antropizationRate = newAntropizationRate;
        
        return 0;
    }
    
    int setEnvironmentParameters(float newTemperature, 
                                 float newHygrometry, 
                                 float newAntropizationRate){
        
        if (newHygrometry < 0.0 || newHygrometry > 1.0 || 
            newAntropizationRate < 0.0 || newAntropizationRate > 1.0){
            std::cout << "[DEBUG] hygrometry and antropizationRate are percentage value between 0 and 1" << std::endl;
            return -1;
        }
       
        temperature = newTemperature;
        hygrometry = newHygrometry;
        antropizationRate = newAntropizationRate;
        
        return 0;
    }
    
    std::vector<float> getEnvironmentParameters(){
        
        std::vector<float> parameters {temperature,hygrometry,antropizationRate};
        
        std::cout << "[DEBUG] Returning environment parameters : " << std::endl;
        
        for(const auto& x: parameters)
            std::cout << x << std::endl;
        
        return parameters;
    }
    
protected :
    float temperature = 0.0;
    float hygrometry = 0.0 ;
    float antropizationRate = 0.0; // Default a super dry, cold and wild environment :)

};

class Animals {
private :
    static unsigned int count;
public :
    Animals(void){count++;};
    ~Animals(void){};
    
    static unsigned int totalAnimals(void){
        return count;
    }
    
    int run(){
        return 0;
    }
    
    int setLocation(std::vector<float> newLocation){
        if (newLocation.size() != 3) {
            return -1;
        }
        location = newLocation;
        return 0;
    }
        
    std::vector <float> getLocation(){return location;}
    
    int setName(std::string newName){name = newName;return 0;};
    std::string getName(){return name;};
    
    int setParameters(float newLength,
             float newActionRadius,
             float newDetectionRadius,
             int newGrowthState){
        
        length = newLength;
        actionRadius = newActionRadius;
        detectionRadius = newDetectionRadius;
        growthState = newGrowthState;
        
        return 0;
    }
    
    int setProbabilities(float newAriseProbability,
                     float newDeadProbability,
                     float newGrowthProbability,
                     float newMoveProbability){
        
        ariseProbability = newAriseProbability;
        deadProbability = newDeadProbability;
        growthProbability = newGrowthProbability;
        moveProbability = newMoveProbability;

        return 0;
    }
    
    int alterAgent(std::string alterationType){
        bool applyAlteration = (runRNG(0,100)) < ariseProbability;
        std::cout << "Alterate agent ? : " << applyAlteration << std::endl;
        return 0;
    }

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
    int growth(int targetState );
    int arise();
    int dead();

    int ariseProbability = 0;
    int deadProbability = 0;
    int growthProbability = 0;
    int moveProbability = 0;

};

class Leucorrhinia: public Animals {
public :
    int run(){std::cout << "Running leucorrhinia life cycle !" << std::endl; return 0;};
};
    
class Hyla: public Animals {};
    
class Phengaris: public Animals {};
    
class Zootoca: public Animals {};
    
class Vipera: public Animals {};

class Plants {
public:
    Plants(void){};
    ~Plants(void){};
    std::string name;
    
    int growth(int targetState);
    int damage();
}; 

class Gentiania: public Plants {};

#endif // __MAS_H_INCLUDED__ 
