#ifndef AUX_H
#define AUX_H

extern bool SHOW_INFO,SAVE_AT_INTERFACE,INIT_AT_INTERFACE;

template <class myType> 
myType*** allocate3D(int x,int y,int z) {
	myType ***a = new myType**[x];
	for (int i=0;i<x;i++) {
		a[i] = new myType*[y];
		for (int j=0;j<y;j++) {
			a[i][j] = new myType[z];
		}
	}

	return a;
}

extern void time(clock_t c_start),INFO(const char *s1),INFO(const char *s1,bool ERR),INFO(const char *s1,const char *s2,bool ERR);
extern void filename(char* out,const char* name),filename(char* out,const char* name,const char* proc_name,const int ID);
extern clock_t time_start();
extern void print_point_neighbours(int,int,int,int r=1),print_point_neighbours_slowness(int,int,int,int r=1);

template <typename T>
const void print_slice(T ***a,const int nx,const int ny,const int nz) { 
	cout<<"slice from 3D: "<<nx<<"x"<<ny<<"x"<<nz<<endl;
	int samples = 15;
	/*
	cout<<"YZ"<<endl;
	for(int j=0;j<samples;j++) {
	for(int k=0;k<samples;k++) {
		cout<<(unsigned short)a[nx/2][j*(ny-1)/samples][k*(nz-1)/samples]<<" "; 
	}
		cout<<endl;
	}

	cout<<"XZ"<<endl;
	for(int i=0;i<samples;i++) {
	for(int k=0;k<samples;k++) {
		cout<<(unsigned short)a[i*(nx-1)/samples][ny/2][k*(nz-1)/samples]<<" "; 
	}
		cout<<endl;
	}

	cout<<"XY"<<endl;
	for(int i=0;i<samples;i++) {
	for(int j=0;j<samples;j++) {
		cout<<(unsigned short)a[i*(nx-1)/samples][j*(ny-1)/samples][nz/2]<<" "; 
	}
		cout<<endl;
	}

	cout<<"surface XY"<<endl;
	for(int i=0;i<samples;i++) {
	for(int j=0;j<samples;j++) {
		cout<<(unsigned short)a[i*(nx-1)/samples][j*(ny-1)/samples][0]<<" "; 
	}
		cout<<endl;
	}
	*/
	cout<<"surface+2 XY"<<endl;
	for(int i=0;i<samples;i++) {
	for(int j=0;j<samples;j++) {
		cout<<(unsigned short)a[i*(nx-1)/samples][j*(ny-1)/samples][2]<<" "; 
	}
		cout<<endl;
	}
	//cin.get();
} 

#endif