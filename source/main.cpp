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

#include "U_randomGenerator.hpp"
#include "C_animal.hpp"
#include "C_plant.hpp"
#include "C_environment.hpp"

#include "ComponentSystem/ComponentSystem.h"

#include "GC_animal.hpp"
#include "GC_environment.hpp"

#include "AppEditorLogic.h"
#include "AppSystemLogic.h"
#include "AppWorldLogic.h"

using namespace Unigine;
using namespace Math;

#ifdef _WIN32
int wmain ( int argc, wchar_t *argv[] )
#else
int main ( int argc, char *argv[] )
#endif
{
        // UnigineLogic
        AppSystemLogic system_logic;
        AppWorldLogic world_logic;
        AppEditorLogic editor_logic;
        
       // system_logic.worldlogic_ptr = &world_logic;
       // world_logic.systemlogic_ptr = &system_logic;
        
        // init engine
        Unigine::EnginePtr engine ( UNIGINE_VERSION, argc, argv );

        // enter main loop
        engine->main ( &system_logic, &world_logic, &editor_logic );

        return 0;
}

#ifdef _WIN32
#include <Windows.h>
extern "C" __declspec ( dllexport ) DWORD NvOptimusEnablement = 0x00000001;
extern "C" __declspec ( dllexport ) int AmdPowerXpressRequestHighPerformance = 1;
#endif