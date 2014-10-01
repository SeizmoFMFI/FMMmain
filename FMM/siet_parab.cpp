/*
#include "global.h"
#include "mriezka.h"

void sir_na_z_parab(short i,short j,short k,short smer,short zi,short zj,short zk) {
     Bod b(smer,i,j,k);
     b.sir2(zi,zj,zk);
	 pq.push(b);
}

void Bod::sir() { //vyber najmensieho prvku z haldy a sirenie vlny z neho  
	if ((i == 0) || (j == 0) || (k == 0) || (i == nx-1) || (j == ny-1) || (k == nz-1)) {
		return;
	}
	
	if (s != 1)
			if (at[i-1][j][k]<-1)
				sir_na_z_parab(i-1,j,k,-1,i,j,k);
	if (s !=-1)
			if (at[i+1][j][k]<-1)
				sir_na_z_parab(i+1,j,k, 1,i,j,k);
	if (s != 2)
			if (at[i][j-1][k]<-1)
				sir_na_z_parab(i,j-1,k,-2,i,j,k);
	if (s !=-2)
			if (at[i][j+1][k]<-1)
				sir_na_z_parab(i,j+1,k, 2,i,j,k);
	if (s != 3)
			if (at[i][j][k-1]<-1)
				sir_na_z_parab(i,j,k-1,-3,i,j,k);
	if (s !=-3)
			if (at[i][j][k+1]<-1)
				sir_na_z_parab(i,j,k+1, 3,i,j,k);
}

void Bod::sir2(const short &si, const short &sj, const short &sk) {
	app.prep_arrivals(s,si,sj,sk);
 
    nastav_polohu_primaca_a_dlzku();

	app.prep_param_O2(X,Y);
	//app.prep_param_O3(X,Y);

	app.correct_for_NOG_parab(Yn);

	iteruj(Xn,Yn,Xn,Yn,Zn,0);
}

void Bod::iteruj(float x, float y,const float &xn, const float &yn, const float &zn,short it) {
	const float &w = v[i][j][k];
     
    float r=w*sqrt(SQR(x-xn)+SQR(y-yn)+SQR(zn));

	// O(2)
    x=-(2*app.m*x+app.n)*r+xn;
    y=-(2*app.p*y+app.q)*r+yn;
     
	// O(3)
	//x = (app.m*x*(3*app.n*x-2) - app.n)*r + xn;
    //y = (app.p*y*(3*app.q*y-2) - app.q)*r + yn;

    it++;
    if (it==7) {
		if ((SQR(x-xn)>1.2)||(SQR(y-yn)>1.2)) {
			x=xn;
			y=yn;
		}

		//t=(float)(app.add_time_O3(x,y) + sqrt(SQR(x-xn)+SQR(y-yn)+SQR(zn))/w); 
		t = (app.add_time_O2(x,y) + sqrt(SQR(x-xn)+SQR(y-yn)+SQR(zn))/w);

		//at[i][j][k] = sqrtf(SQR(i-nx/2-0.1f) + SQR(j-ny/2-0.1f) + SQR(k-nz/2)) / w;
		//dbgt[i][j][k] = (t - at[i][j][k])*w;
		float precise = sqrtf(SQR(i-nx/2-0.1) + SQR(j-ny/2-0.1) + SQR(k-nz/2))/v[i][j][k];
		dbgt[i][j][k] = (t - precise)*v[i][j][k];

		at[i][j][k] = t;

		return;
    }

	iteruj(x,y,xn,yn,zn,it);
}
*/