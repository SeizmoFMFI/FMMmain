#include "global.h"

float ***v,***at;
bool SHOW_INFO = false;
bool SAVE_AT_INTERFACE = false;
bool INIT_AT_INTERFACE = false;

void process_args(int argc,char* argv[]) {
	if (argc < 5) {
		cout<<"a TEST or WRONG input params:"<<endl;
		cout<<argc<<endl;
		for (int i=0;i<argc;i++)
			cout<<argv[i]<<endl;

        argv[1] = "test";
		argv[2] = "0";
		argv[3] = "1"; //show info
		argv[4] = "0"; //save at interface
    }

	if (strcmp(argv[3],"1")==0)
		SHOW_INFO = true;
	if (strcmp(argv[4],"save")==0)
		SAVE_AT_INTERFACE = true;
	if (strcmp(argv[4],"init")==0)
		INIT_AT_INTERFACE = true;
}

int main(int argc, char* argv[]) {
	process_args(argc,argv);

	INFO("reading model");
	Data d = Data(argv[1],argv[2]);
	v = d.read_model();
	INFO("reading model finished");

	at = allocate3D<float>(nx,ny,nz);
	if (INIT_AT_INTERFACE) {
		init_interface(at,d.computation_ID);
	}
	else {
		FORALL
			at[i][j][k]=-2;
		Source s = d.read_source();
		s.excite(1);
	}
	
	int p = 0;
	clock_t c_start = time_start();

	Bod b = Bod(0,0,0,0);
	INFO("MAIN LOOP");
	while ( !pq.empty() ) { 
		b = pq.top();
   		pq.pop();
		b.sir();

		p++;
		if (SHOW_INFO) {
			if (p%10000000 == 0) {
				char c[64];
				sprintf(c,"%.6f out of %.6f completed",p/1000000.f,nx*ny*nz/1000000.f);
				INFO(c,false);
			}
		}
    }

	time(c_start);

	//cout<<"writing output"<<endl;
	Output out;
	out.save_at(&d);

	if (!d.isAdjoint) {
		vector<Receiver> recs = d.read_receivers();
		out.save_arrivals(recs,d);
	}

	time(c_start);

	/*
	out.save_spherical_cuts(s);
	out.save_err_vs_dist(s);
	out.save_err_surface(s);
	*/

	//cout<<"OK. Finished, press anything to exit."<<endl;
	//cin.get();

	if (SAVE_AT_INTERFACE) 
		save_interface(at,d.computation_ID);
}

