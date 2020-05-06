#include <iostream>

#include "mas.h"
//#include "randomUtils.h"
#include <unistd.h>

using namespace std;

int MASinitialize() {
   
    Environment environment;
    Leucorrhinia leuco1, leuco2, leuco3;
    Hyla hyla1, hyla2, hyla3;
    Zootoca zoo1, zoo2;
    Vipera vipera1;
    
    int numberOfRun = 10;
    
    environment.setEnvironmentParameters(25,0.5,0.7);
    //vector<float> result = environment.getEnvironmentParameters();
    
    leuco1.setParameters(4.0,5.0,1.0,1);
    leuco1.setProbabilities(0.7,0.3,0.3,0.5);
    leuco1.setName("Leuco1");
    
    vector<float> loc2 {1,2,3};
    
    if (leuco1.setLocation(loc2) == -1) {
        cout << "ERROR while setting location" << endl;
        return -1;
    }
    
//     for (auto x: leuco1.getLocation())
//         std::cout << x << ' ';
//     cout << endl;
    
//    cout << leuco1.getName() << endl;
    
    return 0;
}

int MASrun(){
    
    const unsigned int SLEEPTIME = 0.5 * 1000000; // µsecs ! Use 1 multiplicator for test and minus for prod.
    const unsigned int MAXRUN = 5;
    bool runError = false;
    
    /* DEV PART */
    for (int run=1; run != (MAXRUN + 1); ++run){ 
        cout << "[DEBUG] Run number : " << run << endl;
//        runRNG(0,10); // Testing PCG32 RNG
        usleep(SLEEPTIME);
    }
    
    /* END DEV PART */
    
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
    
    MASinitialize();
    
    MASrun();
    
    // MAScollector();
    
    return 0;
}


