//
//  VelocityModel.h
//  FastMarchingMethod
//
//  Created by fimi on 30/09/14.
//  Copyright (c) 2014 Filip Michlik. All rights reserved.
//

#ifndef __FastMarchingMethod__VelocityModel__
#define __FastMarchingMethod__VelocityModel__

#include <iostream>

struct Dimension
{
    int dx, dy, dz;
    
    Dimension(int x, int y, int z): dx(x), dy(y), dz(z) {};
};

class VelocityModel
{
public:
    VelocityModel(Dimension *d);
    ~VelocityModel();
    
    Dimension   *dimension;
    float       ***velocity;
    
    bool readModel(std::string pathToFile);
    
private:
    void init();
};

#endif /* defined(__FastMarchingMethod__VelocityModel__) */
