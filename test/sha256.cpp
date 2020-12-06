#include <emp-tool/emp-tool.h>
#include "emp-agmpc/emp-agmpc.h"
#include "test/test.h"
using namespace std;
using namespace emp;

const static int nP = 3;
const static int nT = 16;

int party, port;
int main(int argc, char** argv) {
	parse_party_and_port(argv, &party, &port);
	if(party > nP)return 0;

	NetIOMP<nP>* ios[nT+1];
	for(int i = 0; i < nT+1; i++) {
		ios[i] = new NetIOMP<nP>(party, port +2*(nP+1)*(nP+1)*i+1);
	}

	ThreadPool pool(2*(nP-1)+2);

	bench_once<nP, nT>(party, ios, &pool, circuit_file_location+"sha-256.txt");
	return 0;
}
