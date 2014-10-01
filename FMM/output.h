#ifndef OUTPUT_H
#define OUTPUT_H
#include "global.h"

class Output {
public:
	void save_at(Data *d);
	void save_arrivals(vector<Receiver> receivers,const Data &d);
	void save_spherical_cuts(const Source &);
	void save_err_vs_dist(const Source &);
	void save_err_surface(const Source &);
};

#endif