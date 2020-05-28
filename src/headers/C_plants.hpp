#ifndef __C_PLANTS_H_INCLUDED__
#define __C_PLANTS_H_INCLUDED__

#include <string>
#include <vector>

class Plants {
public:
    Plants(int newId = 0) {
        id = newId;
    };
    ~Plants(void) {};
    std::string name;

    int growth(int targetState);
    int damage();

protected :
    int id=0;

};

class Gentiania: public Plants {
public :
    Gentiania(int id = 0):Plants(id) {}
};

#endif // __C_PLANTS_H_INCLUDED__
