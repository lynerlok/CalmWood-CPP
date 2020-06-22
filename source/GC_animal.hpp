#ifndef __GC_ANIMAL_H_INCLUDED__
#define __GC_ANIMAL_H_INCLUDED__

using namespace Unigine;
using namespace Math;

class Animal;

class GAnimal : public ComponentBase
{
public :
    COMPONENT(GAnimal, ComponentBase);
    
    COMPONENT_INIT(init);
    COMPONENT_UPDATE(update);
    COMPONENT_SHUTDOWN(shutdown);
    
    PROP_NAME("animal");
    
    PROP_PARAM(Int, id, 99);
    
    int setAnimal( Animal *newAnimal );
    
protected :
    
    Animal *animal;

    void init();
    void update();
    void shutdown();

};

#endif // __GC_ANIMAL_H_INCLUDED__
