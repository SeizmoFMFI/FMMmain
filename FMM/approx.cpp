#include "global.h"

void Approximation::prep_param_O2(const float &X,const float &Y) {
    if (okx) {
         m=(at_A+at_B-2*at_Z)/(2*SQR(X));
         n=(at_B-at_A)/(2*abs(X));
    }
    else {
         m=0;
         n=0;
    }
    
    if (oky) {
        p=(at_C+at_D-2*at_Z)/(2*SQR(Y));
        q=(at_D-at_C)/(2*abs(Y));
    }
    else {
        p=0;
        q=0;
    }
}

void Approximation::prep_param_O3(const float &X,const float &Y) {
	float div;
    if (okx) {
         m=(at_A+at_B-2*at_Z)/(2*SQR(X));
		 div = 2*abs(X)*(1-m*SQR(X));
         n=(at_B-at_A)/div;
    }
    else {
        m=0;
        n=0;
    }
    
    if (oky) {
        p=(at_C+at_D-2*at_Z)/(2*SQR(Y));
		div = 2*abs(Y)*(1-p*SQR(Y));
        q=(at_D-at_C)/div;
    }
	else {
        p=0;
        q=0;
    }
}

float find_t0_in_circ_approx(const float &t_near,const float &x_near,const float &z,const float &v) {
	return z/v + t_near - sqrtf(SQR(x_near) + SQR(z))/v;
}

float find_z0_in_circ_approx(const float &t_near,const float &t_far,const float &x_near,const float &x_far,const float &dy,const float &v) {
	const float dt = t_far - t_near;

	float chi = SQR(x_far) + SQR(x_near) - SQR(dt*v);
	float zzyy = (SQR(chi)/4.f - SQR(x_far)*SQR(x_near)) / (SQR(dt*v));

	return sqrtf(zzyy - SQR(dy));
}

float Approximation::add_time_O2(const float &x,const float &y) {
	return (m*x + n)*x + (p*y + q)*y + at_Z;
}

float Approximation::add_time_O3(const float &x,const float &y)  {
	return ((-n*x + 1)*m*x + n)*x + ((-q*y + 1)*p*y + q)*y + at_Z; // - ABxxx + Axx + Bx
}

float Approximation::res(const float &X,const float &x0,const float &at,const float &v) {
	return (SQR(X) - 2*X*x0)/(SQR(v)) + SQR(at_Z) - SQR(at);
}

void Approximation::guess_init_position(const float &X,const float &Y,const float &v) {
	sx = -n/(2*m);
	sy = -q/(2*p);

	if (at_A + at_B < at_C + at_D)
		st = (SQR(at_A) + SQR(at_B) - 2*SQR(at_Z) - 2*SQR(X)/SQR(v)) / (2*(at_A + at_B - 2*at_Z));
	else 
		st = (SQR(at_C) + SQR(at_D) - 2*SQR(at_Z) - 2*SQR(Y)/SQR(v)) / (2*(at_C + at_D - 2*at_Z));
	
	#ifdef DEBUG
	if (st != st) {cout<<"ERR: guess virtual source t is "<<st<<endl;}
	if (sx != sx) {cout<<"ERR: guess virtual source x is "<<sx<<endl;}
	if (sy != sy) {cout<<"ERR: guess virtual source y is "<<sy<<endl;}
	#endif
}

void Approximation::linearize(const float &X,const float &Y,const float &v) {
	//linearize x
	if (at_A < at_B) {
		sx = (SQR(at_A) - SQR(at_Z) - 2*(at_A - at_Z)*st)*SQR(v) / ( 2*X)  - X/2;
	}
	else {
		sx = (SQR(at_B) - SQR(at_Z) - 2*(at_B - at_Z)*st)*SQR(v) / (-2*X)  + X/2;
	}

	//linearize y
	if (at_C < at_D) {
		sy = (SQR(at_C) - SQR(at_Z) - 2*(at_C - at_Z)*st)*SQR(v) / ( 2*Y)  - Y/2;
	}
	else {
		sy = (SQR(at_D) - SQR(at_Z) - 2*(at_D - at_Z)*st)*SQR(v) / (-2*Y)  + Y/2;
	}

	correct_for_NOG();

	//compute z
	sz = - sqrtf(SQR(at_Z - st)*SQR(v) - SQR(sx) - SQR(sy));
	if (st>at_Z) {
		sz = -sz;
	}
}

void Approximation::find_virtual_source(const float &X,const float &Y,const float &v) {
	guess_init_position(X,Y,v);
	linearize(X,Y,v);
}

void Approximation::correct_for_NOG(){
	if ((sikmox == 0) || (sikmoy == 0))
		return;

	if (sikmox*sikmoy>0) { //angle = 60
		sy = (2*sy - sx) / sqrtf(3);
	}
	else { //angle = 120
		sy = (2*sy + sx) / sqrtf(3);
	}
}

void Approximation::correct_Yn_for_NOG(float &Yn){
	if ((sikmox == 0) || (sikmoy == 0))
		return;

	Yn = Yn / sqrtf(3);
}

void Approximation::correct_for_NOG_parab(float &Yn){
	if ((sikmox == 0) || (sikmoy == 0))
		return;

	if (sikmox*sikmoy>0) { //angle = 60
		q -=   n/2.f;
		q *= 2.f/sqrtf(3);
	}
	else { //angle = 120
		q +=   n/2.f;
		q *= 2.f/sqrtf(3);
	}

	p -=   m/4.f;
	p *= 4.f/3.f;

	Yn = Yn * sqrtf(3)/2.f;
}
