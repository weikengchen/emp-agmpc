#ifndef EMP_AGMPC_TEST_H__
#define EMP_AGMPC_TEST_H__
const string circuit_file_location = macro_xstr(EMP_CIRCUIT_PATH) + string("bristol_format/");

template<int nP, int nT=1>
void bench_once(int party, NetIOMP<nP> * ios[nT+1], ThreadPool * pool, string filename) {
	if(party == 1)cout <<"CIRCUIT:\t"<<filename<<endl;
	//string file = circuit_file_location+"/"+filename;
	BristolFormat cf(filename.c_str());

	auto start = clock_start();
	CMPC<nP, nT>* mpc = new CMPC<nP, nT>(ios, pool, party, &cf);
	ios[0]->flush();
	ios[1]->flush();
	double t2 = time_from(start);
//	ios[0]->sync();
//	ios[1]->sync();
	if(party == 1)cout <<"Setup:\t"<<party<<"\t"<< t2 <<"\n"<<flush;

	start = clock_start();
	mpc->function_independent();
	ios[0]->flush();
	ios[1]->flush();
	t2 = time_from(start);
	if(party == 1)cout <<"FUNC_IND:\t"<<party<<"\t"<<t2<<" \n"<<flush;
	
	
	if(party == 1) {
		int cot_limit = mpc->fpre->abit->abit1[2]->ot_limit;
		int cot_used = mpc->fpre->abit->abit1[2]->ot_used;

		cout << "COT limit/used: " << cot_limit << "\t" << cot_used << " \n"<< flush;
		cout <<"FUNC_IND adjusted:\t"<<party<<"\t"<<t2 * (1.0 * cot_used / cot_limit)<<" \n"<<flush;
	}

	start = clock_start();
	mpc->function_dependent();
	ios[0]->flush();
	ios[1]->flush();
	t2 = time_from(start);
	if(party == 1)cout <<"FUNC_DEP:\t"<<party<<"\t"<<t2<<" \n"<<flush;

	bool *in = new bool[cf.n1+cf.n2]; bool *out = new bool[cf.n3];
	memset(in, false, cf.n1+cf.n2);
	start = clock_start();
	mpc->online(in, out);
	ios[0]->flush();
	ios[1]->flush();
	t2 = time_from(start);
//	uint64_t band2 = io.count();
//	if(party == 1)cout <<"bandwidth\t"<<party<<"\t"<<band2<<endl;
	if(party == 1)cout <<"ONLINE:\t"<<party<<"\t"<<t2<<" \n"<<flush;
	delete mpc;
}

#endif// EMP_AGMPC_TEST_HHH
