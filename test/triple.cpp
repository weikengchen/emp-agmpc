#include <emp-tool/emp-tool.h>
#include "emp-agmpc/emp-agmpc.h"
using namespace std;
using namespace emp;

const static int nP = 2;
int party, port;
int main(int argc, char** argv) {
	parse_party_and_port(argv, &party, &port);
	if(party > nP)return 0;

	const static int nT = 5;

	NetIOMP<nP>* ios[nT+1];
	for(int i = 0; i < nT+1; i++) {
		ios[i] = new NetIOMP<nP>(party, port +2*(nP+1)*(nP+1)*i+1);
	}

	ThreadPool pool(96);	

	FpreMP<nP, nT> mp(ios, &pool, party);

	int num_ands = 1000 * 1000;
	block * mac[nP+1];
	block * key[nP+1];
	bool * value;

	for(int i = 1; i <= nP; ++i) {
		key[i] = new block[num_ands*3];
		mac[i] = new block[num_ands*3];
	}
	value = new bool[num_ands*3];
	auto t1 = clock_start();
	mp.compute(mac, key, value, num_ands);
	cout <<"Gates: "<<num_ands<<" time: "<<time_from(t1)/num_ands<<endl;
	return 0;
}
