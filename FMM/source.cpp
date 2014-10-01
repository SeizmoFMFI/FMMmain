#include "global.h"

Source Data::read_source() {
	char file[256];
	filename(file,"source.dat");
	FILE *in = fopen(file,"r");
	if (in == NULL)
		INFO("no input source.dat",true);
	int ns;
	fscanf(in,"%d",&ns);
	if (ns != 1)
		INFO("num. of sources is not 1",true);

	int relative;
	fscanf(in,"%d",&relative);
	float tmpx,tmpy,tmpz;
	fscanf(in,"%f %f %f",&tmpx,&tmpy,&tmpz);

	if (relative == 1) {
		tmpx*=(nx-1);
		tmpy*=(ny-1);
		tmpz*=(nz-1);
	}

	Source s = Source(tmpx,tmpy,tmpz);
	if (SHOW_INFO)
		cout<<"source "<<s.x<<","<<s.y<<","<<s.z<<endl;
	return s;
}

Source::Source(float xx,float yy,float zz): x(xx),y(yy),z(zz) {
	if ((x>=nx) || (y>=ny) || (z>=nz) || (x<0) || (y<0) || (z<0))  {
		char c[120];
		sprintf(c,"position %d,%d,%d, medium %dx%dx%d",x,y,z,nx,ny,nz);
		INFO("source out of medium",c,true);
	}
}

void Source::excite(int rad) {
	int srcx = (int)(x+0.5f);
	int srcy = (int)(y+0.5f);
	int srcz = (int)(z+0.5f);

	int direction;

     // Add container elements.
	for (int i=max(0,srcx-rad);i<=min(nx-1,srcx+rad);i++)
	for (int j=max(0,srcy-rad);j<=min(ny-1,srcy+rad);j++)
	for (int k=max(0,srcz-rad);k<=min(nz-1,srcz+rad);k++) {
		at[i][j][k] = sqrt(SQR(i-x)+SQR(j-y)+SQR(k-z)) *2 / (v[i][j][k]+v[srcz][srcy][srcz]);

			 if (i<srcx) direction =-1;
		else if (i>srcx) direction = 1;
		else if (j<srcy) direction =-2;
		else if (j>srcy) direction = 2;
		else if (k<srcz) direction =-3;
		else             direction = 3;  

		Bod b(direction,i,j,k);
		b.t = at[i][j][k]; 
		pq.push(b);
    }
}

