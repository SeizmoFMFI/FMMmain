#include "global.h"
int nx,ny,nz;

Data::Data(char* argv,char *argv2): name(argv),computation_ID(atoi(argv2)) {
	read_data();
}

void Data::read_data() {
	isAdjoint = false;
	if (strcmp(name,"adjoint") == 0)
		isAdjoint = true;

	char file[256];
	filename(file,"data.dat");
	FILE *in = fopen(file,"r");
	if (in == NULL)
		INFO("no input data.dat",true);
	fscanf(in,"%d",&out_sparse);

	filename(file,"model.dat");
	in = fopen(file,"r");
	if (in == NULL)
		INFO("no input model.dat",true);

	fscanf(in,"%d %d %d",&mx,&my,&mz);
	fscanf(in,"%d %d %d",&nx,&ny,&nz);
	fscanf(in,"%f",&x_width_in_m);
	fscanf(in,"%s",model_filename);

	if ((nx<2)||(ny<2)||(nz<2)||(mx<2)||(my<2)||(mz<2)) {
		cout<<nx<<"  "<<ny<<"  "<<nz<<"  "<<mx<<"  "<<my<<"  "<<mz<<endl;
		INFO("grid (dense or sparse) is too small, must be at least 2 in every direction",true);
	}

	if (((nx-1)%(mx-1)!=0) || ((ny-1)%(my-1)!=0) || ((nz-1)%(mz-1)!=0))
		INFO("number of grid points can't be matched to sparse model grid",true);

	dh = x_width_in_m / (nx-1);
	if (dh<0.00001)
		INFO("dh is too small or zero",true);
}

void slow_down_edges(unsigned short ***mv,int mx,int my,int mz) {
	float c=0.5f;

	if (!INIT_AT_INTERFACE) {
		for(int i=0;i<mx;i++)
		for(int j=0;j<my;j++)
			mv[i][j][mz-1] *= c;
	}

	for(int i=0;i<mx;i++)
	for(int k=0;k<mz;k++) {
		mv[i][0][k]    *= c;
		mv[i][my-1][k] *= c;
	}

	for(int j=0;j<my;j++)
	for(int k=0;k<mz;k++) {
		mv[0][j][k]    *= c;
		mv[mx-1][j][k] *= c;
	}
}

float*** Data::read_model() {
	INFO("reading input model: ",model_filename,false);

	char file[256];
	filename(file,model_filename);
	FILE *in = fopen(file,"rb");
	if (in == NULL) {
		char err[256];
		sprintf(err,"read model: no input %s",file);
		INFO(err,true);
	}

	unsigned short*** mv = allocate3D<unsigned short>(mx,my,mz);

	//read v
	int size = sizeof(unsigned short);
	int count;
	for (int i=0;i<mx;i++)
	for (int j=0;j<my;j++) {
		count = fread (mv[i][j], size, mz, in);
		if (count != mz) {
			char c[30];
			sprintf(c, "%d out of %d", count,mz);
			INFO("read model: reading the model.bin went wrong, count ",c,true);
		}
	}
	slow_down_edges(mv,mx,my,mz);

	//print_slice(mv,mx,my,mz);

	//allocate
	float*** v = allocate3D<float>(nx,ny,nz);
	interpolate(mv,v);

	//delete
	for (int i=0;i<mx;i++) {
		for (int j=0;j<my;j++) {
			delete(mv[i][j]);
		}
		delete(mv[i]);
	}
	delete(mv);

	if ((dh==NULL)||(dh<0.00001))
		INFO("prepare velocity: dh is too small or zero or null",true);
	FORALL
		v[i][j][k] /= dh;

	INFO("velocity model prepared",false);
	return v;
}

void Data::interpolate(unsigned short*** src,float*** dst) {
	//check if possible
	int dx = (nx-1) / (mx-1);
	int dy = (ny-1) / (my-1);
	int dz = (nz-1) / (mz-1);

	if ((dx*(mx-1) != nx-1) || (dy*(my-1) != ny-1) || (dz*(mz-1) != nz-1)) {
		char s[60];
		sprintf(s,"%d %d %d -> %d %d %d",mx,my,mz,nx,ny,nz);
		INFO("can not interpolate: ",s,true);
		return;
	}

	//copy src to dst
	for (int i=0;i<mx;i++)
	for (int j=0;j<my;j++)
	for (int k=0;k<mz;k++) {
		dst[i][j][k] = (float)src[i][j][k];
	}
	
	int sparse,wide;
	//interpolate z
	for (int i=mx-1;i>=0;i--)
	for (int j=my-1;j>=0;j--)
	for (int k=nz-1;k>=0;k--) {
		sparse = (k-1)/dz;
		wide = sparse*dz;
		dst[i][j][k] = ((wide+dz-k)*dst[i][j][sparse] + (k-wide)*dst[i][j][sparse+1])/dz;
	}

	//interpolate y
	for (int i=mx-1;i>=0;i--)
	for (int j=ny-1;j>0;j--)
	for (int k=nz-1;k>=0;k--) {
		sparse = (j-1)/dy;
		wide = sparse*dy;
		dst[i][j][k] = ((wide+dy-j)*dst[i][sparse][k] + (j-wide)*dst[i][sparse+1][k])/dy;
	}

	//interpolate x
	for (int i=nx-1;i>0;i--)
	for (int j=ny-1;j>=0;j--)
	for (int k=nz-1;k>=0;k--) {
		sparse = (i-1)/dx;
		wide = sparse*dx;
		dst[i][j][k] = ((wide+dx-i)*dst[sparse][j][k] + (i-wide)*dst[sparse+1][j][k])/dx;
	}

	/*
	121110 9 8 7 6 5 4 3 2 1 0
	 4     3     2     1     0
	 nz = 13
	 mz = 5
	 dz = 3

	 12-1/3=3 9
	 11-1/3=3 9
	 10-1/3=3 9
	 9 -1/3=2 6
	 8 -1/3=2 6
	 7 -1/3=2 6
	 6 -1/3=1 3
	 5 -1/3=1 3
	 4 -1/3=1 3
	 3 -1/3=0 0
	 2 -1/3=0 0
	 1 -1/3=0 0

	int dx = (nx-1) / (mx-1);
	int dy = (ny-1) / (my-1);
	int dz = (nz-1) / (mz-1);

	dh = x_width_in_m / (nx-1);

	int val;

	for (int k=0;k<mz-1;k++)
	for (int j=0;j<my-1;j++)
	for (int i=0;i<mx-1;i++) {
		for (int kk=0;kk<dz;kk++)
		for (int jj=0;jj<dy;jj++)
		for (int ii=0;ii<dx;ii++) {
			val = src[k][j][i]*(dz-kk)*(dy-jj)*(dx-ii) + src[k+1][j+1][i+1]*kk*jj*ii
				+ src[k+1][j][i]*kk*(dy-jj)*(dx-ii) + src[k][j+1][i]*(dz-kk)*jj*(dx-ii) + src[k][j][i+1]*(dz-kk)*(dy-jj)*ii
				+ src[k+1][j+1][i]*kk*jj*(dx-ii)	+ src[k][j+1][i+1]*(dz-kk)*jj*ii	+ src[k+1][j][i+1]*kk*(dy-jj)*ii;

			dst[k*dz+kk][j*dy+jj][i*dx+ii] = (float)val / (dx*dy*dz*dh);
		}
	}

	for (int k=0;k<mz-1;k++)
	for (int j=0;j<my-1;j++) {
		for (int kk=0;kk<dz-1;kk++)
		for (int jj=0;jj<dy-1;jj++) {
			val = src[k][j][mx-1]*(dz-kk)*(dy-jj) + src[k+1][j+1][mx-1]*kk*jj
				+ src[k+1][j][mx-1]*kk*(dy-jj)	  + src[k][j+1][mx-1]*(dz-kk)*jj;
				
			dst[k*dz+kk][j*dy+jj][nx-1] = (float)val / (dy*dz*dh);
		}
	}

	for (int k=0;k<mz-1;k++)
	for (int i=0;i<mx-1;i++) {
		for (int kk=0;kk<dz-1;kk++)
		for (int ii=0;ii<dx-1;ii++) {
			val = src[k][my-1][i]*(dz-kk)*(dx-ii) + src[k+1][my-1][i+1]*kk*ii
				+ src[k+1][my-1][i]*kk*(dx-ii)    + src[k][my-1][i+1]*(dz-kk)*ii;
					
			dst[k*dz+kk][ny-1][i*dx+ii] = (float)val / (dx*dz*dh);
		}
	}

	for (int j=0;j<my-1;j++)
	for (int i=0;i<mx-1;i++) {
		for (int jj=0;jj<dy-1;jj++)
		for (int ii=0;ii<dx-1;ii++) {
			val = src[mz-1][j][i]*(dy-jj)*(dx-ii) + src[mz-1][j+1][i+1]*jj*ii
				+ src[mz-1][j+1][i]*jj*(dx-ii)    + src[mz-1][j][i+1]*(dy-jj)*ii;

			dst[nz-1][j*dy+jj][i*dx+ii] = (float)val / (dy*dx*dh);
		}
	}

	for (int k=0;k<mz-1;k++) {
		for (int kk=0;kk<dz;kk++) {
			val = src[k][my-1][mx-1]*(dz-kk) + src[k+1][my-1][mx-1]*kk;
			dst[k*dz+kk][ny-1][nx-1] = (float)val / (dz*dh);
		}
	}
	
	for (int j=0;j<my-1;j++) {
		for (int jj=0;jj<dy;jj++) {
			val = src[mz-1][j][mx-1]*(dy-jj) + src[mz-1][j+1][mx-1]*jj;
			dst[nz-1][j*dy+jj][nx-1] = (float)val / (dy*dh);
		}
	}
	
	for (int i=0;i<mx-1;i++) {
		for (int ii=0;ii<dx;ii++) {
			val = src[mz-1][my-1][i]*(dx-ii) + src[mz-1][my-1][i+1]*ii;
			dst[nz-1][ny-1][i*dx+ii] = (float)val / (dx*dh);
		}
	}
	
	dst[nz-1][ny-1][nx-1] = src[mz-1][my-1][mx-1]/dh;
	*/
}

/*
void nacitaj_pole_zo_suboru()
{
CPU_TIME("nacitavam udaje");
cout<<"model iteracia cislo "<<key_main<<endl; 
char name[50];
sprintf(name,"data/model_PS_it_%d",key_main); 
FILE *in = fopen(name,"r");
fscanf(in,"%d %d %d\n",&mx,&my,&mz);
cout<<"rychlostne pole (d="<<md<<")  "<<mx<<" "<<my<<" "<<mz<<endl;
cout<<"vypoctovy model (d="<<d <<")  "<<nx<<" "<<ny<<" "<<nz<<endl;

int tmp;
FORALLM
      {
      if (k<nz)fscanf(in,"%d %d",&vP[i][j][k],&vS[i][j][k]);
      else fscanf(in,"%d %d",&tmp,&tmp);
      
      if (vP[i][j][k]<0) {cout<<"zadane zle pole, na mieste:"<<i<<" "<<j<<" "<<k<<" je hodnota rychlosti "<<vP[i][j][k]<<endl;cin.get();}
      }
fclose(in);

    //rychlost
    if (d==md)
       {
       if (mz!=nz) 
          {
          if (mz>nz)
             {
             mz=nz;
             cout<<"WARNING: model prostredia je hlbsi, ako ten, co vyuzijem pri ratani"<<endl;
             }
          else
              {
               cout<<"WARNING: velkost poli sa nezhoduje, skontroluj, cakam..."<<endl;
               cin.get();
               }
          }
       if ((mx!=nx)||(my!=ny))
          {
          cout<<"WARNING: velkost poli sa nezhoduje, skontroluj, cakam..."<<endl;
          cin.get();
          }
       }
    else if (2*d==md) //priemerovanie z okolitych 
                      //davat si pozor, lebo male pole mapujem na vacssie v ramci 
                      //jedineho pola!                
         {
         for (int i=nx-1;i>=0;i--)
         for (int j=ny-1;j>=0;j--)
         for (int k=nz-1;k>=0;k--)
             {
             short i1,i2,j1,j2,k1,k2;
             
             if (i%2==0) {i1=i/2;i2=i1;}
             else        {i1=i/2;i2=i1+1;}
             if (j%2==0) {j1=j/2;j2=j1;}
             else        {j1=j/2;j2=j1+1;}
             if (k%2==0) {k1=k/2;k2=k1;}
             else        {k1=k/2;k2=k1+1;}
             
             //predna strana
             int vw;
             vw =vP[i1][j1][k1]+vP[i1][j1][k2]+vP[i1][j2][k1]+vP[i1][j2][k2];
             //zadna strana
             vw+=vP[i2][j1][k1]+vP[i2][j1][k2]+vP[i2][j2][k1]+vP[i2][j2][k2];
             vP[i][j][k]=(short)(vw/8);
             
             //predna strana
             vw =vS[i1][j1][k1]+vS[i1][j1][k2]+vS[i1][j2][k1]+vS[i1][j2][k2];
             //zadna strana
             vw+=vS[i2][j1][k1]+vS[i2][j1][k2]+vS[i2][j2][k1]+vS[i2][j2][k2];
             vS[i][j][k]=(short)(vw/8);
             }
         }
    else
        {cout<<"ERR: nevhodny nasobok medzi mriezkami nacitaneho rychlostneho pola a vypoctoveho modelu";cin.get();}
        
cout<<"Pole rychlosti uspesne nacitane"<<endl;
}
*/