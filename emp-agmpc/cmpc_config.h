#ifndef __CMPC_CONFIG
#define __CMPC_CONFIG
const static int abit_block_size = 1024;
const static int fpre_threads = 1;
#define LOCALHOST

#ifdef __clang__
	#define __MORE_FLUSH
#endif

//#define __debug
const static char *IP[] = {""
,	"172.31.1.137"
,	"172.31.15.170"
,	"172.31.12.22"
,	"172.31.13.61"
,	"172.31.7.45"};

const static bool lan_network = false;
#endif// __C2PC_CONFIG
