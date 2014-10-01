#include "global.h"

clock_t time_start() {
	return std::clock();
}
void time(clock_t c_start) {
	if (!SHOW_INFO)
		return;
    std::clock_t c_end = std::clock();
    std::cout << "CPU time used: "
              << 1000.0 * (c_end-c_start) / CLOCKS_PER_SEC
              << " ms\n";
}
void INFO(const char *s) {
	INFO(s,"",false);
}

void INFO(const char *s,bool ERR) {
	INFO(s,"",ERR);
}

void INFO(const char *s1,const char *s2,bool ERR) {
	if (ERR) { 
		cout<<"ERR: ";
	}
	else {
		if (!SHOW_INFO)
			return;
		cout<<"i: ";
	}
	
	cout<<s1<<" "<<s2<<endl;

	if (ERR) {
		cin.get();cin.get();
	}
}

void filename(char *out, const char* name) {
	char* dir = "..//..//inout//computation//";
	sprintf(out,"%s%s",dir,name);
}

void filename(char *out,const char* name,const char* proc_name,const int ID) {
	char* dir = "..//..//inout//computation//";
	sprintf(out,"%s%s%d%s",dir,proc_name,ID,name);
}

void print_point_neighbours(int ii,int jj,int kk,int r) {
	cout.precision(4);
	cout<<"okolie bodu "<<ii<<","<<jj<<","<<kk<<endl;
	for (int i=max(0,ii-r);i<=min(nx-1,ii+r);i++) {
	for (int j=max(0,jj-r);j<=min(ny-1,jj+r);j++) {
	for (int k=max(0,kk-r);k<=min(nz-1,kk+r);k++) {
		cout<<at[i][j][k]<<" ";
	}
	cout<<endl;
	}
	cout<<endl;
	}
}

void print_point_neighbours_slowness(int ii,int jj,int kk,int r) {
	cout.precision(4);
	cout<<"okolie bodu "<<ii<<","<<jj<<","<<kk<<" - slowness"<<endl;
	for (int i=max(0,ii-r);i<=min(nx-1,ii+r);i++) {
	for (int j=max(0,jj-r);j<=min(ny-1,jj+r);j++) {
	for (int k=max(0,kk-r);k<=min(nz-1,kk+r);k++) {
		cout<<1/v[i][j][k]<<" ";
	}
	cout<<endl;
	}
	cout<<endl;
	}
}