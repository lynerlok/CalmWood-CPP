#include <iostream>

#include "headers/U_randomGenerator.hpp"
#include "headers/C_animals.hpp"
#include "headers/C_environment.hpp"
#include "headers/C_plants.hpp"
#include <unistd.h>

using namespace std;


int MASrun(Environment environment, vector<Animals*> animals){
    
    const unsigned int SLEEPTIME = 0.5 * 1000000; // µsecs ! Use 1 multiplicator for test and minus for prod.
    const unsigned int MAXRUN = 10;
    
    bool runError = false;
    int agent = 0;
    vector<int> probabilities;
    
    int agentNumber = animals.size();
    
    /* DEV PART */
    for (int run=1; run != (MAXRUN + 1); ++run){
        agent = runRNG(0,agentNumber-1);
        animals[agent]->run();
    }

    
    /* PROD PART */
    
//     while (runError == false){
//         usleep(SLEEPTIME);
//     }
    
    /* END PROD PART */
    
    return 0;    
}

int MASinitialize() {
    
    Environment environment;
    vector<Animals*> animals;

    uint16_t MaxNumberAgent = 20;
    uint8_t NumberSpecies = 5;
    
     int setParameters(int newLength,
             int newActionRadius,
             int newDetectionRadius,
             int newGrowthState);
     
     for(int agent=0; agent < MaxNumberAgent; agent+=NumberSpecies){
       animals.push_back(new Leucorrhinia());
       animals[agent]->setProbabilities(0,100,0,0,0);
       animals[agent]->setParameters(1,5,5,0);
       animals.push_back(new Hyla());
       animals[agent+1]->setProbabilities(0,100,0,0,0);
       animals[agent+1]->setParameters(1,5,5,0);
       animals.push_back(new Phengaris());
       animals[agent+2]->setProbabilities(0,100,0,0,0);
       animals[agent+2]->setParameters(1,5,5,0);
       animals.push_back(new Zootoca());
       animals[agent+3]->setProbabilities(0,100,0,0,0);
       animals[agent+3]->setParameters(1,5,5,0);
       animals.push_back(new Vipera());
       animals[agent+4]->setProbabilities(0,100,0,0,0);
       animals[agent+4]->setParameters(1,5,5,0);
    }
    
    environment.setEnvironmentParameters(25,0.5,0.7);

    int LevelNumber = 1;
    std::vector<std::vector<int>> mapArray(10,std::vector<int>(10,0));

    
    MASrun(environment,animals);
    
    return 0;
}

int MAScollector(){
    
    return 0;
}

int main(int argc, char **argv) {
    
    cout << MASinitialize() << endl;
    
    //vector <float> location = animals[0]->getLocation();
    
    //cout << location[0] << endl;
    
    return 0;
}
    
    /* END DEV PART */
    
    //MASrun();
    
    // MAScollector();

