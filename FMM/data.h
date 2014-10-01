#ifndef DATA_H
#define DATA_H
#include "source.h"
#include "receiver.h"

class Data {
public:
	Data(char*,char*);
	float*** read_model();
	Source read_source();
	vector<Receiver> read_receivers();
	float getDh() {return dh;};
const char* name;
const int computation_ID;

	int out_sparse;
	bool isAdjoint;
private:
	float x_width_in_m;
	int mx,my,mz;
	float dh;

	char model_filename[32];
	void read_data();
	void interpolate(unsigned short*** src,float*** dest);
};

#endif