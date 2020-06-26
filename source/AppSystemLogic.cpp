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
#include "GraphicalClass/GC_environment.hpp"

#include "AppSystemLogic.h"
#include "AppWorldLogic.h"

using namespace std;
using namespace Unigine;
using namespace Math;

// System logic, it exists during the application life cycle.
// These methods are called right after corresponding system script's (UnigineScript) methods.

AppSystemLogic::AppSystemLogic()
{
}

AppSystemLogic::~AppSystemLogic()
{
}

int AppSystemLogic::init()
{
        // Write here code to be called on engine initialization.

        cout << "Init system" << endl;
        ComponentSystem::get()->initialize();

        // ComponentSystem::get()->addComponent<GEnvironment> ( World::getNodeByName ( "EnvironmentSimulation" ) );

        return 1;
}

////////////////////////////////////////////////////////////////////////////////
// start of the main loop
////////////////////////////////////////////////////////////////////////////////

int AppSystemLogic::update()
{
        // Write here code to be called before updating each render frame.
        return 1;
}

int AppSystemLogic::postUpdate()
{
        // Write here code to be called after updating each render frame.
        return 1;
}

////////////////////////////////////////////////////////////////////////////////
// end of the main loop
////////////////////////////////////////////////////////////////////////////////

int AppSystemLogic::shutdown()
{
        // Write here code to be called on engine shutdown.
        return 1;
}

