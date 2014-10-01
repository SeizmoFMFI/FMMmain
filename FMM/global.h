#ifndef GLOBAL_H
#define GLOBAL_H

//#define DEBUG

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <queue>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <cmath>
#include <ctime>
using namespace std;

#define SQR(x) ((x) * (x))
extern float  ***at,***v;

#include "approx.h"
#include "auxilary.h"
#include "data.h"
#include "siet.h"
#include "output.h"
#include "queue.h"
#include "receiver.h"
#include "source.h"

#define FORALL  for(unsigned short i=0;i<nx;i++) for(unsigned short j=0;j<ny;j++) for(unsigned short k=0;k<nz;k++)
#define FORSPARSE  for(unsigned short i=0;i<mx;i++) for(unsigned short j=0;j<my;j++) for(unsigned short k=0;k<mz;k++)

#define PI 3.1415926535

extern int nx,ny,nz;

extern bool operator< (const Bod&, const Bod&);
extern PQ pq;

extern bool SHOW_INFO;

#endif /* GLOBAL_H */
