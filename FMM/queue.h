#ifndef QUEUE_H
#define QUEUE_H
using namespace std;
#include "siet.h"

//template <class T>
class PQ {
private:
	static const unsigned MaxItemsPerQueue = 1000000;
	static const unsigned NumberOfQueues = 100;
	unsigned ActiveQueue;
	priority_queue<Bod,vector<Bod>,less<vector<Bod>::value_type> >  pq[NumberOfQueues];

public:
    void push(Bod item);
	void pop();
    Bod top();
	bool empty();
	int size() {
		return ActiveQueue*MaxItemsPerQueue + pq[ActiveQueue].size();
	}
	PQ();
};
#endif /* QUEUE_H */
