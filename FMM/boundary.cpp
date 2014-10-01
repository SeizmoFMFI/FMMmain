#include "global.h"

float correction_inclined_plane_boundary(float dr,const float &at0,const float &atI,const float &w) {
	if (atI <= -1)
		return dr;
	if (at0 <= atI)
		return dr;

	float sina = (at0 - atI)*w;
	if (abs(sina)>1)
		sina = 0;
	else 
		sina = sqrtf(1-SQR(sina));

	return dr*sina; 
}

float simple_plane_wave_at_boundary(const float &w) {
	float atA = max(app.at_A,app.at_B); //to druhe je mensie ako 0 - neurcene

	float dst = correction_inclined_plane_boundary(1.f,app.at_Z,atA,w);
	dst = correction_inclined_plane_boundary(dst,app.at_Z,app.at_C,w);

	return app.at_Z + dst/w;
}

void Bod::sir_at_boundary(const short& si,const short& sj,const short& sk) {
	app.prep_arrivals_boundary(s,si,sj,sk);

	float w = (v[i][j][0] + v[si][sj][0])/2.f;
	if ((app.at_A<0) || (app.at_B<0)) {
		t = simple_plane_wave_at_boundary(w);

		#ifdef DEBUG 
		if (t<at[si][sj][sk]) {cout<<"ERR1402051257 FDBND "<<i<<","<<j<<","<<k<<" z "<<si<<","<<sj<<","<<sk<<" "<<t<<" z "<<at[si][sj][sk]<<endl;}
		#endif
		return;
	}

	//korekcia rychlosti na dopad zospodu
	if (app.at_C>-1) {
		if (app.at_C<app.at_Z) {
			float sina = (app.at_Z - app.at_C)*w;
			if (sina > 0.9f) 
				sina = 0.9f;

			w = w/sqrtf(1-SQR(sina));

			if (i==389) if (j==250) if (k==0) {
				cout<<"korekcia "<<w<<" "<<sina<<endl;
			}
		}
	}

	t = app.find_and_compute_from_virtual_source_boundary(w);
	if (t<at[si][sj][sk]) {cout<<"ERR1402051256 SPHBND "<<i<<","<<j<<","<<k<<" z "<<si<<","<<sj<<","<<sk<<" "<<t<<" z "<<at[si][sj][sk]<<endl;}
	if (t<at[si][sj][sk]+0.3/w) if (at[si][sj][sk]<at[si][sj][sk+1]) {cout<<"WAR SPHBND "<<i<<","<<j<<","<<k<<" z "<<si<<","<<sj<<","<<sk<<" "<<t<<" z "<<at[si][sj][sk]<<endl;}
	if (i==389) if (j==250) if (k==0) {
			cout<<"cas "<<t<<" velocity "<<w<<endl;
			cout<<app.st<<" "<<app.sx<<" "<<app.sz<<endl;
			cout<<"rovinna "<<abs(app.at_A + app.at_B - 2*app.at_Z)<<" "<<w*abs(app.at_A + app.at_B - 2*app.at_Z)<<" vs 0.005"<<endl;
	}
	#ifdef DEBUG 
	if (t<at[si][sj][sk]) {cout<<"ERR1402051256 SPHBND "<<i<<","<<j<<","<<k<<" z "<<si<<","<<sj<<","<<sk<<" "<<t<<" z "<<at[si][sj][sk]<<endl;}
	#endif
}

float Approximation::find_and_compute_from_virtual_source_boundary(const float &w) {
	float ww = SQR(w);

	st = at_A + at_B - 2*at_Z;

	if (abs(st)*w < 0.005f) { //rovinna vlna
		float sina;
		if (at_A < at_B) {
			sina = (at_Z - at_A) * w/X;
		}
		else {
			sina = (at_Z - at_B) * w/X;
		}

		if (abs(sina)>1)
			return at_Z;
		return at_Z + Zn*sqrtf(1 - SQR(sina))/w;
	}

	st = (SQR(at_A) + SQR(at_B) - 2*SQR(at_Z) - 2*SQR(X)/ww) / (2*st);

	sx = -(ww * (at_B*(at_B - 2*st) - at_Z*(at_Z - 2*st)) - SQR(X)) / (2*X);
	sz = ww * SQR(at_Z - st) - SQR(sx);
	if (sz<0)
		sz = 0;
	sz = -sqrtf(sz);

	if (st > at_Z) {//opacne zakrivenie - chcelo by to spresnit, ale to zakomentene nejak nefunguje
		return at_Z + 1.f/w;
		/*
		sz = -sz;
		if (st - sqrtf(SQR(Xn-sx) + SQR(Zn-sz))/w < at_Z) {
			return at_Z;
		}
		return st - sqrtf(SQR(Xn-sx) + SQR(Zn-sz))/w;
		*/
	}

	return st + sqrtf(SQR(Xn-sx) + SQR(Zn-sz))/w;
}