//
//  main.cpp
//  FastMarchingMethod
//
//  Created by fimi on 30/09/14.
//  Copyright (c) 2014 Filip Michlik. All rights reserved.
//

#include <iostream>

#include "FastMarchingMethod.h"
#include "VelocityModel.h"

using namespace std;

int main(int argc, const char * argv[]) {
	//one iteration:

	//prepare directory - copy input files
	//run extern program forward - FMM.exe

	//prepare directory - copy input files
	//run extern program forward - FMM.exe

	//compute kernels

	//update model

    int dx, dy, dz, sx, sy, sz;
    //prepare MODEL
    dx = 100;
    dy = 100;
    dz = 100;
    
    Dimension *dimension = new Dimension(dx, dy, dz);
    VelocityModel *vm = new VelocityModel(dimension);
    
    cout << "MODEL-dimensions: " << vm->dimension->dx << " x " << vm->dimension->dy << " x " << vm->dimension->dz << endl;
    
    //prepare SOURCE POSITION
    sx = 50;
    sy = 50;
    sz = 50;
    GridPosition *source = new GridPosition(sx, sy, sz);
    
    //instantiate FMM
    FastMarchingMethod *fmm = new FastMarchingMethod(vm, source);
    
    //RUN CALCULATIONS
    
    //release memory
    delete fmm;
    delete source;
    delete vm;
    delete dimension;
    
    return 0;
}

