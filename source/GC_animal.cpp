#include <unistd.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

#include <UnigineGame.h>
#include <UnigineControls.h>
#include <UnigineConsole.h>
#include <UnigineRender.h>

#include "ComponentSystem/ComponentSystem.h"

#include "C_animal.hpp"
#include "GC_animal.hpp"

REGISTER_COMPONENT ( GAnimal );

void GAnimal::init()
{
}

void GAnimal::update() {}

void GAnimal::shutdown()
{
}

int GAnimal::setAnimal ( Animal* newAnimal )
{
        animal = newAnimal;
        return 0;
}
