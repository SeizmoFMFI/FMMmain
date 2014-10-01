#ifndef SOURCE_H
#define SOURCE_H

class Source {
public:
	Source(float xx,float yy,float zz);
	const float x,y,z;
	void excite(int radius);
};

#endif