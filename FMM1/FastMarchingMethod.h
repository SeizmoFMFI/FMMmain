//
//  FastMarchingMethod.h
//  FastMarchingMethod
//
//  Created by fimi on 30/09/14.
//  Copyright (c) 2014 Filip Michlik. All rights reserved.
//

#ifndef __FastMarchingMethod__FastMarchingMethod__
#define __FastMarchingMethod__FastMarchingMethod__

#include <iostream>

#include "VelocityModel.h"


struct GridPosition
{
    int x, y, z;
    
    GridPosition(int a,int b, int c):x(a), y(b), z(c) {};
};


class FastMarchingMethod
{
public:
    FastMarchingMethod(VelocityModel *vm, GridPosition *source);
    ~FastMarchingMethod();
    
    VelocityModel*  const   model;
    Dimension*      const   dimension;
    GridPosition*   const   sourcePosition;   //point from which the wavefront spreads
    float***        const   traveltimes;
    //float           *wavefront;         //heap???
    int             pointsProcessed;    //counter of points in which traveltimes are already calculated
    
    void        calculateTraveltimes();
    void        spreadWavefrontToNextGridPoint();
    int         modelPointsCount;
    
private:
    void    init();
};

#endif /* defined(__FastMarchingMethod__FastMarchingMethod__) */
