#include "headers/C_plants.hpp"

#include <iostream>

int Plants::getID()
{
    return id;
}

int Plants::growth ( int targetState )
{
    return 0;
}

int Plants::damage()
{
    return 0;
}


int Plants::setLocation ( std::vector<int> newLocation )
{
    if ( newLocation.size() != 3 )
        return -1;

    location = newLocation;

    return 0;
}

std::vector<int> Plants::getLocation()
{
    return location;
}
