#include <unistd.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

#include "C_plant.hpp"
#include "C_environment.hpp"

Plant::Plant ( int newId, std::string newName )
{
        id = newId;
        name = newName;
        
};

Plant::~Plant () {};

int Plant::getID()
{
        return id;
}

std::string Plant::getName()
{
    return name;
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

int Plant::dead ( Environment* environment )
{
        environment->getCell ( location[0], location[1] )->removePlant ( id, this );
        death = true;

        return 0;
}

bool Plant::isDead()
{
    return death;
}

