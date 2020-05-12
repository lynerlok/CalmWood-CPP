#include <iostream>
#include "headers/C_animals.hpp"
#include "headers/C_environment.hpp"
#include "headers/C_plants.hpp"
#include "headers/U_randomGenerator.hpp"
#include <unistd.h>

using namespace std;

int MASrun(Environment environment, vector<Animals*> animals){
    
    const unsigned int SLEEPTIME = 0.5 * 1000000; // µsecs ! Use 1 multiplicator for test and minus for prod.
    const unsigned int MAXRUN = 10;
    
    bool runError = false;
    int agent = 0;
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
    
   for(int agent=0; agent < MaxNumberAgent; agent+=NumberSpecies){
       animals.push_back(new Leucorrhinia());
       animals.push_back(new Hyla());
       animals.push_back(new Phengaris());
       animals.push_back(new Zootoca());
       animals.push_back(new Vipera());
    }
    
    environment.setEnvironmentParameters(25,0.5,0.7);

    int LevelNumber = 1;
    std::vector<std::vector<int>> mapArray(10,std::vector<int>(10,0));
    
    vector<float> loc2 {1,2,3}; // X,Y,Z ?
    
    if (animals[0]->setLocation(loc2) == -1) {
        cout << "ERROR while setting location" << endl;
        return -1;
    }
    
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

