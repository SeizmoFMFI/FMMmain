#include "global.h"
#include "queue.h"
#include "siet.h"
using namespace std;

//template <class T>
PQ::PQ(){
	ActiveQueue = 0;
}

//pq cmp fcia
inline bool operator<(const Bod& a1, const Bod& a2) {
	return a1.t > a2.t;	
};

//template <class T>
void PQ::push(Bod item){
	if(pq[ActiveQueue].size()<MaxItemsPerQueue){
		pq[ActiveQueue].push(item);
	} else if(ActiveQueue+1<NumberOfQueues){
           cout<<"pridana queue "<<ActiveQueue+1<<endl;
		pq[++ActiveQueue].push(item);
	} else {
		cout << "Error, PQ-s are full"<<endl;
		cin.get();
	}
	
	//teraz musim zabezpecit prioritnost v mojich queues
	for (int i=ActiveQueue;i>0;i--) {
        Bod a=pq[i].top();
        Bod b=pq[i-1].top();
 
        if (a.t<b.t) {
           pq[i].pop(); //tu ich zmazem
           pq[i-1].pop();
            
           pq[i-1].push(a); //swapujem...
           pq[i].push(b);
        }
        else {
             break;
		}
    }
}

//template <class T>
void PQ::pop(){
	//if PQ is empty, you have problem

	pq[0].pop();
	for (unsigned int i=1;i<=ActiveQueue;i++) {
        Bod ch=pq[i].top();
        pq[i-1].push(ch); //najspodnejsi postupuje do skorsej queue
        pq[i].pop(); //zmazem ho z povodnej
    }

	if(pq[ActiveQueue].empty()&&(ActiveQueue>0)){
		ActiveQueue--;
	}
}

//template <class T>
Bod PQ::top(){
	return pq[0].top();
}

//template <class T>
bool PQ::empty(){
	if((ActiveQueue == 0) && (pq[0].empty()))
		return true;
	else return false;
}

PQ pq;
