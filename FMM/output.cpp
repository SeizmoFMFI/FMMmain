#include "global.h"

float Dt = 500.f / 4500.f; //v[(int)(s.x/2)][(int)(s.y/2)][(int)(s.z/2)];

void save_all(Data *d) {
	cout<<"DBG save all ATs"<<endl;
	FILE * out;
	int meta[3] = {nx,ny,nz};

	float *buffer = new float[nx*ny*nz];
	float *ptr = buffer;

	FORALL {
		*ptr = at[i][j][k];  
		ptr++;
	}

	char file[256];
	filename(file,"atALL.bin",d->name,d->computation_ID);
	out = fopen (file, "wb");
	fwrite(meta, sizeof(meta[0]), 3, out);
	fwrite(buffer, sizeof(buffer[0]), nx*ny*nz, out);
	fclose(out);

	delete buffer;
}

void Output::save_at(Data *d) {
	FILE * out;
	int mx = (nx-1)/d->out_sparse + 1;
	int my = (ny-1)/d->out_sparse + 1;
	int mz = (nz-1)/d->out_sparse + 1;

	//cout<<"saving sparse data for kernel "<<mx<<","<<my<<","<<mz<<endl;

	int meta[3] = {mx,my,mz};

	float *buffer = new float[mx*my*mz];
	float *ptr = buffer;

	FORSPARSE {
		*ptr = at[i*d->out_sparse][j*d->out_sparse][k*d->out_sparse];  
		ptr++;
	}

	char file[256];
	filename(file,"at.bin",d->name,d->computation_ID);
	out = fopen (file, "wb");
	fwrite(meta, sizeof(meta[0]), 3, out);
	fwrite(buffer, sizeof(buffer[0]), mx*my*mz, out);
	fclose(out);

	delete buffer;
	//save_all(d);
}

void Output::save_arrivals(vector<Receiver> recs,const Data &d) {
	char file[256];
	filename(file,"arrivals.dat",d.name,d.computation_ID);
	FILE * out = fopen (file, "w");
	fprintf(out,"%d\n",recs.size());
	for (unsigned int i=0;i<recs.size();i++) {
		fprintf(out,"%f\n",recs.at(i).get_arrival());
	}
	fclose(out);
}

float precise(int i,int j,int k,const Source &s) {
	if ((i==s.x) && (j==s.y) && (k==s.z))
		return 0;
	return sqrt(SQR(i-s.x) + SQR(j-s.y) + SQR(k-s.z)) / v[i][j][k]; //homog
	/*
	//linear gradient
	double grad = (v[nx/2][ny/2][nz-1] - v[nx/2][ny/2][0]) / (nz-1);
	double X = sqrt(SQR(i-s.x)+SQR(j-s.y));
	double v0 = v[(int)s.x][(int)s.y][(int)s.z];
	double vZ = v[i][j][k];
	double rayP;
	rayP = SQR(grad*X)+SQR(vZ)+SQR(v0);
	rayP = SQR(rayP) - SQR(2*v0*vZ);
	rayP = 2*grad*X / sqrt(rayP);

	if (rayP == 0) { //kolmo dole
		return (float)abs(log(v0/vZ)/grad);
	}

	double sq0 = 1-SQR(rayP*v0);
	double sqZ = 1-SQR(rayP*vZ);
	if (sq0<0 && sq0>-0.0001)
		sq0 = 0;
	if (sqZ<0 && sqZ>-0.0001)
		sqZ = 0;
	sq0 = sqrt(sq0);
	sqZ = sqrt(sqZ);

	double Xmin = abs((sq0 - sqZ)/(grad*rayP)); //riesenie rovnice bez dosiahnutia minima
	double Xmax = abs((sq0 + sqZ)/(grad*rayP));
	double maxZ = (1/rayP - v0) / grad;

	double t;
	if (abs(X-Xmin) < abs(X-Xmax))
		t = abs( log(vZ/v0 * (1-sq0)/(1-sqZ)) / grad);
	else 
		t = abs( log(1/(v0*rayP) * (1-sq0)) / grad) + abs( log(1/(vZ*rayP) * (1-sqZ)) / grad);

	if (t!=t) {
		cout<<"analytical problem: "<<t<<" at "<<i<<","<<j<<","<<k<<" "<<rayP<<endl;
		cout<<(abs(X-Xmin) < abs(X-Xmax))<<""<<endl;
		cout<<"prvy "<<log(vZ/v0 * (1-sq0)/(1-sqZ)) / grad<<endl;
		cout<<"druhy "<<log(1/(v0*rayP) * (1-sq0)) / grad<<" + "<<log(1/(vZ*rayP) * (1-sqZ)) / grad<<endl;
		cout<<"druhy "<<1/(v0*rayP) * (1-sq0)<<" + "<<1/(vZ*rayP) * (1-sqZ)<<" "<<grad<<endl;
		cout<<Xmin<<" "<<X<<" "<<Xmax<<endl;
		cout<<1-SQR(rayP*v0)<<" "<<1-SQR(rayP*vZ)<<endl;
		cin.get();
		return 0.f;
	}
	return (float)t;
	*/
}

void Output::save_spherical_cuts(const Source &s) {
	FILE *o;
	int rr;
	float tmp,vup,vdown;
	for (int r=5;r<nx-10;r*=2) {
		if (r>nx/2) r=nx/2;

		char *c = new char[128];
		sprintf(c,"out_supka_%d.txt",r);
		o = fopen(c,"w");
		int k;

		rr = SQR(r); 
		for(int i=max(0,(int)(s.x-r));i<min(nx,(int)(s.x+r+1));i++){
		for(int j=max(0,(int)(s.y-r));j<min(ny,(int)(s.y+r+1));j++){

			tmp = SQR(i-s.x) + SQR(j-s.y);
			if (tmp>rr) 
				fprintf(o," 0");
			else {
				k = (int)( sqrt(rr - tmp) + s.z);
				if (k>nz-1)
					vdown = 0;
				else 
					vdown = at[i][j][k]-precise(i,j,k,s);

				k = (int)(-sqrt(rr - tmp) + s.z);
				if (k<0)
					vup = 0;
				else
					vup = at[i][j][k]-precise(i,j,k,s);
	
				if (abs(vdown)>abs(vup))
					sprintf(c," %f", vdown/ Dt);
				else 
					sprintf(c," %f", vup/ Dt);

				replace(c,c+strlen(c), '.', ',' );
				fprintf(o,c);
			}	
		}
		fprintf(o,"\n");
		}
		fclose(o);
	}
}

void Output::save_err_vs_dist(const Source &s) {
	FILE *o = fopen("out_err_vs_dist_max_avg.txt","w");
	int r,n;
	float tmp;
	char *c = new char[128];
	n = (int)max(max(s.x,s.y),s.z)+1;

	float* err = new float[n];
	int* err_n = new int[n];
	for(int i=0;i<n;i++) 
		err[i] = 0;

	//max err
	FORALL {
		r = (int)sqrt( SQR(i-s.x) + SQR(j-s.y) + SQR(k-s.z) );
		if (r<n) {
			tmp = abs(at[i][j][k]-precise(i,j,k,s))/Dt;

			if (tmp>err[r]) {
				err[r] = tmp;
			}
		}
	}

	for(int i=0;i<n;i++)  {
		sprintf(c,"%f ",err[i]);
		replace(c,c+strlen(c), '.', ',' );
		fprintf(o,c);
	}

	//avg err
	for(int i=0;i<n;i++) {
		err[i] = 0;
		err_n[i] = 0;
	}
	
	FORALL {
		r = (int)sqrt( SQR(i-s.x) + SQR(j-s.y) + SQR(k-s.z) );
		if (r<n) {
			err[r] += abs(at[i][j][k]-precise(i,j,k,s))/Dt;
			err_n[r]++;
		}
	}

	fprintf(o,"\n");
	for(int i=0;i<n;i++)  {
		sprintf(c,"%f ",err[i]/err_n[i]);
		replace(c,c+strlen(c), '.', ',' );
		fprintf(o,c);
	}
	
	delete [] err;
	delete [] c;

	fclose(o);
}

void Output::save_err_surface(const Source &s) {
	if (s.z != 0) {
		INFO("WARNING, source is not at surface, can't compute errs",false);
		return;
	}

	FILE *o = fopen("err_surface.txt","w");
	char *c = new char[128];
	for (int i=0;i<nx;i++) {
	for (int j=0;j<ny;j++) {
		sprintf(c," %f", at[i][j][0] - sqrtf(SQR(i-s.x)+SQR(j-s.y))/v[i][j][0]);
		replace(c,c+strlen(c), '.', ',' );
		fprintf(o,c);
	}
	fprintf(o,"\n");
	}
	fclose(o);
}

