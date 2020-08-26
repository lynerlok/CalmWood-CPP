#ifndef __C_PLANTS_H_INCLUDED__
#define __C_PLANTS_H_INCLUDED__

class Environment;

class Plant
{
public:
    Plant ( int newId = 0, std::string newName = "default" );
    ~Plant ();

    int getID();
    std::string getName();

    int growth ( int targetState );
    int damage();

    int setLocation ( std::vector<int> newLocation );
    std::vector <int> getLocation();
    
    int dead(Environment * environment);
    bool isDead();

protected :
    int id=0;
    std::string name;

    bool death = false;
    std::vector <int> location{0,0,0};

};

class Gentiania: public Plant
{
public :
    Gentiania ( int id = 0 ) :Plant ( id ) {}
};

class Juncus: public Plant
{
public :
    Juncus ( int id = 1 ) :Plant ( id ) {}
};

class Glyceria: public Plant
{
public :
    Glyceria ( int id = 2 ) :Plant ( id ) {}
};

class Carex: public Plant
{
public :
    Carex ( int id = 3 ) :Plant ( id ) {}
};

class Iris: public Plant
{
public :
    Iris ( int id = 4 ) :Plant ( id ) {}
};


#endif // __C_PLANTS_H_INCLUDED__

