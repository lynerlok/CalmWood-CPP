#include "C_environment.hpp"

#include <iostream>

int Environment::setTemperature(float newTemperature) {
    temperature = newTemperature;
    return 0;
}

int Environment::setHygtometry(float newHygrometry) {
    if( newHygrometry < 0 || newHygrometry > 1.0 ) {
        std::cout << "[DEBUG] hygrometry percentage value between 0 and 1" << std::endl;
        return -1;
    }
    hygrometry = newHygrometry;
    return 0;
}

int Environment::setAntropization(float newAntropizationRate) {

    if( newAntropizationRate < 0 || newAntropizationRate > 1.0 ) {
        std::cout << "[DEBUG] antropizationRate are percentage value between 0 and 1" << std::endl;
        return -1;
    }

    antropizationRate = newAntropizationRate;

    return 0;
}

int Environment::setEnvironmentParameters(float newTemperature,
        float newHygrometry,
        float newAntropizationRate) {

    if (newHygrometry < 0.0 || newHygrometry > 1.0 ||
            newAntropizationRate < 0.0 || newAntropizationRate > 1.0) {
        std::cout << "[DEBUG] hygrometry and antropizationRate are percentage value between 0 and 1" << std::endl;
        return -1;
    }

    temperature = newTemperature;
    hygrometry = newHygrometry;
    antropizationRate = newAntropizationRate;

    return 0;
}

std::vector<float> Environment::getEnvironmentParameters() {

    std::vector<float> parameters {temperature,hygrometry,antropizationRate};

    std::cout << "[DEBUG] Returning environment parameters : " << std::endl;

    for(const auto& x: parameters)
        std::cout << x << std::endl;

    return parameters;
}
