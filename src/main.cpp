#include <iostream>
#include "headers/C_animals.hpp"
#include "headers/C_environment.hpp"
#include "headers/C_plants.hpp"
#include "headers/U_randomGenerator.hpp"
#include <unistd.h>

using namespace std;

unsigned int Animals::count = 0;

int MASinitialize() {
    
    Environment environment;
    vector<Leucorrhinia> leucorrhinia(5);
    vector<Hyla> hyla(2);
    vector<Zootoca> zootoca(3);
    vector<Vipera> vipera(1);
    
    vector<Animals> Animals(11);
    
    environment.setEnvironmentParameters(25,0.5,0.7);
    
    leucorrhinia[0].setParameters(4.0,5.0,1.0,1);
    leucorrhinia[0].setProbabilities(0.7,0.3,0.3,0.5);
    leucorrhinia[0].setName("Leuco1");
    
    int LevelNumber = 1;
    std::vector<std::vector<int>> mapArray(10,std::vector<int>(10,0));
    
    vector<float> loc2 {1,2,3}; // X,Y,Z ?
    
    if (leucorrhinia[0].setLocation(loc2) == -1) {
        cout << "ERROR while setting location" << endl;
        return -1;
    }
    
    int numberAnimals = leucorrhinia.size() + hyla.size() + zootoca.size() + vipera.size();
    
    return 0;
}

int MASrun(){
    
    const unsigned int SLEEPTIME = 0.5 * 1000000; // µsecs ! Use 1 multiplicator for test and minus for prod.
    const unsigned int MAXRUN = 3;
    const unsigned int numberOfRun = 10;
    bool runError = false;
    int animalPicker = 0;
    int speciePicker = 0;
    int animalNumber = 0;
    
    unsigned int totalAnimals = Animals::totalAnimals();
    
        cout << "[DEBUG] Number of animals in simulation : " << totalAnimals << endl;
    
    /* DEV PART */
    for (int run=1; run != (MAXRUN + 1); ++run){ 
        cout << "[DEBUG] Run number : " << run << endl;
        
        speciePicker = runRNG(0,3);
        animalPicker = runRNG(0,totalAnimals);
        
    }

    /* PROD PART */
    
//     while (runError == false){
//         usleep(SLEEPTIME);
//     }
    
    /* END PROD PART */
    
    return 0;    
}

int MAScollector(){
    
    return 0;
}

int main(int argc, char **argv) {
    return 0;
}
    
    /* END DEV PART */
    
    
    
    //MASinitialize();
    
    //MASrun();
    
    // MAScollector();

