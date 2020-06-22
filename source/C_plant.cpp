#include <unistd.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

#include "C_plant.hpp"

int Plant::getID()
{
    return id;
}

int Plant::growth ( int targetState )
{
    return 0;
}

int Plant::damage()
{
    return 0;
}


int Plant::setLocation ( std::vector<int> newLocation )
{
    if ( newLocation.size() != 3 )
        return -1;

    location = newLocation;

    return 0;
}

std::vector<int> Plant::getLocation()
{
    return location;
}
