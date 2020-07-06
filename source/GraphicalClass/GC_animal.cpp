#include <unistd.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

#include <UnigineGame.h>
#include <UnigineControls.h>
#include <UnigineConsole.h>
#include <UnigineRender.h>

#include "../SMA/U_randomGenerator.hpp"
#include "../SMA/C_animal.hpp"
#include "../SMA/C_plant.hpp"
#include "../SMA/C_environment.hpp"

#include "../ComponentSystem/ComponentSystem.h"

#include "../SMA/C_animal.hpp"
#include "GC_animal.hpp"

using namespace std;

REGISTER_COMPONENT ( GAnimal );

void GAnimal::init()
{}

void GAnimal::update()
{

        ifps = Game::getIFps();

        if ( animal->isDead() )
                node.deleteLater();

        move ( ifps );

}

void GAnimal::shutdown()
{
        delete animal;
}

int GAnimal::setAnimal ( Animal* newAnimal )
{
        animal = newAnimal;
        return 0;
}

int GAnimal::run ( Environment* environment )
{
        animal->run ( environment );
        return 0;
}

int GAnimal::move ( float ifps )
{

        X = node->getWorldPosition().x;
        Y = node->getWorldPosition().y;

        coord = { static_cast <int> ( trunc ( X ) ), static_cast <int> ( trunc ( Y ) ) };

        if ( ! isMoving && animal->getOldLocation() != animal->getLocation() ) {
                animal->stopSimulation();
                isMoving = true;
                goal = animal->getLocation();

        } else {

                hook = animal->getLocation();

                angle = ( float ) runRNG ( -180,180 );

                Math::Mat4 tranform = node->getTransform();
                Math::Vec3 forward_direction = tranform.getColumn3 ( 1 );

                Vec3 forward = node->getWorldPosition() + forward_direction * movement_speed * ifps;

                if ( forward[0] >= hook[0]+1 || forward[1] >= hook[1]+1 || forward[0] <= hook[0]-1 || forward[1] <= hook[1]-1 )
                        angle = -180.0f;

                Math::quat delta_rotation = Math::quat ( 0.0f, 0.0f, 1.0f, angleMultiplicator * angle * ifps );

                node->setWorldPosition ( node->getWorldPosition() + forward_direction * movement_speed * ifps );
                node->setWorldRotation ( node->getWorldRotation() * delta_rotation );
        }

        if ( isMoving && coord != goal ) {

                if ( ( X < goal[0] ) && ( Y < goal[1] ) ) {

                        node->setWorldPosition ( node->getWorldPosition() + Unigine::Math::Vec3 ( 0.1, 0.1, 0 ) * movement_speed * ifps );

                } else if ( ( X < goal[0] ) && ( Y > goal[1] ) ) {

                        node->setWorldPosition ( node->getWorldPosition() + Unigine::Math::Vec3 ( 0.1, -0.1, 0 ) * movement_speed * ifps );

                } else if ( ( X > goal[0] ) && ( Y < goal[1] ) ) {

                        node->setWorldPosition ( node->getWorldPosition() + Unigine::Math::Vec3 ( -0.1, 0.1, 0 ) * movement_speed * ifps );

                } else if ( ( X > goal[0] ) && ( Y > goal[1] ) ) {

                        node->setWorldPosition ( node->getWorldPosition() + Unigine::Math::Vec3 ( -0.1, -0.1, 0 ) * movement_speed * ifps );

                } else if ( ( X == goal[0] ) && ( Y < goal[1] ) ) {

                        node->setWorldPosition ( node->getWorldPosition() + Unigine::Math::Vec3 ( 0, 0.1, 0 ) * movement_speed * ifps );

                } else if ( ( X == goal[0] ) && ( Y > goal[1] ) ) {

                        node->setWorldPosition ( node->getWorldPosition() + Unigine::Math::Vec3 ( 0, -0.1, 0 ) * movement_speed * ifps );

                } else if ( ( X > goal[0] ) && ( Y == goal[1] ) ) {

                        node->setWorldPosition ( node->getWorldPosition() + Unigine::Math::Vec3 ( -0.1, 0, 0 ) * movement_speed * ifps );

                } else if ( ( X < goal[0] ) && ( Y == goal[1] ) ) {

                        node->setWorldPosition ( node->getWorldPosition() + Unigine::Math::Vec3 ( 0.1, 0, 0 ) * movement_speed * ifps );

                }
        }

        if ( isMoving && coord == goal ) {
                isMoving = false;
                animal->setOldLocation ( goal );
                animal->continueSimulation();
        }

        return 0;
}

bool GAnimal::isDead()
{
        return animal->isDead();
}

bool GAnimal::isSpawn()
{
        return animal->isSpawn();
}

bool GAnimal::getSpawnProbability()
{
        return animal->getSpawnProbability();
}



