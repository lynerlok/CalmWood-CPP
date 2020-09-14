/* 
 * Copyright 2020 Axel Polin, univ_apolin@protonmail.com
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *   http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * 
*/
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

Cell::Cell ( int newX, int newY, std::string newName )
{
        X = newX;
        Y = newY;
        name = newName;
};

Cell::~Cell()
{
        AnimalCellContent.clear();
        PlantCellContent.clear();
};

bool Cell::getViabilityBoolean()
{
        return viability;
}

std::string Cell::getName()
{
        return name;
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

int Cell::setTrees ( int status )
{
        containTrees = status;
        return 0;
}

int Cell::setAnthropization ( int status )
{
        containAnthropization = status;
        return 0;
}

int Cell::setWetland ( int status )
{
        containWetland = status;
        return 0;
}

int Cell::setViability ( int status )
{
        viability = status;
        return 0;
}

int Cell::setWater ( int status )
{
        isWater = status;
        return 0;
}

int Cell::setRates ( std::vector<int> rates )
{
        if ( rates.size() != 3 ) {
                waterEutrophisationRate = 0;
                waterPlantClosedRate = 0;
                sunExpositionRate = 0;
                return 0;
        }

        waterEutrophisationRate = rates[0];
        waterPlantClosedRate = rates[1];
        sunExpositionRate = rates[2];

        return 0;
}


Environment::Environment()
{
        mapParser ( "level1" );

        std::string name;
        std::vector<int> values;

        std::cout << "Sucessfully parsing XML map" << std::endl;

        for ( int x=0; x<mapLength; ++x )
                for ( int y=0; y<mapLength; ++y ) {
                        try {
                                name = mapCells.at(x).at(y);
                                values = mapCellsParameters.at(name);
                        } catch ( const std::out_of_range& oor ) {
                                std::cerr << "Cell not found in xml file throw to default values" << oor.what() << '\n';
                                name = "default";
                        }
                        map[x].push_back ( new Cell ( x,y, name ) );
                        map[x][y]->setTrees(values[0]);
                        map[x][y]->setAnthropization(values[1]);
                        map[x][y]->setWetland(values[2]);
                        map[x][y]->setViability(values[3]);
                        map[x][y]->setWater(values[4]);
                        map[x][y]->setRates({values[5],values[6],values[7]});
                }

        std::cout << "Sucessfully creating virtual map" << std::endl;
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

int Environment::setAnthropization ( float newAnthropizationRate )
{

        if ( newAnthropizationRate < 0 || newAnthropizationRate > 1.0 ) {
                std::cout << "[DEBUG] anthropizationRate are percentage value between 0 and 1" << std::endl;
                return -1;
        }

        anthropizationRate = newAnthropizationRate;

        return 0;
}

int Environment::setEnvironmentParameters ( float newTemperature,
                float newHygrometry,
                float newAnthropizationRate )
{

        if ( newHygrometry < 0.0 || newHygrometry > 1.0 ||
                        newAnthropizationRate < 0.0 || newAnthropizationRate > 1.0 ) {
                std::cout << "[DEBUG] hygrometry and anthropizationRate are percentage value between 0 and 1" << std::endl;
                return -1;
        }

        temperature = newTemperature;
        hygrometry = newHygrometry;
        anthropizationRate = newAnthropizationRate;

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

        std::vector<float> parameters {temperature,hygrometry,anthropizationRate};

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

int Environment::mapParser ( std::string level )
{
        XMLDocument doc;
        std::string filename = "data/MAPs/MAP_" + level + ".xml";
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
        mapLength = mapLength > 300 ? 300 : mapLength;
        monthOfYear = std::stoi ( parametersElement->FirstChildElement ( "monthOfYear" )->GetText() );
        originMonth = monthOfYear;
        yearOfSimulation = std::stoi ( parametersElement->FirstChildElement ( "year" )->GetText() );
        originYear = yearOfSimulation;
        MaxNumberAgentAnimal = std::stoi ( parametersElement->FirstChildElement ( "maxnumberagentanimal" )->GetText() );
        MaxNumberAgentPlant = std::stoi ( parametersElement->FirstChildElement ( "maxnumberagentplant" )->GetText() );
        MaxAgentRun = std::stoi ( parametersElement->FirstChildElement ( "maxagentperrun" )->GetText() );
        MaxRunPerRunTime = std::stoi ( parametersElement->FirstChildElement ( "maxrunperruntime" )->GetText() );
        MaxRunTime = std::stoi ( parametersElement->FirstChildElement ( "maxruntime" )->GetText() );
        RunDuration = std::stof ( parametersElement->FirstChildElement ( "runduration" )->GetText() );
        timeType =  parametersElement->FirstChildElement ( "timetype" )->GetText();

        for ( XMLElement * agent = agentByTypeAnimal->FirstChildElement ( "value" ); agent != NULL; agent = agent->NextSiblingElement ( "value" ) )
                MaxNumberAgentByTypeAnimal.push_back ( std::stof ( agent->GetText() ) );

        for ( XMLElement * agent = agentByTypePlant->FirstChildElement ( "value" ); agent != NULL; agent = agent->NextSiblingElement ( "value" ) )
                MaxNumberAgentByTypePlant.push_back ( std::stof ( agent->GetText() ) );

        int cellCounterX = 0, cellCounterY = 0;

        for ( XMLElement * cell = cellsElement->FirstChildElement ( "cell" ); cell != NULL; cell = cell->NextSiblingElement ( "cell" ) ) {
                if ( cellCounterY >= mapLength ) {
                        cellCounterX += 1;
                        cellCounterY = 0;
                }
                mapCells[cellCounterX].push_back ( cell->FirstChildElement()->GetText() );
                ++cellCounterY;
        }

        for ( XMLElement * cell = cellsParametersElement->FirstChildElement ( "Cell" ); cell != NULL; cell = cell->NextSiblingElement ( "Cell" ) ) {
                name = cell->FirstChildElement ( "name" )->GetText();
                cellParameters.push_back ( std::stoi ( cell->FirstChildElement ( "trees" )->GetText() ) );
                cellParameters.push_back ( std::stoi ( cell->FirstChildElement ( "anthropized" )->GetText() ) );
                cellParameters.push_back ( std::stoi ( cell->FirstChildElement ( "wetland" )->GetText() ) );
                cellParameters.push_back ( std::stoi ( cell->FirstChildElement ( "viability" )->GetText() ) );
                cellParameters.push_back ( std::stoi ( cell->FirstChildElement ( "water" )->GetText() ) );
                cellParameters.push_back ( std::stoi ( cell->FirstChildElement ( "eutrophisation" )->GetText() ) );
                cellParameters.push_back ( std::stoi ( cell->FirstChildElement ( "waterPlantClosed" )->GetText() ) );
                cellParameters.push_back ( std::stoi ( cell->FirstChildElement ( "sunExposition" )->GetText() ) );
                cellParameters.push_back ( std::stoi ( cell->FirstChildElement ( "surface" )->GetText() ) );
                mapCellsParameters.emplace ( name, cellParameters );
                cellParameters.clear();
        }

        std::cout << "Data statistics :" << std::endl;
        for ( int i = 0 ; i < mapLength; ++i )
                for ( int j = 0 ; j < mapLength ; ++j )
                        std::cout << "Cell : " << mapCells[i][j] << std::endl;

        for ( int i = 0 ; i < MaxNumberAgentByTypeAnimal.size(); ++i )
                std::cout << "Animal (" << typeid ( MaxNumberAgentByTypeAnimal[i] ).name() << ") : " << MaxNumberAgentByTypeAnimal[i] << std::endl;

        for ( int i = 0 ; i < MaxNumberAgentByTypePlant.size(); ++i )
                std::cout << "Plant (" << typeid ( MaxNumberAgentByTypeAnimal[i] ).name() << ") : " << MaxNumberAgentByTypePlant[i] << std::endl;

        std::cout << "Level : " << mapContent.find ( "level" )->second << std::endl;
        std::cout << "Difficulty : " << mapContent.find ( "difficulty" )->second << std::endl;

        std::cout << "Temperature : " << temperature << std::endl;
        std::cout << "Hygrometry : " << hygrometry << std::endl;
        std::cout << "MapLength : " << mapLength << std::endl;
        std::cout << "Month : " << monthOfYear << std::endl;
        std::cout << "Year : " << yearOfSimulation << std::endl;
        std::cout << "Max number agent animal : " << MaxNumberAgentAnimal << std::endl;
        std::cout << "Max number agent plant : " << MaxNumberAgentPlant << std::endl;
        std::cout << "Max number agent per run : " << MaxAgentRun << std::endl;
        std::cout << "Max run per run time : " << MaxRunPerRunTime << std::endl;
        std::cout << "Max number of run : " << MaxRunTime << std::endl;
        std::cout << "Time type : " << timeType << std::endl;
        std::cout << "Run duration : " << RunDuration << std::endl;

        return 0;
}
