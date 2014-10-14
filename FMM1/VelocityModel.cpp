//
//  VelocityModel.cpp
//  FastMarchingMethod
//
//  Created by fimi on 30/09/14.
//  Copyright (c) 2014 Filip Michlik. All rights reserved.
//

#include "VelocityModel.h"

VelocityModel::VelocityModel(Dimension *d): dimension(d)
{
    this->init();
}

VelocityModel::~VelocityModel()
{
    for (int i=0; i < this->dimension->dx; i++)
    {
        for (int j=0; j < this->dimension->dy; j++)
        {
            delete [] this->velocity[i][j];
        }
        
        delete [] this->velocity[i];
    }
    
    delete [] this->velocity;
}

void VelocityModel::init()
{
    if (!dimension) return;
    
    this->velocity = new float **[dimension->dx];
    
    for (int i=0; i < dimension->dy; i++)
    {
        this->velocity[i] = new float *[dimension->dy];
        
        for (int j=0; j < dimension->dz; j++)
        {
            this->velocity[i][j] = new float [dimension->dz];
        }
    }
    //values of 3D array this->velocity are not initialized!
}

bool VelocityModel::readModel(std::string pathToFile)
{
    //NOT IMPLEMENTED YET!!!
    return false; //should return true if reading was successful
}


