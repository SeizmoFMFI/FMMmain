#include "global.h"

float interpolate_undefined_arrival(float ***at,const int i,const int j,const int k) {
	int ii,lo,up;
	ii = i;
	while ((ii>0) && (at[ii][j][k]<0)) {
		ii--;
	}
	lo = ii;
	ii = i;
	while ((ii<nx-1) && (at[ii][j][k]<0)) {
		ii++;
	}
	up = ii;
	if ((up>i) && (lo<i)) {
		at[i][j][k] = ((up-i)*at[lo][j][k] + (i-lo)*at[up][j][k])/(up-lo);
		return at[i][j][k];
	}
	else if (up>i) {
		at[i][j][k] = at[up][j][k];
		return at[i][j][k];
	}
	else if (lo<i) {
		at[i][j][k] = at[lo][j][k];
		return at[i][j][k];
	}
	return -2;
}


void save_at_hline(float ***at,int z,int id) {
	float *buffer = new float[nx*ny*z];
	int *meta = new int[3];
	meta[0] = nx;
	meta[1] = ny;
	meta[2] =  z;

	for (int i=0;i<nx;i++) 
	for (int j=0;j<ny;j++)
	for (int k=0;k< z;k++) {
		if (k<z-2) {
			buffer[i*ny*z+j*z+k] = -2;
		}
		else {
			if (at[i][j][k]>0) {
				buffer[i*ny*z+j*z+k] = at[i][j][k];
			}
			else {
				buffer[i*ny*z+j*z+k] = interpolate_undefined_arrival(at,i,j,k);
				cout<<"ERR"<<i<<","<<j<<","<<k<<" "<<at[i][j][k]<<endl;
				cout<<"ERR"<<nx<<","<<ny<<","<<nz<<endl;
			}
		}
	}

	char file[256];
	filename(file,"at_interface.bin","init",id);
	FILE *out = fopen (file, "wb");
	fwrite(meta, sizeof(meta[0]), 3, out);
	fwrite(buffer, sizeof(buffer[0]), nx*ny*z, out);
	fclose(out);

	delete buffer;
	delete meta;
}

void save_interface(float ***at,int id) {
	save_at_hline(at,21,id);
}

void check_init_ats(float ***at) {
	FORALL {
		if (abs(at[i][j][k])<0.001)
			cout<<"init problem "<<i<<","<<j<<","<<k<<" "<<at[i][j][k]<<endl;
		if (k>18) {
			if (at[i][j][k]<0) {
				cout<<"init problem "<<i<<","<<j<<","<<k<<" "<<at[i][j][k]<<endl;
			}
		}
		else {
			if (at[i][j][k]>0) {
				cout<<"init problem "<<i<<","<<j<<","<<k<<" "<<at[i][j][k]<<endl;
			}
		}

		//edges too fast
		if (i==0) if (at[i][j][k]<at[i+1][j][k]) {
			at[i][j][k] = at[i+1][j][k];
		}
		if (i==nx-1) if (at[i][j][k]<at[i-1][j][k]) {
			at[i][j][k] = at[i-1][j][k];
		}
		if (j==0) if (at[i][j][k]<at[i][j+1][k]) {
			at[i][j][k] = at[i][j+1][k];
		}
		if (j==ny-1) if (at[i][j][k]<at[i][j-1][k]) {
			at[i][j][k] = at[i][j-1][k];
		}
	}
}

void init_points(float ***at) {
	for(unsigned short i=2;i<nx-2;i++) 
	for(unsigned short j=2;j<ny-2;j++) 
	for(unsigned short k=1;k<nz-1;k++) {
		if (at[i][j][k]>-1) {
			Bod b(-3,i,j,k); //only horizontal interface
			b.t = at[i][j][k]; 
			pq.push(b);
		}
		else if (k==19) {
			cout<<"init "<<i<<","<<j<<","<<k<<" "<<at[i][j][k]<<endl;
		}
	}
	//cout<<"initialized "<<pq.size()<<" from "<<(nx-4)*(ny-4)<<endl;
}

void init_interface(float ***at,int id) {
	INFO("only horizontal interface");
	char file[256];
	filename(file,"at_interface.bin","init",id);
	FILE *in = fopen (file, "rb");
	if (in == NULL) {
		INFO("no file ",file,true);
	}

	int *m = new int[3]; 
	fread (m, sizeof(int), 3, in);
	if ((m[0]!=nx) || (m[0]!=nx) || (m[0]!=nx)) {
		cerr<<"ERR diferent size of init interface and model:"<<endl;
		cerr<<m[0]<<","<<m[1]<<","<<m[2]<<" vs "<<nx<<","<<ny<<","<<nz<<endl;
		cin.get();
	}
	float *buffer = new float[nx*ny*nz];
	fread (buffer, sizeof(float), nx*ny*nz, in);
	FORALL {
		at[i][j][k] = buffer[i*ny*nz+j*nz+k];
	}

	fclose(in);
	delete m;
	delete buffer;

	check_init_ats(at);
	init_points(at);
}