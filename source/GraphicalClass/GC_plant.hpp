#ifndef __GC_PLANT_H_INCLUDED__
#define __GC_PLANT_H_INCLUDED__

using namespace Unigine;
using namespace Math;

class GPlant : public ComponentBase
{
public :
    
    COMPONENT(GPlant, ComponentBase);
    
    COMPONENT_INIT(init);
    COMPONENT_UPDATE(update);
    COMPONENT_SHUTDOWN(shutdown);
    
    PROP_NAME("plant");
    
    PROP_PARAM(String, name, "Plant");
    
    Plant *plant;

protected :
    
    void init();
    void update();
    void shutdown();

};

#endif // __GC_PLANT_H_INCLUDED__
