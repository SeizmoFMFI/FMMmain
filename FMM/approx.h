#ifndef APPROX_H
#define APPROX_H
#include "global.h"

class Approximation {
public:
	float at_Z,at_A,at_B,at_C,at_D;
	bool okx,oky;
	short sikmox,sikmoy;

	float m,n,p,q; //O(2)
	float sx,sy,sz,st;
	float dx,dy,dz,dt;

	void prep_arrivals(short &smer,const short &si,const short &sj,const short &sk);
	void prep_arrivals_boundary(short &smer,const short &si,const short &sj,const short &sk);
	void prep_arrivals_1X(short &smer,const short &si,const short &sj,const short &sk);
	void prep_arrivals_1Y(short &smer,const short &si,const short &sj,const short &sk);
	void prep_arrivals_2X(short &smer,const short &si,const short &sj,const short &sk);
	void prep_arrivals_2Y(short &smer,const short &si,const short &sj,const short &sk);
	void prep_arrivals_3X(short &smer,const short &si,const short &sj,const short &sk);
	void prep_arrivals_3Y(short &smer,const short &si,const short &sj,const short &sk);
	void prep_arrivals_boundary_1(const short &smer,const short &si,const short &sj,const short &sk);
	void prep_arrivals_boundary_2(const short &smer,const short &si,const short &sj,const short &sk);
	void prep_arrivals_boundary_3(const short &smer,const short &si,const short &sj,const short &sk);
	void prep_param_O2(const float &X,const float &Y),prep_param_O3(const float &X,const float &Y);

	void find_virtual_source(const float &X,const float &Y,const float &v);
	float find_and_compute_from_virtual_source_boundary(const float &v);
	void guess_init_position(const float &X,const float &Y,const float &v);
	void linearize(const float &X,const float &Y,const float &v);
	void correct_for_NOG(),correct_Yn_for_NOG(float &Yn),correct_for_NOG_parab(float &Yn);

	float add_time_O2(const float &x,const float &y),add_time_O3(const float &x,const float &y);
	float res(const float &X,const float &x0,const float &at,const float &v);

	void print_arrivals() {
		cout<<"AzB CzD: "<<at_A<<" "<<at_Z<<" "<<at_B<<" , "<<at_C<<" "<<at_Z<<" "<<at_D<<endl; 
	};
	void print_dts(float X,float Y,float v) {
		cout<<" "<<(at_Z - st - sqrtf(SQR(sz) + SQR(sx) + SQR(sy))/v)/at_Z; 
		cout<<" "<<(at_A - st - sqrtf(SQR(sz) + SQR(-X - sx) + SQR(sy))/v)/at_A; 
		cout<<" "<<(at_B - st - sqrtf(SQR(sz) + SQR( X - sx) + SQR(sy))/v)/at_B; 
		cout<<" "<<(at_C - st - sqrtf(SQR(sz) + SQR(sx) + SQR(-Y - sy))/v)/at_C; 
		cout<<" "<<(at_D - st - sqrtf(SQR(sz) + SQR(sx) + SQR( Y - sy))/v)/at_D<<endl; 
	};
	void print_param_O2() { cout<<"O2 coef: "<<m<<" "<<n<<" , "<<p<<" "<<q<<" t0:"<<at_Z<<endl; };
	void print_param_O3() { cout<<"O3 coef: "<<-m*n<<" "<<m<<" "<<n<<" , "<<-p*q<<" "<<p<<" "<<q<<endl; };
	void print_virtual() { cout<<"vrt: "<<sx<<","<<sy<<","<<sz<<" "<<st<<endl;};
};

extern Approximation app;

#endif