#include "headers.h"

char * path()
{
	int i =0;
	int p = 0;
	char cwd[1000000];
	getcwd(cwd,sizeof(cwd));

	int j = strlen(cwd);
	int k = strlen(root);	

	char * temp;
	char final[1000000];
	if (strcmp(cwd,root)==0)
		temp = "~";

	else if(j>k)
	{
		final[p++]='~';
		for(i=0;i<j;i++)
		{
			if(cwd[i]!=root[i])
				final[p++] = cwd[i];
		}
		temp = final;
	}
	else 
		temp = cwd;
	return temp;
}

int prompt()
{
	char hostname[1000000];
	gethostname(hostname,1000000);

	char * username = getenv("USER");

	printf("<%s@%s:%s>",username,hostname,path());
}

int cd(char ** args)
{
	if(args[1]!=NULL)
	{
		if(strcmp(args[1],"~")==0)
		args[1]=root;

		int ret = chdir(args[1]);
		if(ret<0)
			perror("");
	}
	else 	
	{
		int ret = chdir(root);
		if(ret<0)
			perror("");
	}
}

int pwd(char ** args)
{
	char cwd[1000000];
	getcwd(cwd,sizeof(cwd));
	printf("%s\n",cwd);
}

int echo(char ** args)
{
	int i;

	for(i=1;args[i]!=NULL;i++)
		printf("%s ",args[i]);
	printf("\n");
}