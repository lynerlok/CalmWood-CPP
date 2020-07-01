/* Copyright (C) 2005-2020, UNIGINE. All rights reserved.
 *
 * This file is a part of the UNIGINE 2.11.0.1 SDK.
 *
 * Your use and / or redistribution of this software in source and / or
 * binary form, with or without modification, is subject to: (i) your
 * ongoing acceptance of and compliance with the terms and conditions of
 * the UNIGINE License Agreement; and (ii) your inclusion of this notice
 * in any version of this software that you use or redistribute.
 * A copy of the UNIGINE License Agreement is available by contacting
 * UNIGINE. at http://unigine.com/
 */

#include <unistd.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

#include <UnigineApp.h>
#include <UnigineConsole.h>
#include <UnigineEngine.h>
#include <UnigineEditor.h>
#include <UnigineGame.h>
#include <UnigineLights.h>
#include <UnigineLogic.h>
#include <UnigineWorld.h>
#include <UnigineGui.h>
#include <UnigineWidgets.h>
#include <UnigineEngine.h>
#include <UnigineStreams.h>

#include "SMA/U_randomGenerator.hpp"
#include "SMA/C_animal.hpp"
#include "SMA/C_plant.hpp"
#include "SMA/C_environment.hpp"

#include "ComponentSystem/ComponentSystem.h"

#include "GraphicalClass/GC_animal.hpp"
#include "GraphicalClass/GC_plant.hpp"

#include "AppWorldLogic.h"
#include "AppSystemLogic.h"

using namespace Unigine;
using namespace Math;
using namespace std;

// World logic, it takes effect only when the world is loaded.
// These methods are called right after corresponding world script's (UnigineScript) methods.

// define the movement speed
float movement_speed = 5.0f;

AppWorldLogic::AppWorldLogic()
{
}

AppWorldLogic::~AppWorldLogic()
{
}

int AppWorldLogic::init()
{
        // Write here code to be called on world initialization: initialize resources for your world scene during the world start.

        cout << "Init world" << endl;
        label = WidgetLabel::create ( Gui::get() );
        label->setPosition ( 10, 10 );
        label->setFontSize ( 24 );
        label->setFontOutline ( 1 );
        Gui::get()->addChild ( label, Gui::ALIGN_OVERLAP );

        animals = systemlogic_ptr->animals;
        plants = systemlogic_ptr->plants;

        for ( agentAnimal = animals.begin(); agentAnimal != animals.end(); ++agentAnimal )
                createAnimal ( ( * agentAnimal ) );

        return 1;
}

////////////////////////////////////////////////////////////////////////////////
// start of the main loop
////////////////////////////////////////////////////////////////////////////////

int AppWorldLogic::update()
{
        // Write here code to be called before updating each render frame: specify all graphics-related functions you want to be called every frame while your application executes.

        // show game info
        label->setText ( String::format (
                                 "Components: %d",
                                 ComponentSystem::get()->getNumComponents() ).get() );


        ifps = Game::getIFps();

        return 1;
}

int AppWorldLogic::postUpdate()
{
        // The engine calls this function after updating each render frame: correct behavior after the state of the node has been updated.
        return 1;
}

int AppWorldLogic::updatePhysics()
{
        // Write here code to be called before updating each physics frame: control physics in your application and put non-rendering calculations.
        // The engine calls updatePhysics() with the fixed rate (60 times per second by default) regardless of the FPS value.
        // WARNING: do not create, delete or change transformations of nodes here, because rendering is already in progress.
        return 1;
}

////////////////////////////////////////////////////////////////////////////////
// end of the main loop
////////////////////////////////////////////////////////////////////////////////

int AppWorldLogic::shutdown()
{
        // Write here code to be called on world shutdown: delete resources that were created during world script execution to avoid memory leaks.
        return 1;
}

int AppWorldLogic::save ( const Unigine::StreamPtr &stream )
{
        // Write here code to be called when the world is saving its state (i.e. state_save is called): save custom user data to a file.
        UNIGINE_UNUSED ( stream );
        return 1;
}

int AppWorldLogic::restore ( const Unigine::StreamPtr &stream )
{
        // Write here code to be called when the world is restoring its state (i.e. state_restore is called): restore custom user data to a file here.
        UNIGINE_UNUSED ( stream );
        return 1;
}

Unigine::ObjectMeshDynamicPtr AppWorldLogic::create_box ( const Unigine::Math::Mat4& transform, const Unigine::Math::vec3& size )
{
        MeshPtr mesh = Mesh::create();
        mesh->addBoxSurface ( "box", size );

        ObjectMeshDynamicPtr object = ObjectMeshDynamic::create ( 1 );
        object->setMesh ( mesh );
        object->setWorldTransform ( transform );
        object->setMaterial ( "mesh_base", "*" );

        return object;
}

int AppWorldLogic::createAnimal ( Animal * animal )
{

        if ( animal->getGrowthState() == 2 ) {

                meshPathStr = "animals_assets/" + animal->getName() + "_MESH.mesh" ;
                meshPathConst = meshPathStr.c_str();

                temporaryMesh = ObjectMeshStatic::create ( meshPathConst );

                direction = runRNG ( -180,180 );

                agentLocation = animal->getLocation();

                temporaryMesh->setPosition ( Vec3 ( ( float ) agentLocation[0], ( float ) agentLocation[1], getFloat ( 1, 3 ) ) );

                temporaryMesh->setDirection ( Vec3 ( 0.0f, 0.0f, static_cast<float> ( direction ) ), Vec3 ( 0.0f,0.0f,1.0f ) );

                ComponentSystem::get()->addComponent<GAnimal> ( temporaryMesh );

                temporaryMesh->getProperty()->getParameterPtr ( "id" )->setValue ( animal->getID() );
                ComponentSystem::get()->getComponent<GAnimal> ( temporaryMesh )->setAnimal ( animal );

                animalMesh.push_back ( temporaryMesh );

        }

        return 0;
}

// int AppWorldLogic::spawn ( Animal * animal )
// {
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
//
//     return 0;
// }
