//Magic
#pragma GCC optimize "Ofast"
//stack resize,change esp to rsp if 64-bit system
asm("mov %0,%%esp\n" ::"g"(mem+10000000));
//linux stack resize
#include<sys/resource.h>
void increase_stack(){
	const rlim_t ks=64*1024*1024;
	struct rlimit rl;
	int res=getrlimit(RLIMIT_STACK,&rl);
	if(!res&&rl.rlim_cur<ks){
		rl.rlim_cur=ks;
		res=setrlimit(RLIMIT_STACK,&rl);
	}
}
