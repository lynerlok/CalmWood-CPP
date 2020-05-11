#ifndef __C_PLANTS_H_INCLUDED__
#define __C_PLANTS_H_INCLUDED__

#include <string>
#include <vector>

class Plants {
public:
    Plants(void){};
    ~Plants(void){};
    std::string name;
    
    int growth(int targetState);
    int damage();
}; 

class Gentiania: public Plants {};

#endif // __C_PLANTS_H_INCLUDED__
