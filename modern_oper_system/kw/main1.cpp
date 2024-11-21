#include <iostream>
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/neutrino.h>
#include <inttypes.h>

int main(){
	int n=5000, switch_count=n*2;
	pid_t pid=fork();
	if(pid==0){
		for(int i=0;i<n;i++) sched_yield();
		return 0;
	}
	unsigned long long start=ClockCycles();
	for(int i=0;i<n;i++) sched_yield();
	unsigned long long end=ClockCycles(), result=end-start;
	std::cout<<"full time = "<<result<<"ns, time for 1 switch = "<<(result/(float)switch_count)<<"ns \n";
	return 0;
}