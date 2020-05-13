#ifndef __U_LOADLEVEL_H_INCLUDED__
#define __U_LOADLEVEL_H_INCLUDED__

#include <iostream>
#include <unistd.h>
#include "MAP/MAP_level0.h"

using namespace std;

int loadMAP()
{
    cout << level0.size() << endl;
    int count0 = 0;
    int count255 = 255;
    
    for (int i=0; i < level0.size(); ++i){
        if (level0[i] == 0 || level0[i] == 1)
            count0++;
        
        if (level0[i] == 255)
            count255++;
    }
    
    cout << count0 << endl;
    cout << count255 << endl;
    
    return 0;
}

#endif // __U_LOADLEVEL_H_INCLUDED__
