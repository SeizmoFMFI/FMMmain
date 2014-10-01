#include "global.h"
#include "siet.h"
/*
void sir_na_z_vidale(short i,short j,short k,short smer,short zi,short zj,short zk) {
     Bod b(smer,i,j,k);
     b.sirFD(zi,zj,zk);

	 if (b.t>-1) {
		 pq.push(b);
		 at[i][j][k] = b.t;
	}
}

void Bod::sir() { //vyber najmensieho prvku z haldy a sirenie vlny z neho  
	if ((i == 0) || (j == 0) || (k == 0) || (i == nx-1) || (j == ny-1) || (k == nz-1)) {
		return;
	}
	
	if (s != 1)
			if (at[i-1][j][k]<-1)
				sir_na_z_vidale(i-1,j,k,-1,i,j,k);
	if (s !=-1)
			if (at[i+1][j][k]<-1)
				sir_na_z_vidale(i+1,j,k, 1,i,j,k);
	if (s != 2)
			if (at[i][j-1][k]<-1)
				sir_na_z_vidale(i,j-1,k,-2,i,j,k);
	if (s !=-2)
			if (at[i][j+1][k]<-1)
				sir_na_z_vidale(i,j+1,k, 2,i,j,k);
	if (s != 3)
			if (at[i][j][k-1]<-1)
				sir_na_z_vidale(i,j,k-1,-3,i,j,k);
	if (s !=-3)
			if (at[i][j][k+1]<-1)
				sir_na_z_vidale(i,j,k+1, 3,i,j,k);
}
*/
float stencil_A(const float &v,const float &t0,const float &t1,const float &t2,const float &t3,const float &t4,const float &t5,const float &t6) {
	float ss = 1.f/SQR(v);
	return t0 + sqrtf((6.f*ss - min(SQR(t1 - t2),ss) - min(SQR(t2 - t4),ss) - min(SQR(t4 - t1),ss) - min(SQR(t3 - t5),ss) - min(SQR(t5 - t6),ss) - min(SQR(t6 - t3),ss))/2.f);
	//return t0 + sqrtf((6.f/SQR(v) - SQR(t1 - t2) - SQR(t2 - t4) - SQR(t4 - t1) - SQR(t3 - t5) - SQR(t5 - t6) - SQR(t6 - t3))/2.f);
}

float stencil_B(const float &v,const float &t0,const float &t1,const float &t2,const float &t3,const float &t4) {
	return t1 + sqrtf(2.f/SQR(v) - 0.5f*SQR(t0 - t3) - SQR(t2 - t4));
}

float stencil_C(const float &v,const float &t0,const float &t1,const float &t2,const float &t3,const float &t4) {
	return t2 + sqrtf(1.f/SQR(v) - 0.25f*(SQR(t1 - t3) + SQR(t0 - t4)));
}

void Bod::sirFD(const short &si, const short &sj, const short &sk) {
	float tl,tp,td,th,tld,tpd,tlh,tph,sl,sp,sd,sh,sld,spd,slh,sph,sc;
	sc = at[si][sj][sk];
	float w = (v[si][sj][sk] + v[i][j][k])/2.f;

	if (s == 1 || s == -1) {
		tl = at[i][j+1][k];
		tp = at[i][j-1][k];
		th = at[i][j][k+1];
		td = at[i][j][k-1];

		tld = at[i][j+1][k-1];
		tpd = at[i][j-1][k-1];
		tlh = at[i][j+1][k+1];
		tph = at[i][j-1][k+1];

		sl = at[si][j+1][k];
		sp = at[si][j-1][k];
		sh = at[si][j][k+1];
		sd = at[si][j][k-1];

		sld = at[si][j+1][k-1];
		spd = at[si][j-1][k-1];
		slh = at[si][j+1][k+1];
		sph = at[si][j-1][k+1];
	}
	else if (s == 2 || s == -2) {
		tl = at[i+1][j][k];
		tp = at[i-1][j][k];
		th = at[i][j][k+1];
		td = at[i][j][k-1];

		tld = at[i+1][j][k-1];
		tpd = at[i-1][j][k-1];
		tlh = at[i+1][j][k+1];
		tph = at[i-1][j][k+1];

		sl = at[i+1][sj][k];
		sp = at[i-1][sj][k];
		sh = at[i][sj][k+1];
		sd = at[i][sj][k-1];

		sld = at[i+1][sj][k-1];
		spd = at[i-1][sj][k-1];
		slh = at[i+1][sj][k+1];
		sph = at[i-1][sj][k+1];
	}
	else {
		tl = at[i][j+1][k];
		tp = at[i][j-1][k];
		th = at[i+1][j][k];
		td = at[i-1][j][k];

		tld = at[i-1][j+1][k];
		tpd = at[i-1][j-1][k];
		tlh = at[i+1][j+1][k];
		tph = at[i+1][j-1][k];

		sl = at[i][j+1][sk];
		sp = at[i][j-1][sk];
		sh = at[i+1][j][sk];
		sd = at[i-1][j][sk];

		sld = at[i-1][j+1][sk];
		spd = at[i-1][j-1][sk];
		slh = at[i+1][j+1][sk];
		sph = at[i+1][j-1][sk];
	}

	if (tl>-1) {
		if (td>-1 && tld>-1 && sl>-1 && sd>-1 && sld>-1) {
			t = stencil_A(w,sld,tld,sd,td,sl,tl,sc);
			return;
		}
		if (th>-1 && tlh>-1 && sl>-1 && sh>-1 && slh>-1) {
			t = stencil_A(w,slh,tlh,sh,th,sl,tl,sc);
			return;
		}
	}

	if (tp>-1) {
		if (td>-1 && tpd>-1 && sp>-1 && sd>-1 && spd>-1) {
			t = stencil_A(w,spd,tpd,sd,td,sp,tp,sc);
			return;
		}
		if (th>-1 && tph>-1 && sp>-1 && sh>-1 && sph>-1) {
			t = stencil_A(w,sph,tph,sh,th,sp,tp,sc);
			return;
		}
	}

	if (td>-1) {
		if (sd>-1 && sld>-1 && spd>-1)  {
			t = stencil_B(w,sld,sd,td,spd,sc);
			return;
		}
	}
	if (th>-1) {
		if (sh>-1 && slh>-1 && sph>-1)  {
			t = stencil_B(w,slh,sh,th,sph,sc);
			return;
		}
	}
	if (tl>-1) {
		if (sl>-1 && sld>-1 && slh>-1)  {
			t = stencil_B(w,sld,sl,tl,slh,sc);
			return;
		}
	}
	if (tp>-1) {
		if (sp>-1 && spd>-1 && sph>-1)  {
			t = stencil_B(w,spd,sp,tp,sph,sc);
			return;
		}
	}

	if (sl>-1 && sp>-1 && sd>-1 && sh>-1) {
		t = stencil_C(w,sp,sd,sc,sh,sl);
		return;
	}

	t = -2;
	#ifdef DEBUG
	cout<<"ERR1402050946 NO STENCIL"<<endl;
	#endif
}