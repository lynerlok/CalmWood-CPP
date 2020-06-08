#ifndef __C_PLANTS_H_INCLUDED__
#define __C_PLANTS_H_INCLUDED__

#include <string>
#include <vector>

class Plants
{
public:
    Plants ( int newId = 0 )
    {
        id = newId;
    };
    ~Plants ( void ) {};
    std::string name;

    int getID();

    int growth ( int targetState );
    int damage();

    int setLocation ( std::vector<int> newLocation );
    std::vector <int> getLocation();

protected :
    int id=0;

    std::vector <int> location{0,0,0};

};

class Gentiania: public Plants
{
public :
    Gentiania ( int id = 0 ) :Plants ( id ) {}
};

class Juncus: public Plants
{
public :
    Juncus ( int id = 1 ) :Plants ( id ) {}
};

class Glyceria: public Plants
{
public :
    Glyceria ( int id = 2 ) :Plants ( id ) {}
};

class Carex: public Plants
{
public :
    Carex ( int id = 3 ) :Plants ( id ) {}
};

class Iris: public Plants
{
public :
    Iris ( int id = 4 ) :Plants ( id ) {}
};


#endif // __C_PLANTS_H_INCLUDED__
