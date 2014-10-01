#ifndef SIET_H
#define SIET_H

extern float *** at;
extern float X,Y,Xn,Yn,Zn;
extern void nastav_polohu_primaca_a_dlzku();
extern void save_interface(float ***at,int id),init_interface(float ***at,int id);

class Bod {
public:
	Bod(const short &smer,const short &ii,const short &jj,const short &kk): s(smer),i(ii),j(jj),k(kk){};
      short s,i,j,k;
      float t;

      void sir(),sir2(const short&,const short&,const short&),sirFD(const short&,const short&,const short&);
	  void plane_approx(const short &si, const short &sj,const short &sk,const float &w);
	  void sir_at_boundary(const short&,const short&,const short &);
	  bool sir_inside();
	  bool is(short x,short y,short z) {if (i != x) return false;if (j != y) return false;if (k != z) return false;return true;};
      //void iteruj(float x,float y, const float &xn,const float &yn,const float &zn, short it);
};

#endif /* SIET_H */
