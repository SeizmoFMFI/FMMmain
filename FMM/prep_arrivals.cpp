#include "global.h"

float tmp1,tmp2;
/*
inline void Approximation::prep_arrivals_1X(short &smer,const short &si,const short &sj,const short &sk) {
	at_A=at[si][sj+1][sk]; //body v rovine
    at_B=at[si][sj-1][sk];
   
	if (at_A<-1) //body sikmo
		{
        at_A=at[si-smer][sj+1][sk];
        at_B=at[si+smer][sj-1][sk];
        if (at_A<-1) okx=false;
        if (at_B<-1) okx=false;
        sikmox=1;
        }
    else if (at_B<-1) //body sikmo
        {
        at_A=at[si+smer][sj+1][sk];
        at_B=at[si-smer][sj-1][sk];
        if (at_A<-1) okx=false;
        if (at_B<-1) okx=false;
        sikmox=-1;
        }
	else {
		tmp1 = at[si-smer][sj+1][sk];
		tmp2 = at[si+smer][sj-1][sk];
		if ((tmp1 > -1)&&(tmp2 > -1)) {
			if (max(tmp1,tmp2) < max(at_A,at_B)) {
				at_A = tmp1;
				at_B = tmp2;
				sikmox = 1;
			}
		}
		tmp1 = at[si+smer][sj+1][sk];
		tmp2 = at[si-smer][sj-1][sk];
		if ((tmp1 > -1)&&(tmp2 > -1)) {
			if (max(tmp1,tmp2) < max(at_A,at_B)) {
				at_A = tmp1;
				at_B = tmp2;
				sikmox =-1;
			}
		}
	}
}

inline void Approximation::prep_arrivals_1Y(short &smer,const short &si,const short &sj,const short &sk) {
	at_C=at[si][sj][sk+1]; //body v rovine
    at_D=at[si][sj][sk-1];
    if (at_C<-1) //body sikmo
        {
        at_C=at[si-smer][sj][sk+1];
        at_D=at[si+smer][sj][sk-1];
        if (at_C<-1) oky=false;
        if (at_D<-1) oky=false;
        sikmoy=1;
        }
    else if (at_D<-1) //body sikmo
        {
        at_C=at[si+smer][sj][sk+1];
        at_D=at[si-smer][sj][sk-1];
        if (at_C<-1) oky=false;
        if (at_D<-1) oky=false;
        sikmoy=-1;
        }
	else {
		tmp1 = at[si-smer][sj][sk+1];
		tmp2 = at[si+smer][sj][sk-1];
		if ((tmp1 > -1)&&(tmp2 > -1)) {
			if (max(tmp1,tmp2) < max(at_C,at_D)) {
				at_C = tmp1;
				at_D = tmp2;
				sikmoy = 1;
			}
		}
		tmp1 = at[si+smer][sj][sk+1];
		tmp2 = at[si-smer][sj][sk-1];
		if ((tmp1 > -1)&&(tmp2 > -1)) {
			if (max(tmp1,tmp2) < max(at_C,at_D)) {
				at_C = tmp1;
				at_D = tmp2;
				sikmoy =-1;
			}
		}
	}
}

inline void Approximation::prep_arrivals_2X(short &smer,const short &si,const short &sj,const short &sk) {
	at_A=at[si+1][sj][sk]; //body v rovine
    at_B=at[si-1][sj][sk];
    
	if (at_A<-1) //body sikmo
		{
        at_A=at[si+1][sj-smer][sk];
		at_B=at[si-1][sj+smer][sk];
        if (at_A<-1) okx=false;
        if (at_B<-1) okx=false;
        sikmox=1;
        }
    else if (at_B<-1) //body sikmo
        {
		at_A=at[si+1][sj+smer][sk];
		at_B=at[si-1][sj-smer][sk];
        if (at_A<-1) okx=false;
        if (at_B<-1) okx=false;
        sikmox=-1;
        }
	else {
		tmp1 = at[si+1][sj-smer][sk];
		tmp2 = at[si-1][sj+smer][sk];
		if ((tmp1 > -1)&&(tmp2 > -1)) {
			if (max(tmp1,tmp2) < max(at_A,at_B)) {
				at_A = tmp1;
				at_B = tmp2;
				sikmox = 1;
			}
		}
		tmp1 = at[si+1][sj+smer][sk];
		tmp2 = at[si-1][sj-smer][sk];
		if ((tmp1 > -1)&&(tmp2 > -1)) {
			if (max(tmp1,tmp2) < max(at_A,at_B)) {
				at_A = tmp1;
				at_B = tmp2;
				sikmox =-1;
			}
		}
	}
}

inline void Approximation::prep_arrivals_2Y(short &smer,const short &si,const short &sj,const short &sk) {
	at_C=at[si][sj][sk+1]; //body v rovine
    at_D=at[si][sj][sk-1];
    if (at_C<-1) //body sikmo
        {
		at_C=at[si][sj-smer][sk+1];
        at_D=at[si][sj+smer][sk-1];
        if (at_C<-1) oky=false;
        if (at_D<-1) oky=false;
        sikmoy=1;
        }
    else if (at_D<-1) //body sikmo
        {
		at_C=at[si][sj+smer][sk+1];
        at_D=at[si][sj-smer][sk-1];
        if (at_C<-1) oky=false;
        if (at_D<-1) oky=false;
        sikmoy=-1;
        }
	else {
		tmp1 = at[si][sj-smer][sk+1];
		tmp2 = at[si][sj+smer][sk-1];
		if ((tmp1 > -1)&&(tmp2 > -1)) {
			if (max(tmp1,tmp2) < max(at_C,at_D)) {
				at_C = tmp1;
				at_D = tmp2;
				sikmoy = 1;
			}
		}
		tmp1 = at[si][sj+smer][sk+1];
		tmp2 = at[si][sj-smer][sk-1];
		if ((tmp1 > -1)&&(tmp2 > -1)) {
			if (max(tmp1,tmp2) < max(at_C,at_D)) {
				at_C = tmp1;
				at_D = tmp2;
				sikmoy =-1;
			}
		}
	}
}

inline void Approximation::prep_arrivals_3X(short &smer,const short &si,const short &sj,const short &sk) {
	at_A=at[si][sj+1][sk]; //body v rovine
    at_B=at[si][sj-1][sk];
	if (at_A<-1) //body sikmo
		{
        at_A=at[si][sj+1][sk-smer];
        at_B=at[si][sj-1][sk+smer];
        if (at_A<-1) okx=false;
        if (at_B<-1) okx=false;
        sikmox=1;
        }
    else if (at_B<-1) //body sikmo
        {
        at_A=at[si][sj+1][sk+smer];
        at_B=at[si][sj-1][sk-smer];
        if (at_A<-1) okx=false;
        if (at_B<-1) okx=false;
        sikmox=-1;
        }
	else {
		tmp1 = at[si][sj+1][sk-smer];
		tmp2 = at[si][sj-1][sk+smer];
		if ((tmp1 > -1)&&(tmp2 > -1)) {
			if (max(tmp1,tmp2) < max(at_A,at_B)) {
				at_A = tmp1;
				at_B = tmp2;
				sikmox = 1;
			}
		}
		tmp1 = at[si][sj+1][sk+smer];
		tmp2 = at[si][sj-1][sk-smer];
		if ((tmp1 > -1)&&(tmp2 > -1)) {
			if (max(tmp1,tmp2) < max(at_A,at_B)) {
				at_A = tmp1;
				at_B = tmp2;
				sikmox =-1;
			}
		}
	}
}

inline void Approximation::prep_arrivals_3Y(short &smer,const short &si,const short &sj,const short &sk) {
	at_C=at[si+1][sj][sk]; //body v rovine
    at_D=at[si-1][sj][sk];
    if (at_C<-1) //body sikmo
        {
		at_C=at[si+1][sj][sk-smer];
        at_D=at[si-1][sj][sk+smer];
        if (at_C<-1) oky=false;
        if (at_D<-1) oky=false;
        sikmoy=1;
        }
    else if (at_D<-1) //body sikmo
        {
        at_C=at[si+1][sj][sk+smer];
        at_D=at[si-1][sj][sk-smer];
        if (at_C<-1) oky=false;
        if (at_D<-1) oky=false;
        sikmoy=-1;
        }
	else {
		tmp1 = at[si+1][sj][sk-smer];
		tmp2 = at[si-1][sj][sk+smer];
		if ((tmp1 > -1)&&(tmp2 > -1)) {
			if (max(tmp1,tmp2) < max(at_C,at_D)) {
				at_C = tmp1;
				at_D = tmp2;
				sikmoy = 1;
			}
		}
		tmp1 = at[si+1][sj][sk+smer];
		tmp2 = at[si-1][sj][sk-smer];
		if ((tmp1 > -1)&&(tmp2 > -1)) {
			if (max(tmp1,tmp2) < max(at_C,at_D)) {
				at_C = tmp1;
				at_D = tmp2;
				sikmoy =-1;
			}
		}
	}
}
*/
inline void Approximation::prep_arrivals_1X(short &smer,const short &si,const short &sj,const short &sk) {
	at_A=at[si][sj+1][sk]; //body v rovine
    at_B=at[si][sj-1][sk];

	if (at_A<-1) //body sikmo
		{
        at_A=at[si-smer][sj+1][sk];
        at_B=at[si+smer][sj-1][sk];
        if (at_A<-1) okx=false;
        if (at_B<-1) okx=false;
        sikmox=1;
        }
    else if (at_B<-1) //body sikmo
        {
        at_A=at[si+smer][sj+1][sk];
        at_B=at[si-smer][sj-1][sk];
        if (at_A<-1) okx=false;
        if (at_B<-1) okx=false;
        sikmox=-1;
        }
}

inline void Approximation::prep_arrivals_1Y(short &smer,const short &si,const short &sj,const short &sk) {
	at_C=at[si][sj][sk+1]; //body v rovine
    at_D=at[si][sj][sk-1];
    if (at_C<-1) //body sikmo
        {
        at_C=at[si-smer][sj][sk+1];
        at_D=at[si+smer][sj][sk-1];
        if (at_C<-1) oky=false;
        if (at_D<-1) oky=false;
        sikmoy=1;
        }
    else if (at_D<-1) //body sikmo
        {
        at_C=at[si+smer][sj][sk+1];
        at_D=at[si-smer][sj][sk-1];
        if (at_C<-1) oky=false;
        if (at_D<-1) oky=false;
        sikmoy=-1;
        }
}

inline void Approximation::prep_arrivals_2X(short &smer,const short &si,const short &sj,const short &sk) {
	at_A=at[si+1][sj][sk]; //body v rovine
    at_B=at[si-1][sj][sk];

	if (at_A<-1) //body sikmo
		{
        at_A=at[si+1][sj-smer][sk];
		at_B=at[si-1][sj+smer][sk];
        if (at_A<-1) okx=false;
        if (at_B<-1) okx=false;
        sikmox=1;
        }
    else if (at_B<-1) //body sikmo
        {
		at_A=at[si+1][sj+smer][sk];
		at_B=at[si-1][sj-smer][sk];
        if (at_A<-1) okx=false;
        if (at_B<-1) okx=false;
        sikmox=-1;
        }
}

inline void Approximation::prep_arrivals_2Y(short &smer,const short &si,const short &sj,const short &sk) {
	at_C=at[si][sj][sk+1]; //body v rovine
    at_D=at[si][sj][sk-1];
    if (at_C<-1) //body sikmo
        {
		at_C=at[si][sj-smer][sk+1];
        at_D=at[si][sj+smer][sk-1];
        if (at_C<-1) oky=false;
        if (at_D<-1) oky=false;
        sikmoy=1;
        }
    else if (at_D<-1) //body sikmo
        {
		at_C=at[si][sj+smer][sk+1];
        at_D=at[si][sj-smer][sk-1];
        if (at_C<-1) oky=false;
        if (at_D<-1) oky=false;
        sikmoy=-1;
        }
}

inline void Approximation::prep_arrivals_3X(short &smer,const short &si,const short &sj,const short &sk) {
	at_A=at[si][sj+1][sk]; //body v rovine
    at_B=at[si][sj-1][sk];
	if (at_A<-1) //body sikmo
		{
        at_A=at[si][sj+1][sk-smer];
        at_B=at[si][sj-1][sk+smer];
        if (at_A<-1) okx=false;
        if (at_B<-1) okx=false;
        sikmox=1;
        }
    else if (at_B<-1) //body sikmo
        {
        at_A=at[si][sj+1][sk+smer];
        at_B=at[si][sj-1][sk-smer];
        if (at_A<-1) okx=false;
        if (at_B<-1) okx=false;
        sikmox=-1;
        }
}

inline void Approximation::prep_arrivals_3Y(short &smer,const short &si,const short &sj,const short &sk) {
	at_C=at[si+1][sj][sk]; //body v rovine
    at_D=at[si-1][sj][sk];
    if (at_C<-1) //body sikmo
        {
		at_C=at[si+1][sj][sk-smer];
        at_D=at[si-1][sj][sk+smer];
        if (at_C<-1) oky=false;
        if (at_D<-1) oky=false;
        sikmoy=1;
        }
    else if (at_D<-1) //body sikmo
        {
        at_C=at[si+1][sj][sk+smer];
        at_D=at[si-1][sj][sk-smer];
        if (at_C<-1) oky=false;
        if (at_D<-1) oky=false;
        sikmoy=-1;
        }
}

void Approximation::prep_arrivals(short &smer,const short &si,const short &sj,const short &sk) {
	okx=true;
    oky=true;
    sikmox=0;
    sikmoy=0;

	at_Z = at[si][sj][sk];
	if ((smer==1)||(smer==-1)) {  
		prep_arrivals_1X(smer,si,sj,sk);
        prep_arrivals_1Y(smer,si,sj,sk);
    }
	else if ((smer==2)||(smer==-2)) {
        smer/=2;
		prep_arrivals_2X(smer,si,sj,sk);
        prep_arrivals_2Y(smer,si,sj,sk);
		smer*=2;
	}
	else {
        smer/=3;
		prep_arrivals_3X(smer,si,sj,sk);
        prep_arrivals_3Y(smer,si,sj,sk);
		smer*=3;
	}
}

void nastav_polohu_primaca_a_dlzku() {
    if (app.okx)
        {
        if (app.sikmox == 0) {Xn=0;X=1;}
        if (app.sikmox == 1) {X= sqrtf(2);Xn= X/2;}
        if (app.sikmox ==-1) {X= sqrtf(2);Xn=-X/2;}
        }
    else 
        {
        Xn=0;
        X =1;
        app.sikmox = 0;
        }
          
     if (app.oky)
        {
        if (app.sikmoy == 0) {Yn=0;Y=1;}
        if (app.sikmoy == 1) {Y= sqrtf(2);Yn= Y/2;}
        if (app.sikmoy ==-1) {Y= sqrtf(2);Yn=-Y/2;}      
        }
     else 
        {
        Yn=0;
        Y =1;
        app.sikmoy = 0;
        }
        
     int sik=SQR(app.sikmox)+SQR(app.sikmoy);

     if      (sik==0)  Zn=1;
     else if (sik==1)  Zn=sqrtf(2)/2;
     else              Zn=sqrtf(3)/3; //z=vzdialenost od roviny so sikmostou 2 / tretina telesovej uhlopriecky
}

//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx			BOUNDARY		xxxxxxxxxxxxxxxxxxxxxxxxxx
void Approximation::prep_arrivals_boundary_1(const short &smer,const short &si,const short &sj,const short &sk) {
	if ((sj == 0) || (sj == ny-1)) {
		if (sj==0)
			at_C = at[si][sj+1][sk];
		else 
			at_C = at[si][sj-1][sk];


		if (sk>0)
			at_A = at[si][sj][sk-1];
		if (sk<nz-1)
			at_B = at[si][sj][sk+1];

		//sikmo
		if ((sk>0)&&(sk<nz-1)) {
			if (at_A<-1) {
				if ((at[si-smer][sj][sk-1]>-1) && (at[si+smer][sj][sk+1]>-1)) {
					X = sqrtf(2);
					Xn = sqrtf(2)/2;
					Zn = sqrtf(2)/2;
					at_A = at[si-smer][sj][sk-1];
					at_B = at[si+smer][sj][sk+1];
				}
			}
			else if (at_B<-1)  {
				if ((at[si+smer][sj][sk-1]>-1) && (at[si-smer][sj][sk+1]>-1)) {
					X = sqrtf(2);
					Xn = -sqrtf(2)/2;
					Zn = sqrtf(2)/2;
					at_A = at[si+smer][sj][sk-1];
					at_B = at[si-smer][sj][sk+1];
				}
			}
		}
	}
	else if ((sk == 0) || (sk == nz-1)) {
		if (sk==0)
			at_C = at[si][sj][sk+1];
		else
			at_C = at[si][sj][sk-1];

		if (sj>0)
			at_A = at[si][sj-1][sk];
		if (sj<ny-1)
			at_B = at[si][sj+1][sk];

		//sikmo
		if ((sj>0)&&(sj<ny-1)) {
			if (at_A<-1) {
				if ((at[si-smer][sj-1][sk]>-1) && (at[si+smer][sj+1][sk]>-1)) {
					X = sqrtf(2);
					Xn = sqrtf(2)/2;
					Zn = sqrtf(2)/2;
					at_A = at[si-smer][sj-1][sk];
					at_B = at[si+smer][sj+1][sk];
				}
			}
			else if (at_B<-1)  {
				if ((at[si+smer][sj-1][sk]>-1) && (at[si-smer][sj+1][sk]>-1)) {
					X = sqrtf(2);
					Xn = -sqrtf(2)/2;
					Zn = sqrtf(2)/2;
					at_A = at[si+smer][sj-1][sk];
					at_B = at[si-smer][sj+1][sk];
				}
			}
		}
	}
	else {
		INFO("SOMETHING WRONG AT THE BOUNDARY",true);
	}
}

void Approximation::prep_arrivals_boundary_2(const short &smer,const short &si,const short &sj,const short &sk) {
	if ((si == 0) || (si == nx-1)) {
		if (si==0)
			at_C = at[si+1][sj][sk];
		else 
			at_C = at[si-1][sj][sk];


		if (sk>0)
			at_A = at[si][sj][sk-1];
		if (sk<nz-1)
			at_B = at[si][sj][sk+1];

		//sikmo
		if ((sk>0)&&(sk<nz-1)) {
			if (at_A<-1) {
				if ((at[si][sj-smer][sk-1]>-1) && (at[si][sj+smer][sk+1]>-1)) {
					X = sqrtf(2);
					Xn = sqrtf(2)/2;
					Zn = sqrtf(2)/2;
					at_A = at[si][sj-smer][sk-1];
					at_B = at[si][sj+smer][sk+1];
				}
			}
			else if (at_B<-1)  {
				if ((at[si][sj+smer][sk-1]>-1) && (at[si][sj-smer][sk+1]>-1)) {
					X = sqrtf(2);
					Xn = -sqrtf(2)/2;
					Zn = sqrtf(2)/2;
					at_A = at[si][sj+smer][sk-1];
					at_B = at[si][sj-smer][sk+1];
				}
			}
		}
	}
	else if ((sk == 0) || (sk == nz-1)) {
		if (sk==0)
			at_C = at[si][sj][sk+1];
		else
			at_C = at[si][sj][sk-1];

		if (si>0)
			at_A = at[si-1][sj][sk];
		if (si<nx-1)
			at_B = at[si+1][sj][sk];

		//sikmo
		if ((si>0)&&(si<nx-1)) {
			if (at_A<-1) {
				if ((at[si-1][sj-smer][sk]>-1) && (at[si+1][sj+smer][sk]>-1)) {
					X = sqrtf(2);
					Xn = sqrtf(2)/2;
					Zn = sqrtf(2)/2;
					at_A = at[si-1][sj-smer][sk];
					at_B = at[si+1][sj+smer][sk];
				}
			}
			else if (at_B<-1)  {
				if ((at[si-1][sj+smer][sk]>-1) && (at[si+1][sj-smer][sk]>-1)) {
					X = sqrtf(2);
					Xn = -sqrtf(2)/2;
					Zn = sqrtf(2)/2;
					at_A = at[si-1][sj+smer][sk];
					at_B = at[si+1][sj-smer][sk];
				}
			}
		}
	}
	else {
		INFO("SOMETHING WRONG AT THE BOUNDARY",true);
	}
}

void Approximation::prep_arrivals_boundary_3(const short &smer,const short &si,const short &sj,const short &sk) {
	if ((sj == 0) || (sj == ny-1)) {
		if (sj==0)
			at_C = at[si][sj+1][sk];
		else 
			at_C = at[si][sj-1][sk];


		if (si>0)
			at_A = at[si-1][sj][sk];
		if (si<nx-1)
			at_B = at[si+1][sj][sk];

		//sikmo
		if ((si>0)&&(si<nx-1)) {
			if (at_A<-1) {
				if ((at[si-1][sj][sk-smer]>-1) && (at[si+1][sj][sk+smer]>-1)) {
					X = sqrtf(2);
					Xn = sqrtf(2)/2;
					Zn = sqrtf(2)/2;
					at_A = at[si-1][sj][sk-smer];
					at_B = at[si+1][sj][sk+smer];
				}
			}
			else if (at_B<-1)  {
				if ((at[si-1][sj][sk+smer]>-1) && (at[si+1][sj][sk-smer]>-1)) {
					X = sqrtf(2);
					Xn = -sqrtf(2)/2;
					Zn = sqrtf(2)/2;
					at_A = at[si-1][sj][sk+smer];
					at_B = at[si+1][sj][sk-smer];
				}
			}
		}
	}
	else if ((si == 0) || (si == nx-1)) {
		if (si==0)
			at_C = at[si+1][sj][sk];
		else
			at_C = at[si-1][sj][sk];

		if (sj>0)
			at_A = at[si][sj-1][sk];
		if (sj<ny-1)
			at_B = at[si][sj+1][sk];

		//sikmo
		if ((sj>0)&&(sj<ny-1)) {
			if (at_A<-1) {
				if ((at[si][sj-1][sk-smer]>-1) && (at[si][sj+1][sk+smer]>-1)) {
					X = sqrtf(2);
					Xn = sqrtf(2)/2;
					Zn = sqrtf(2)/2;
					at_A = at[si][sj-1][sk-smer];
					at_B = at[si][sj+1][sk+smer];
				}
			}
			else if (at_B<-1)  {
				if ((at[si][sj-1][sk+smer]>-1) && (at[si][sj+1][sk-smer]>-1)) {
					X = sqrtf(2);
					Xn = -sqrtf(2)/2;
					Zn = sqrtf(2)/2;
					at_A = at[si][sj-1][sk+smer];
					at_B = at[si][sj+1][sk-smer];
				}
			}
		}
	}
	else {
		INFO("SOMETHING WRONG AT THE BOUNDARY",true);
	}
}

void Approximation::prep_arrivals_boundary(short &smer,const short &si,const short &sj,const short &sk) {
	Xn = 0;
	Zn = 1;
	X = 1;

	at_Z = at[si][sj][sk];
	at_A = -2;
	at_B = -2;
	if ((smer==1) || (smer==-1)) {  
		prep_arrivals_boundary_1(smer,si,sj,sk);
    }
	else if ((smer==2)||(smer==-2)) {  
		smer/=2;
		prep_arrivals_boundary_2(smer,si,sj,sk);
		smer*=2;
    }
	else {
        smer/=3;
		prep_arrivals_boundary_3(smer,si,sj,sk);
		smer*=3;
	}
}

