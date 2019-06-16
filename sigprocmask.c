#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<stdlib.h>
 
int main(){


	sigset_t set,oldset;
	sigemptyset(&set);
	sigfillset(&set);
	sigprocmask(SIG_BLOCK,&set,&oldset);
	getchar();
	sigprocmask(SIG_UNBLOCK,&set ,NULL);
	//sigprocmask(SIG_BLOCK,&set,&oldset);
	return 0;
}
