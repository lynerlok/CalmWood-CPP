#include <unistd.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>

#include "../3rdParty/tinyxml/tinyxml2.h"

#include "U_randomGenerator.hpp"
#include "C_animal.hpp"
#include "C_plant.hpp"
#include "C_environment.hpp"

using namespace tinyxml2;

Cell::Cell ( int newX, int newY )
{
        X = newX;
        Y = newY;
};

Cell::~Cell()
{
        AnimalCellContent.clear();
        PlantCellContent.clear();
};

int Cell::setViability ( bool newViability )
{
        viability = newViability;
        return 0;

}

bool Cell::getViabilityBoolean()
{
        return viability;
}

int Cell::addAnimal ( int ID, Animal * animal )
{

        AnimalCellContent.emplace ( ID,animal );

        return 0;
}

int Cell::addPlant ( int ID, Plant * plant )
{
        PlantCellContent.emplace ( std::make_pair ( ID,plant ) );

        return 0;
}

int Cell::removeAnimal ( int ID, Animal * animal )
{

        Aumit it = AnimalCellContent.begin();

        for ( it ; it != AnimalCellContent.end(); it++ ) {
                if ( ( it->second ) == animal ) {
                        AnimalCellContent.erase ( it );
                        break;
                }
        }

        return 0;
}

int Cell::removePlant ( int ID, Plant * plant )
{
        Pumit it = PlantCellContent.begin();

        for ( it ; it != PlantCellContent.end(); it++ ) {
                if ( ( it->second ) == plant ) {
                        PlantCellContent.erase ( it );
                        break;
                }
        }

        return 0;
}

std::unordered_multimap<int, Animal *> Cell::getCellContentAnimals()
{
        return AnimalCellContent;
}

std::unordered_multimap<int, Plant *> Cell::getCellContentPlants()
{
        return PlantCellContent;
}

std::vector<int> Cell::getCellContentSpecs()
{
        return {viability,containTrees,containAnthropization,containWetland,X,Y};
}

int Cell::toggleTrees()
{
        containTrees = ! containTrees;
        return 0;
}

int Cell::toggleAnthropization()
{
        containAnthropization = ! containAnthropization;
        return 0;
}

int Cell::toggleWetland()
{
        containWetland = ! containWetland;
        return 0;
}

Environment::Environment()
{
        mapParser("level1");
        
        for ( int x=0; x<mapLength; ++x )
                for ( int y=0; y<mapLength; ++y )
                        map[x].push_back ( new Cell ( x,y ) );
}

Environment::~Environment()
{
        for ( int x=0; x<mapLength; ++x )
                for ( int y=0; y<mapLength; ++y )
                        delete ( map[x][y] );
}

int Environment::setTemperature ( float newTemperature )
{
        temperature = newTemperature;
        return 0;
}

int Environment::setHygrometry ( float newHygrometry )
{
        if ( newHygrometry < 0 || newHygrometry > 1.0 ) {
                std::cout << "[DEBUG] hygrometry percentage value between 0 and 1" << std::endl;
                return -1;
        }
        hygrometry = newHygrometry;
        return 0;
}

int Environment::setAntropization ( float newAntropizationRate )
{

        if ( newAntropizationRate < 0 || newAntropizationRate > 1.0 ) {
                std::cout << "[DEBUG] antropizationRate are percentage value between 0 and 1" << std::endl;
                return -1;
        }

        antropizationRate = newAntropizationRate;

        return 0;
}

int Environment::setEnvironmentParameters ( float newTemperature,
                float newHygrometry,
                float newAntropizationRate )
{

        if ( newHygrometry < 0.0 || newHygrometry > 1.0 ||
                        newAntropizationRate < 0.0 || newAntropizationRate > 1.0 ) {
                std::cout << "[DEBUG] hygrometry and antropizationRate are percentage value between 0 and 1" << std::endl;
                return -1;
        }

        temperature = newTemperature;
        hygrometry = newHygrometry;
        antropizationRate = newAntropizationRate;

        return 0;
}

unsigned int Environment::getTimeOfDay()
{
        return timeOfDay;
}

int Environment::setTimeOfDay ( unsigned int newTimeOfDay )
{
        timeOfDay = newTimeOfDay;
        return 0;
}

int Environment::setMonth ( unsigned int newMonthOfYear )
{
        monthOfYear = newMonthOfYear;
        return 0;
}

unsigned int Environment::getMonth()
{
        return monthOfYear;
}

unsigned int Environment::getOriginDayTime()
{
        return originTimeOfDay;
}

unsigned int Environment::getOriginMonth()
{
        return originMonth;
}

int Environment::setYear ( unsigned int newYear )
{
        yearOfSimulation = newYear;
        return 1;
}

unsigned int Environment::getYear()
{
        return yearOfSimulation;
}

unsigned int Environment::getOriginYear()
{
        return originYear;
}

std::vector<float> Environment::getEnvironmentParameters()
{

        std::vector<float> parameters {temperature,hygrometry,antropizationRate};

        return parameters;
}

const unsigned int Environment::getMapLength()
{
        return mapLength;
}

Cell * Environment::getCell ( int x, int y )
{
        return map[x][y];
}

int Environment::mapParser (std::string level)
{
        XMLDocument doc;
        std::string filename = "MAP_" + level + ".xml";
        std::string name;
        std::vector<int> cellParameters;

        XMLElement * attributesElement, * parametersElement, * cellsElement, * cellsParametersElement, * agentByTypeAnimal, * agentByTypePlant;

        doc.LoadFile ( filename.c_str() );

        attributesElement = doc.FirstChildElement()->FirstChildElement ( "attributes" );
        parametersElement = doc.FirstChildElement()->FirstChildElement ( "parameters" );
        cellsElement = doc.FirstChildElement()->FirstChildElement ( "cells" );
        cellsParametersElement = doc.FirstChildElement()->FirstChildElement ( "CellsParameters" );
        agentByTypeAnimal = parametersElement->FirstChildElement ( "maxnumberagentbytypeanimal" );
        agentByTypePlant = parametersElement->FirstChildElement ( "maxnumberagentbytypeplant" );

        mapContent.emplace ( "level", attributesElement->FirstChildElement ( "level" )->GetText() );
        mapContent.emplace ( "difficulty", attributesElement->FirstChildElement ( "difficulty" )->GetText() );

        temperature = std::stof ( parametersElement->FirstChildElement ( "temperature" )->GetText() );
        hygrometry = std::stof ( parametersElement->FirstChildElement ( "hygrometry" )->GetText() );
        mapLength = std::stoi ( parametersElement->FirstChildElement ( "mapLength" )->GetText() );
        timeOfDay = std::stoi ( parametersElement->FirstChildElement ( "timeOfDay" )->GetText() );
        monthOfYear = std::stoi ( parametersElement->FirstChildElement ( "monthOfYear" )->GetText() );
        yearOfSimulation = std::stoi ( parametersElement->FirstChildElement ( "year" )->GetText() );
        MaxNumberAgentAnimal = std::stoi ( parametersElement->FirstChildElement ( "maxnumberagentanimal" )->GetText() );
        MaxNumberAgentPlant = std::stoi ( parametersElement->FirstChildElement ( "maxnumberagentplant" )->GetText() );
        MaxDailyRun = std::stoi ( parametersElement->FirstChildElement ( "maxdailyrun" )->GetText() );
        MaxDayMonth = std::stoi ( parametersElement->FirstChildElement ( "maxdaymonth" )->GetText() );
        MaxTimeSimulation = std::stoi ( parametersElement->FirstChildElement ( "maxtimesimulation" )->GetText() );
        RunDuration = std::stoi ( parametersElement->FirstChildElement ( "runduration" )->GetText() );

        for ( XMLElement * agent = agentByTypeAnimal->FirstChildElement ( "value" ); agent != NULL; agent = agent->NextSiblingElement ( "value" ) )
                MaxNumberAgentByTypeAnimal.push_back ( std::stof(agent->GetText()) );
        
        for ( XMLElement * agent = agentByTypePlant->FirstChildElement ( "value" ); agent != NULL; agent = agent->NextSiblingElement ( "value" ) )
                MaxNumberAgentByTypePlant.push_back ( std::stof(agent->GetText()) );
        
        for ( XMLElement * cell = cellsElement->FirstChildElement ( "cell" ); cell != NULL; cell = cell->NextSiblingElement ( "cell" ) )
                mapCells.push_back ( cell->FirstChildElement()->GetText() );

        for ( XMLElement * cell = cellsParametersElement->FirstChildElement ( "Cell" ); cell != NULL; cell = cell->NextSiblingElement ( "Cell" ) ) {
                name = cell->FirstChildElement ( "name" )->GetText();
                cellParameters.push_back ( std::stoi ( cell->FirstChildElement ( "surface" )->GetText() ) );
                cellParameters.push_back ( std::stoi ( cell->FirstChildElement ( "viability" )->GetText() ) );
                cellParameters.push_back ( std::stoi ( cell->FirstChildElement ( "trees" )->GetText() ) );
                cellParameters.push_back ( std::stoi ( cell->FirstChildElement ( "antropized" )->GetText() ) );
                cellParameters.push_back ( std::stoi ( cell->FirstChildElement ( "wetland" )->GetText() ) );
                cellParameters.push_back ( std::stoi ( cell->FirstChildElement ( "water" )->GetText() ) );
                cellParameters.push_back ( std::stoi ( cell->FirstChildElement ( "eutrophisation" )->GetText() ) );
                cellParameters.push_back ( std::stoi ( cell->FirstChildElement ( "waterPlantClosed" )->GetText() ) );
                cellParameters.push_back ( std::stoi ( cell->FirstChildElement ( "sunExposition" )->GetText() ) );
                mapCellsParameters.emplace ( name, cellParameters );
                cellParameters.clear();
        }

        return 0;
}
