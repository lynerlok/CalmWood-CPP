#include <unistd.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

#include <UnigineGame.h>
#include <UnigineControls.h>
#include <UnigineConsole.h>
#include <UnigineRender.h>
#include <UnigineWorld.h>

#include "../SMA/U_randomGenerator.hpp"
#include "../SMA/C_animal.hpp"
#include "../SMA/C_plant.hpp"
#include "../SMA/C_environment.hpp"

#include "../ComponentSystem/ComponentSystem.h"

#include "GC_environment.hpp"
#include "GC_animal.hpp"
#include "GC_plant.hpp"

using namespace std;

REGISTER_COMPONENT ( GEnvironment );

void GEnvironment::init()
{

        cout << "GEnvironment initialization" << endl;

        vector<int> location = {0,0,0};
        vector<float> direction = { 0.0f, 0.0f, 0.0f };

        const unsigned int mapLength = environment.getMapLength();

        auto initAnimals = [&] ( Environment * environment ) {
                vector<Animal *> newAnimals = { new Leucorrhinia() }; //, new Hyla(), new Phengaris(), new Zootoca(), new Vipera() };

                for ( int animal = 0; animal < newAnimals.size(); ++animal ) {

                        meshPathStr = "animals_assets/" + ( *newAnimals[animal] ).getName() + "_MESH.mesh" ;
                        meshPathConst = meshPathStr.c_str();

                        temporaryMesh = ObjectMeshStatic::create ( meshPathConst );

                        for ( int i = 0; i < 3; ++i ) {

                                location[i] = runRNG ( 0,mapLength-1 );
                        }

                        direction = getDirection ( -180,180 );

                        temporaryMesh->setPosition ( Vec3 ( ( float ) location[0], ( float ) location[1], ( float ) location[2] ) );
                        ( *newAnimals[animal] ).setLocation ( location );

                        temporaryMesh->setDirection ( Vec3 ( direction[0], direction[1], direction[2] ), Vec3 ( 0.0f,0.0f,1.0f ) );

                        ComponentSystem::get()->addComponent<GAnimal> ( temporaryMesh );

                        temporaryMesh->getProperty()->getParameterPtr ( "id" )->setValue ( ( *newAnimals[animal] ).getID() );
                        ComponentSystem::get()->getComponent<GAnimal> ( temporaryMesh )->setAnimal ( newAnimals[animal] );

                        ( *environment ).getCell ( location[0],location[1] )->addAnimal ( ( *newAnimals[animal] ).getID(), newAnimals[animal] );

                        animalMesh.push_back ( temporaryMesh );

                }

        };

        auto initPlants = [&] ( Environment * environment ) {
//                 vector<Plant *> newPlants = { new Gentiania(), new Juncus(), new Glyceria(), new Carex(), new Iris() };
//
//                 for ( int plant = 0; plant < newPlants.size(); ++plant ) {
//
//                         for ( int i = 0; i < 3; ++i ) {
//                                 location[i] = runRNG ( 0,mapLength-1 );
//                         }
//
//                         ( *newPlants[plant] ).setLocation ( location );
//                         ( *environment ).getCell ( location[0],location[1] )->addPlant ( ( *newPlants[plant] ).getID(), newPlants[plant] );
//
//                         ( *plants ).push_back ( newPlants[plant] );
//                 }

        };

        for ( int agent=0; agent < MaxNumberAgent; ++agent ) {
                initAnimals ( &environment );
        }

        for ( int agent=0; agent < PlantDensity; ++agent ) {
                initPlants ( &environment );
        }

        runShuffle ( &animalMesh );

        agent = animalMesh.begin();
        // runShuffle ( &animals ); // Shuffle the GUI static mesh because the animal is accessible.
        //  runShuffle ( &plants );

        environment.setEnvironmentParameters ( 25,0.5,0.7 );
}

void GEnvironment::update ( float ifps )
{
        ifps = Game::getIFps();

        if ( simulationEnd == false ) {

                if ( agent == animalMesh.end() )
                        agent = animalMesh.begin();

                agentNumber = runRNG ( 0,animalMesh.size()-1 );

                animal = ComponentSystem::get()->getComponent<GAnimal> ( *agent );

                if ( runTime < 0.0f ) {

                        animal->run ( &environment );

                        if ( animal->isDead() ) {
                                deadCount += 1;
                                agent = animalMesh.erase ( agent );
                                --agent;
                                if ( agent <= animalMesh.begin() )
                                        simulationEnd = true;

                        } else if ( animal->isSpawn() && runRNG ( 0,100 ) < animal->getSpawnProbability() ) {
                                spawnCount += 1;
                                spawn ( animal );
                        }

                        environment.setTimeOfDay ( ( environment.getTimeOfDay() + AddDayTime ) % 24 );
                        runTime = RunDuration;
                }

                if ( simulationTime < 0.0f ) {
                        Log::message ( "SIMULATION ENDING...\n" );
                        simulationEnd = true;
                }

                if ( monthTime < 0.0f ) {
                        environment.setMonth ( ( environment.getMonth() + 1 ) % 12 );
                        monthTime = MonthDuration;
                }

                runTime -= ifps;
                simulationTime -= ifps;
                monthTime -= ifps;
                agent++;
        }

}

void GEnvironment::shutdown()
{

        cout << "Some statistics on the simulation" << endl;

        cout << "Number of death ( animals ) : " << deadCount << endl;
        cout << "Number of birth ( animals ) : " << spawnCount << endl;

        cout << "Number of Leucorrhinia at simulation start : " << MaxNumberAgent << endl;

        int LeucorrhiniaCount = 0;

        for ( agent = animalMesh.begin(); agent != animalMesh.end() ; ++agent )
                if ( ComponentSystem::get()->getComponent<GAnimal> ( *agent )->getProperty()->getParameterPtr ( "id" )->getValueInt() == 0 )
                        LeucorrhiniaCount++;

        cout << "Number of Leucorrhinia at the end : " << LeucorrhiniaCount << endl;

        cout << "Temperature at the end of the simulation : " << environment.getEnvironmentParameters() [0] << endl;

        cout << "Hygrometry at the end of the simulation : " << environment.getEnvironmentParameters() [1] << endl;

        cout << "Antrhopization at the end of the simulation : " << environment.getEnvironmentParameters() [2] << endl;

        animalMesh.clear();
}

int GEnvironment::spawn ( GAnimal * animal )
{
//         Animal * newAnimal;
//         vector<int> spawnLocation = animal->getLocation();
//
//         switch ( animal->getID() ) {
//         case 0 :
//                 newAnimal = new Leucorrhinia ( 0, "Leucorrhinia", {1,24,1}, {0,0,0,100,1,20}, {1,1,2}, {1,1,1}, true );
//                 break;
//         case 1 :
//                 newAnimal = new Hyla();
//                 break;
//         case 2 :
//                 newAnimal = new Phengaris();
//                 break;
//         case 3 :
//                 newAnimal = new Zootoca();
//                 break;
//         case 4 :
//                 newAnimal = new Vipera();
//                 break;
//         }
//
//         newAnimal->setLocation ( spawnLocation );
//         environment.getCell ( spawnLocation[0],spawnLocation[1] )->addAnimal ( newAnimal->getID(), newAnimal );
//
//         animals.push_back ( newAnimal );
//
//         animal->setSpawnAbility ( false );
//
//         runShuffle ( &animals );

        return 0;
}

int GEnvironment::triggerSimulationEnd()
{
        simulationEnd = true;
        return 0;
}



