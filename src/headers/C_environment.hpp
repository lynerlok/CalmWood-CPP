#ifndef __C_ENVIRONMENT_H_INCLUDED__
#define __C_ENVIRONMENT_H_INCLUDED__

#include <string>
#include <vector>

class Environment {
public :
    Environment(void){};
    ~Environment(void){};
    
    int setTemperature(float newTemperature);
    int setHygtometry(float newHygrometry);
    
    int setAntropization(float newAntropizationRate);
    
    int setEnvironmentParameters(float newTemperature, float newHygrometry, float newAntropizationRate);
    
    std::vector<float> getEnvironmentParameters();
        
protected :
    float temperature = 0.0;
    float hygrometry = 0.0 ;
    float antropizationRate = 0.0; // Default a super dry, cold and wild environment :)

};

#endif // __C_ENVIRONMENT_H_INCLUDED__
