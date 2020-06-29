#include <unistd.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

#include <UnigineGame.h>
#include <UnigineEngine.h>
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

using namespace std;

REGISTER_COMPONENT ( GEnvironment );

void GEnvironment::init()
{  
}

void GEnvironment::update ()
{
   
}

void GEnvironment::shutdown()
{
}
