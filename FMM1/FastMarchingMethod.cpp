//
//  FastMarchingMethod.cpp
//  FastMarchingMethod
//
//  Created by fimi on 30/09/14.
//  Copyright (c) 2014 Filip Michlik. All rights reserved.
//

#include "FastMarchingMethod.h"

FastMarchingMethod::FastMarchingMethod(VelocityModel *vm, GridPosition *source):
model(vm), dimension(vm->dimension), sourcePosition(source), pointsProcessed(1), traveltimes(new float ** [dimension->dx])
{
    this->init();
}

FastMarchingMethod::~FastMarchingMethod()
{
    //delete wavefront;
    
    for (int i=0; i < this->dimension->dx; i++)
    {
        for (int j=0; j < this->dimension->dy; j++)
        {
            delete [] this->traveltimes[i][j];
        }
        
        delete [] this->traveltimes[i];
    }
    
    delete [] this->traveltimes;
}

void FastMarchingMethod::init()
{
    if (!dimension) {
        std::cerr << "Error (DIMENSION): Can not initialize instance of FastMarchingMethod" << std::endl;
        return;
    }
    
    this->modelPointsCount = dimension->dx * dimension->dy * dimension->dz;
    
    //allocating space for TRAVELTIMES[][][]
    
    for (int i=0; i < dimension->dx; i++)
    {
        this->traveltimes[i] = new float *[dimension->dy];
        
        for (int j=0; j < dimension->dy; j++)
        {
            this->traveltimes[i][j] = new float [dimension->dz];
        }
    }
    //values of 3D array this->velocity are not initialized!
    
    //init WAVEFRONT
}

void   FastMarchingMethod::calculateTraveltimes()
{
    while (pointsProcessed != modelPointsCount)
    {
        this->spreadWavefrontToNextGridPoint();
    }
}

void    FastMarchingMethod::spreadWavefrontToNextGridPoint()
{
    // IMPLEMENT!!!
    
    this->pointsProcessed += 1;
}

