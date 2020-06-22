#include <unistd.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

#include <Unigine.h>
#include <UnigineGame.h>
#include <UnigineControls.h>
#include <UnigineConsole.h>
#include <UnigineRender.h>
#include "C_plant.hpp"

#include "ComponentSystem/ComponentSystem.h"

#include "GC_plant.hpp"

REGISTER_COMPONENT( GPlant );

void GPlant::init(){
    Log::message("PLANT: INIT \"%s\"\n", name.get());
}

void GPlant::update(){}

void GPlant::shutdown(){
    Log::message("PLANT : DEAD !\n");
}
