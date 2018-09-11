#include "headers.h"

int main()
{
	root = getenv("PWD");
	int i;
	int run=1;
	int st;
	while(run)
	{
		pid_t pid;
		if((pid = waitpid(-1,&st,WNOHANG)) > 0)
		{
			if(WIFEXITED(st))
				printf("%s with pid %d exited Normally.\n",bgprocesses[pid],pid);
		}
		prompt();
		run=getcommand();
	}
	return 0;
}