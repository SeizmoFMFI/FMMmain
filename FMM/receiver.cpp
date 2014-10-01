#include "global.h"

vector<Receiver> Data::read_receivers() {
	char file[256];
	filename(file,"receivers.dat");
	FILE *in = fopen(file,"r");
	if (in == NULL)
		INFO("no input receivers.dat",true);
	int nr;
	fscanf(in,"%d",&nr);

	int relative;
	fscanf(in,"%d",&relative);

	vector<Receiver> recs;
	float tx,ty,tz;
	for (int i=0;i<nr;i++) {
		fscanf(in,"%f %f %f",&tx,&ty,&tz);
		if (relative==1) {
			tx*=(nx-1);
			ty*=(ny-1);
			tz*=(nz-1);
		}
		Receiver r = Receiver(tx,ty,tz);

		recs.push_back(r);
	}

	return recs;
}

Receiver::Receiver(float xx,float yy,float zz): x(xx),y(yy),z(zz){
	if ((x>=nx-1) || (y>=ny-1) || (z>=nz-1) || (x<=0) || (y<=0) || (z<0))  {
		cout<<x<<","<<y<<","<<z<<" "<<nx<<"x"<<ny<<"x"<<nz<<endl;
		INFO("receiver out of medium or at its interior boundary",true);
	}
};

const float Receiver::get_arrival() {
	float dx,dy,dz,arr = 0;
	dx = x - (int)x;
	dy = y - (int)y;
	dz = z - (int)z;

	if (z <= 0) { //at the free surface
		arr += at[(int)x]  [(int)y]  [0]	*(1-dx)	*(1-dy);
		arr += at[(int)x+1][(int)y]  [0]	* dx	*(1-dy);
		arr += at[(int)x]  [(int)y+1][0]	*(1-dx)	* dy;
		arr += at[(int)x+1][(int)y+1][0]	* dx	* dy;
		return arr;
	}

	arr += at[(int)x]  [(int)y]  [(int)z]	*(1-dx)	*(1-dy)	*(1-dz);
	arr += at[(int)x+1][(int)y]  [(int)z]	* dx	*(1-dy)	*(1-dz);
	arr += at[(int)x]  [(int)y+1][(int)z]	*(1-dx)	* dy	*(1-dz);
	arr += at[(int)x+1][(int)y+1][(int)z]	* dx	* dy	*(1-dz);
	arr += at[(int)x]  [(int)y]  [(int)z+1]	*(1-dx)	*(1-dy)	* dz;
	arr += at[(int)x+1][(int)y]  [(int)z+1]	* dx	*(1-dy)	* dz;
	arr += at[(int)x]  [(int)y+1][(int)z+1]	*(1-dx)	* dy	* dz;
	arr += at[(int)x+1][(int)y+1][(int)z+1]	* dx	* dy	* dz;

	return arr;
}