#ifndef RECEIVER_H
#define RECEIVER_H
#include "global.h"

class Receiver {
private:
	const float x,y,z;
public:
	Receiver(float xx,float yy,float zz);
	const float get_arrival();
};

#endif