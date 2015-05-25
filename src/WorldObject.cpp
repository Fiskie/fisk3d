//
//  worldobject.cpp
//  test
//
//  Created by Fiskie on 22/05/2015.
//  Copyright (c) 2015 Fiskie. All rights reserved.
//

#include <string.h>
#include "WorldObject.h"
#include <cstdarg>

using namespace std;

//missing string printf
//this is safe and convenient but not exactly efficient
inline std::string format(const char* fmt, ...){
    int size = 512;
    char* buffer = 0;
    buffer = new char[size];
    va_list vl;
    va_start(vl, fmt);
    int nsize = vsnprintf(buffer, size, fmt, vl);
    if(size<=nsize){ //fail delete buffer and try again
        delete[] buffer;
        buffer = 0;
        buffer = new char[nsize+1]; //+1 for /0
        nsize = vsnprintf(buffer, size, fmt, vl);
    }
    std::string ret(buffer);
    va_end(vl);
    delete[] buffer;
    return ret;
}

string WorldObject::posAsString() {
    return format("Loc (%.2f, %.2f, %.2f) Rot (%.2f, %.2f, %.2f) Vol (%.2f, %.2f, %.2f)",
            loc.x, loc.y, loc.z,
            rot.x, rot.y, rot.z,
            vol.x, vol.y, vol.z
    );
}