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

void GAnimal::init() {}

void GAnimal::update()
{

        ifps = Game::getIFps();

        move ( ifps );

}

void GAnimal::shutdown()
{
        delete animal;
}

int GAnimal::setAnimal ( Animal* newAnimal )
{
        animal = newAnimal;
        oldHook = animal->getLocation();
        return 0;
}

int GAnimal::run ( Environment* environment )
{
        animal->run ( environment );
        return 0;
}

int GAnimal::move ( float ifps )
{
        // angle = ( float ) runRNG ( -180,180 );

        hook = animal->getLocation();

//         if ( ( hook[0] != oldHook[0] ) || ( hook[1] != oldHook[1] ) ) {
//                 cout << " X : " << oldHook[0] << " | " << hook[0] << endl;
//                 cout << " Y : " << oldHook[1] << " | " << hook[1] << endl;
//         }

        if ( ( hook[0] != oldHook[0] ) && ( hook[1] != oldHook[1] ) ) {

                changeHook = true;

                X = node->getWorldPosition().x;
                Y = node->getWorldPosition().y;

                if ( ( X < hook[0] ) && ( Y < hook[1] ) ) {

                        node->setWorldPosition ( node->getWorldPosition() + Unigine::Math::Vec3 ( 0.1, 0.1, 0 ) * 100 * ifps );

                } else if ( ( X < hook[0] ) && ( Y > hook[1] ) ) {

                        node->setWorldPosition ( node->getWorldPosition() + Unigine::Math::Vec3 ( 0.1, -0.1, 0 ) * 100 * ifps );

                } else if ( ( X > hook[0] ) && ( Y < hook[1] ) ) {

                        node->setWorldPosition ( node->getWorldPosition() + Unigine::Math::Vec3 ( -0.1, 0.1, 0 ) * 100 * ifps );

                } else if ( ( X > hook[0] ) && ( Y > hook[1] ) ) {

                        node->setWorldPosition ( node->getWorldPosition() + Unigine::Math::Vec3 ( -0.1, -0.1, 0 ) * 100 * ifps );

                } else if ( ( X == hook[0] ) && ( Y < hook[1] ) ) {

                        node->setWorldPosition ( node->getWorldPosition() + Unigine::Math::Vec3 ( 0, 0.1, 0 ) * 100 * ifps );

                } else if ( ( X == hook[0] ) && ( Y > hook[1] ) ) {

                        node->setWorldPosition ( node->getWorldPosition() + Unigine::Math::Vec3 ( 0, -0.1, 0 ) * 100 * ifps );

                } else if ( ( X > hook[0] ) && ( Y == hook[1] ) ) {

                        node->setWorldPosition ( node->getWorldPosition() + Unigine::Math::Vec3 ( -0.1, 0, 0 ) * 100 * ifps );

                } else if ( ( X < hook[0] ) && ( Y == hook[1] ) ) {

                        node->setWorldPosition ( node->getWorldPosition() + Unigine::Math::Vec3 ( 0.1, 0, 0 ) * 100 * ifps );

                }
                return 0;
        }

        if ( ( hook[0] == oldHook[0] ) && ( hook[1] == oldHook[1] ) )
                oldHook = hook;

        changeHook = false;

//         Math::Mat4 tranform = node->getTransform();
//         Math::Vec3 forward_direction = tranform.getColumn3 ( 1 );
//
//         Vec3 forward = node->getWorldPosition() + forward_direction * movement_speed * ifps;
//
//       //  for ( int i = 0; i < 3 ; ++i )
//        //         angle = forward[i] >= location[i]+1 ? angle = -180.0f : angle;
//
//         Math::quat delta_rotation = Math::quat ( 0.0f, 0.0f, 1.0f, angle * ifps );
//
//         node->setWorldPosition ( node->getWorldPosition() + forward_direction * movement_speed * ifps );
//         node->setWorldRotation ( node->getWorldRotation() * delta_rotation );

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


