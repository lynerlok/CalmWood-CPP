#ifndef __C_PLANTS_H_INCLUDED__
#define __C_PLANTS_H_INCLUDED__

class Plant
{
public:
    Plant ( int newId = 0 )
    {
        id = newId;
    };
    ~Plant () {};
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
