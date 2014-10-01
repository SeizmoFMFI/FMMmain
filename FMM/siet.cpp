#include "global.h"
#include "siet.h"
#include <iomanip>

float X,Y;
float Xn,Yn,Zn; //poloha bodu kam sa siri vlna v ciarkovanej sustave x AB, y CD

Approximation app = Approximation();

bool sir_na_z(const short& i,const short &j,const short &k,const short &smer,const Bod &z) {
	Bod b(smer,i,j,k);
    b.sir2(z.i,z.j,z.k);

	#ifdef DEBUG 
	if (b.t != b.t)	{cout<<"ERR1402050920 "<<b.t<<" "<<i<<","<<j<<","<<k<<endl; cin.get();}
	#endif

	if (b.t>0) {
		at[i][j][k] = b.t;
		pq.push(b);

		#ifdef DEBUG 
		if (at[i][j][k]<at[z.i][z.j][z.k]) {cout<<"ERR1402051107 "<<i<<","<<j<<","<<k<<" z "<<z.i<<","<<z.j<<","<<z.k<<" "<<at[i][j][k]<<" z "<<at[z.i][z.j][z.k]<<endl;}
		#endif
		return true;
	}

	return false;
}

bool sir_at_boundary_to_from(const short &i,const short &j,const short &k,const short &smer,const Bod &z) {
	Bod b(smer,i,j,k);
	b.sir_at_boundary(z.i,z.j,z.k);

	if (b.t>0) {
		at[i][j][k] = b.t;
		pq.push(b);

		#ifdef DEBUG 
		if (at[i][j][k]<at[z.i][z.j][z.k]) {cout<<"ERR1402051259 BND "<<i<<","<<j<<","<<k<<" z "<<z.i<<","<<z.j<<","<<z.k<<" "<<at[i][j][k]<<" z "<<at[z.i][z.j][z.k]<<endl;}
		#endif
		return true;
	}

	return false;
}

void Bod::sir() { //vyber najmensieho prvku z haldy a sirenie vlny z neho  
	if ((i == 0) || (j == 0) || (i == nx-1) || (j == ny-1) || (k == 0) || (k == nz-1)) {
		bool all = true;
		if ((i>0) && (i<nx-1)) {
			if (at[i-1][j][k]<-1)
				all &= sir_at_boundary_to_from(i-1,j,k,-1,*this);
			if (at[i+1][j][k]<-1)
				all &= sir_at_boundary_to_from(i+1,j,k, 1,*this);
		}
		if ((j>0) && (j<ny-1)) {
			if (at[i][j-1][k]<-1)
				all &= sir_at_boundary_to_from(i,j-1,k,-2,*this);
			if (at[i][j+1][k]<-1)
				all &= sir_at_boundary_to_from(i,j+1,k, 2,*this);
		}
		if ((k>0) && (k<nz-1)) {
			if (at[i][j][k-1]<-1)
				all &= sir_at_boundary_to_from(i,j,k-1,-3,*this);
			if (at[i][j][k+1]<-1)
				all &= sir_at_boundary_to_from(i,j,k+1, 3,*this);
		}

		if (!all) {
			t += 0.1f/v[i][j][k];
			Bod b = Bod(s,i,j,k);
			b.t = t;
			pq.push(b);
		} else {
			if ((j>0)&&(j<ny-1)&&(k>0)&&(k<nz-1)){
				if (i==0)
					if (at[i+1][j][k]<-1)
						sir_na_z(i+1,j,k, 1,*this);
				if (i==nx-1)
					if (at[i-1][j][k]<-1)
						sir_na_z(i-1,j,k,-1,*this);
			}
			if ((i>0)&&(i<nx-1)&&(k>0)&&(k<nz-1)){
				if (j==0)
					if (at[i][j+1][k]<-1)
						sir_na_z(i,j+1,k, 2,*this);
				if (j==ny-1)
					if (at[i][j-1][k]<-1)
						sir_na_z(i,j-1,k,-2,*this);
			}
			if ((i>0)&&(i<nx-1)&&(j>0)&&(j<ny-1)){
				if (k==0)
					if (at[i][j][k+1]<-1)
						sir_na_z(i,j,k+1, 3,*this);
				if (k==nz-1)
					if (at[i][j][k-1]<-1)
						sir_na_z(i,j,k-1,-3,*this);
			}
		}
		return;
	}

	bool all = sir_inside();
	if (!all) {
		all = sir_inside();
		if (!all) {
			t += 0.1f/v[i][j][k];
			Bod b = Bod(s,i,j,k);
			b.t = t;
			pq.push(b);
		}
	}
}

bool Bod::sir_inside() {
	bool all = true;
	/*
	if (s != 1)
		if (at[i-1][j][k]<-1)
			all &= sir_na_z(i-1,j,k,-1,*this);
	if (s !=-1)
		if (at[i+1][j][k]<-1)
			all &= sir_na_z(i+1,j,k, 1,*this);
	if (s != 2)
		if (at[i][j-1][k]<-1)
			all &= sir_na_z(i,j-1,k,-2,*this);
	if (s !=-2)
		if (at[i][j+1][k]<-1)
			all &= sir_na_z(i,j+1,k, 2,*this);
	if (s != 3)
		if (at[i][j][k-1]<-1)
			all &= sir_na_z(i,j,k-1,-3,*this);
	if (s !=-3)
		if (at[i][j][k+1]<-1)
			all &= sir_na_z(i,j,k+1, 3,*this);
	*/

	if (s == 1) {
		if (at[i][j-1][k]<-1)
			all &= sir_na_z(i,j-1,k,-2,*this);
		if (at[i][j+1][k]<-1)
			all &= sir_na_z(i,j+1,k, 2,*this);
		if (at[i][j][k-1]<-1)
			all &= sir_na_z(i,j,k-1,-3,*this);
		if (at[i][j][k+1]<-1)
			all &= sir_na_z(i,j,k+1, 3,*this);

		if (at[i+1][j][k]<-1)
			all &= sir_na_z(i+1,j,k, 1,*this);
	}
	else if (s ==-1) {
		if (at[i][j-1][k]<-1)
			all &= sir_na_z(i,j-1,k,-2,*this);
		if (at[i][j+1][k]<-1)
			all &= sir_na_z(i,j+1,k, 2,*this);
		if (at[i][j][k-1]<-1)
			all &= sir_na_z(i,j,k-1,-3,*this);
		if (at[i][j][k+1]<-1)
			all &= sir_na_z(i,j,k+1, 3,*this);

		if (at[i-1][j][k]<-1)
			all &= sir_na_z(i-1,j,k,-1,*this);
	}
	else if (s == 2) {
		if (at[i-1][j][k]<-1)
			all &= sir_na_z(i-1,j,k,-1,*this);
		if (at[i+1][j][k]<-1)
			all &= sir_na_z(i+1,j,k, 1,*this);
		if (at[i][j][k-1]<-1)
			all &= sir_na_z(i,j,k-1,-3,*this);
		if (at[i][j][k+1]<-1)
			all &= sir_na_z(i,j,k+1, 3,*this);

		if (at[i][j+1][k]<-1)
			all &= sir_na_z(i,j+1,k, 2,*this);
	}
	else if (s ==-2) {
		if (at[i-1][j][k]<-1)
			all &= sir_na_z(i-1,j,k,-1,*this);
		if (at[i+1][j][k]<-1)
			all &= sir_na_z(i+1,j,k, 1,*this);
		if (at[i][j][k-1]<-1)
			all &= sir_na_z(i,j,k-1,-3,*this);
		if (at[i][j][k+1]<-1)
			all &= sir_na_z(i,j,k+1, 3,*this);

		if (at[i][j-1][k]<-1)
			all &= sir_na_z(i,j-1,k,-2,*this);
	}
	else if (s == 3) {
		if (at[i-1][j][k]<-1)
			all &= sir_na_z(i-1,j,k,-1,*this);
		if (at[i+1][j][k]<-1)
			all &= sir_na_z(i+1,j,k, 1,*this);
		if (at[i][j-1][k]<-1)
			all &= sir_na_z(i,j-1,k,-2,*this);
		if (at[i][j+1][k]<-1)
			all &= sir_na_z(i,j+1,k, 2,*this);

		if (at[i][j][k+1]<-1)
			all &= sir_na_z(i,j,k+1, 3,*this);
	}
	else {
		if (at[i-1][j][k]<-1)
			all &= sir_na_z(i-1,j,k,-1,*this);
		if (at[i+1][j][k]<-1)
			all &= sir_na_z(i+1,j,k, 1,*this);
		if (at[i][j-1][k]<-1)
			all &= sir_na_z(i,j-1,k,-2,*this);
		if (at[i][j+1][k]<-1)
			all &= sir_na_z(i,j+1,k, 2,*this);

		if (at[i][j][k-1]<-1)
			all &= sir_na_z(i,j,k-1,-3,*this);
	}

	return all;
}

void Bod::plane_approx(const short &si, const short &sj,const short &sk,const float &w) {
	float tx = app.at_Z + 1,ty = app.at_Z + 1;
	if (abs(s) == 1) {
		if (at[si][sj+1][sk]>-1) {
			if (at[si][sj-1][sk]>-1)
				tx = min(at[si][sj-1][sk],at[si][sj+1][sk]);
			else 
				tx = at[si][sj+1][sk];
		}
		if (at[si][sj-1][sk]>-1)
			tx = at[si][sj-1][sk];

		if (at[si][sj][sk+1]>-1) {
			if (at[si][sj][sk-1]>-1)
				ty = min(at[si][sj][sk-1],at[si][sj][sk+1]);
			else 
				ty = at[si][sj][sk+1];
		}
		if (at[si][sj][sk-1]>-1)
			ty = at[si][sj][sk-1];
	}
	else if (abs(s) == 2) {
		if (at[si+1][sj][sk]>-1) {
			if (at[si-1][sj][sk]>-1)
				tx = min(at[si-1][sj][sk],at[si+1][sj][sk]);
			else 
				tx = at[si+1][sj][sk];
		}
		if (at[si-1][sj][sk]>-1)
			tx = at[si-1][sj][sk];

		if (at[si][sj][sk+1]>-1) {
			if (at[si][sj][sk-1]>-1)
				ty = min(at[si][sj][sk-1],at[si][sj][sk+1]);
			else 
				ty = at[si][sj][sk+1];
		}
		if (at[si][sj][sk-1]>-1)
			ty = at[si][sj][sk-1];
	}
	else {
		if (at[si+1][sj][sk]>-1) {
			if (at[si-1][sj][sk]>-1)
				tx = min(at[si-1][sj][sk],at[si+1][sj][sk]);
			else 
				tx = at[si+1][sj][sk];
		}
		if (at[si-1][sj][sk]>-1)
			tx = at[si-1][sj][sk];

		if (at[si][sj+1][sk]>-1) {
			if (at[si][sj-1][sk]>-1)
				ty = min(at[si][sj-1][sk],at[si][sj+1][sk]);
			else 
				ty = at[si][sj+1][sk];
		}
		if (at[si][sj-1][sk]>-1)
			ty = at[si][sj-1][sk];
	}

	if ((app.at_Z < tx) && (app.at_Z < ty)) {
		t = app.at_Z + 1/w;
		return;
	}

	if (app.at_Z < tx) {
		float k = app.at_Z - ty;
		float kkww = SQR(k*w);
		if (kkww >= 0.5) {
			t = ty + sqrtf(2.f)/w;
			return;
		}

		float opt = sqrtf(kkww / (1-kkww));
		t = app.at_Z - k*opt + sqrtf(1+SQR(opt))/w;
		return;
	}

	if (app.at_Z < ty) {
		float k = app.at_Z - tx;
		float kkww = SQR(k*w);
		if (kkww >= 0.5) {
			t = tx + sqrtf(2.f)/w;
			return;
		}

		float opt = sqrtf(kkww / (1-kkww));
		t = app.at_Z - k*opt + sqrtf(1+SQR(opt))/w;

		return;
	}

	float vv = SQR(w);
	float kk = SQR(app.at_Z - tx);
	float ll = SQR(app.at_Z - ty);
	float div = max(1 - ll*vv - kk*vv, 0.5f);
	float optx = sqrtf(kk*vv / div);
	float opty = sqrtf(ll*vv / div);

	t = app.at_Z - (app.at_Z-tx)*optx - (app.at_Z-ty)*opty + sqrtf(1+SQR(optx)+SQR(opty))/w;

	#ifdef DEBUG 
	if (t<at[si][sj][sk]) {cout<<"ERR1402070955 FD plane app "<<i<<","<<j<<","<<k<<" z "<<si<<","<<sj<<","<<sk<<" "<<t<<" z "<<at[si][sj][sk]<<endl;}
	#endif
}

void Bod::sir2(const short &si, const short &sj, const short &sk) {
	app.prep_arrivals(s,si,sj,sk);   
    nastav_polohu_primaca_a_dlzku();
	app.prep_param_O2(X,Y);

	float w = (v[i][j][k] + v[si][sj][sk])/2.f;

	if ((abs(app.m*w)<0.015) || (abs(app.p*w)<0.015) || (app.m*app.p<=0)) {
		sirFD(si,sj,sk);

		if (t > at[si][sj][sk] + 1.f/w)
			t = at[si][sj][sk] + 1.f/w;

		if (t != t) //usually in a point next to slow velocity zone
			t = at[si][sj][sk] + 1.f/w;
		
		if (t < at[si][sj][sk]) {
			#ifdef DEBUG 
			cout<<"ERR1402051141 FD "<<i<<","<<j<<","<<k<<" z "<<si<<","<<sj<<","<<sk<<" "<<t<<" z "<<at[si][sj][sk]<<endl;print_point_neighbours(i,j,k);print_point_neighbours_slowness(i,j,k);
			#endif
			t = at[si][sj][sk];
		}
		return;
	}

	app.find_virtual_source(X,Y,w);

	if (app.sz != app.sz) { 
		//sqrt of negative number
		//happens, when time distances between ABCDZ points are too long
		//planar approximation from early points
		//could be much improved
		plane_approx(si,sj,sk,w);
		return;
	}

	app.correct_Yn_for_NOG(Yn);

	if (app.sz<=0) {
		t = app.st + sqrtf(SQR(Xn-app.sx) + SQR(Yn-app.sy) + SQR(Zn-app.sz)) / w;
	}
	else if (app.sz<=1) {
		plane_approx(si,sj,sk,w);
		return;
	}
	else {
		t = app.st - sqrtf(SQR(Xn-app.sx) + SQR(Yn-app.sy) + SQR(Zn-app.sz)) / w;
	}

	if (t<at[si][sj][sk]) {
		#ifdef DEBUG
		cout<<"ERR1402070939 arrival sphere t "<<t<<" from "<<at[si][sj][sk]<<" at "<<i<<","<<j<<","<<k<<endl;
		cout<<app.st<<" "<<sqrtf(SQR(Xn-app.sx) + SQR(Yn-app.sy) + SQR(Zn-app.sz)) / w<<" "<<Xn<<" "<<Yn<<" "<<Zn<<endl;
		app.print_virtual();print_point_neighbours(i,j,k);print_point_neighbours_slowness(i,j,k);cin.get();
		#endif
		t = at[si][sj][sk];
	}
	
	#ifdef DEBUG
	if (t != t) {cout<<"ERR1402050921 arrival sphere t "<<t<<" at "<<i<<","<<j<<","<<k<<endl;}
	#endif
}
