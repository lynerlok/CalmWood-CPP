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
        // /!\ REWORK !!!!

        angle = ( float ) runRNG ( -180,180 );

        hook = animal->getLocation();

        if ( hook != oldHook ) {

        }

        Math::Mat4 tranform = node->getTransform();
        Math::Vec3 forward_direction = tranform.getColumn3 ( 1 );

        Vec3 forward = node->getWorldPosition() + forward_direction * movement_speed * ifps;

//         for ( int i = 0; i < 3 ; ++i )
//                 angle = forward[i] >= location[i]+1 ? angle = -180.0f : angle;

        Math::quat delta_rotation = Math::quat ( 0.0f, 0.0f, 1.0f, angle * ifps );

        node->setWorldPosition ( node->getWorldPosition() + forward_direction * movement_speed * ifps );
        node->setWorldRotation ( node->getWorldRotation() * delta_rotation );

        return 0;
}

// void missiletargettracking2()
// {
// 
//         if ( ( unigineNodes.mObject->getWorldPosition().x < uparameters.mmissilehtstargetpoint.x+1.2 ) && ( unigineNodes.mMissileKornetLeft->getWorldPosition().y < uparameters.mmissilehtstargetpoint.y + 1.2 ) ) {
//                 unigineNodes.mObject->setWorldPosition ( unigineNodes.mObject->getWorldPosition()+Unigine::Math::Vec3 ( 0.1,0.1,0 ) * parameters.mMissileTrackingSpeed*Unigine::Game::get()->getIFps() );
//         }
// 
//         else if ( ( unigineNodes.mObject->getWorldPosition().x < uparameters.mmissilehtstargetpoint.x +1.2 ) && ( unigineNodes.mObject->getWorldPosition().y > uparameters.mmissilehtstargetpoint.y + 1.2 ) ) {
//                 unigineNodes.mObject->setWorldPosition ( unigineNodes.mObject->getWorldPosition()+Unigine::Math::Vec3 ( 0.1,-0.1,0 ) * parameters.mMissileTrackingSpeed*Unigine::Game::get()->getIFps() );
//         }
// 
//         else if ( ( unigineNodes.mObject->getWorldPosition().x > uparameters.mmissilehtstargetpoint.x -1.2 ) && ( unigineNodes.mObject->getWorldPosition().y < uparameters.mmissilehtstargetpoint.y - 1.2 ) ) {
//                 unigineNodes.mObject->setWorldPosition ( unigineNodes.mObject->getWorldPosition()+Unigine::Math::Vec3 ( -0.1,0.1,0 ) * parameters.mMissileTrackingSpeed * Unigine::Game::get()->getIFps() );
//         }
// 
//         else if ( ( unigineNodes.mObject->getWorldPosition().x > uparameters.mmissilehtstargetpoint.x- 1.2 ) && ( unigineNodes.mObject->getWorldPosition().y > uparameters.mmissilehtstargetpoint.y - 1.2 ) ) {
//                 unigineNodes.mObject->setWorldPosition ( unigineNodes.mObject->getWorldPosition()+Unigine::Math::Vec3 ( -0.1,-0.1,0 ) * parameters.mMissileTrackingSpeed * Unigine::Game::get()->getIFps() );
//         }
//         qDebug() << "Object position " << unigineNodes.mObject->getWorldPosition().x << unigineNodes.mObject->getWorldPosition().y << unigineNodes.mObject->getWorldPosition().z;
// 
// }

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


