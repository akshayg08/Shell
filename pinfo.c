#include "headers.h"

void pinfo(char ** args)
{
	int i;
	int j;
	int flag = 0;
	char * pid;
	char temp[15];
	char result[1000];
	char res1[1000];
	char new[1000];
	char status;
	ssize_t  read;
	size_t p = 0;
	strcpy(result,"/proc/");

	if (args[1]==NULL)
	{
		sprintf(temp,"%d",getpid());
		pid = temp;
	}
	else 
		pid = args[1];

	strcat(result,pid);
	strcpy(res1,result);
	strcat(result,"/exe");
	strcat(res1,"/status");
	char * line;
	FILE * f = fopen(res1,"r");
	if(f==NULL)
	{
		perror("");
		return;
	}
	printf("PID -- %s\n",pid);
	while((read=getline(&line,&p,f))!=-1)
	{
		int k = strlen(line);
		if(line[0]=='S' && line[1]=='t')
			printf("%s\n",line);
		if(line[0]=='V' && line[1]=='m' && line[2]=='S' && line[3]=='i')
			printf("%s\n",line );
	}
	fclose(f);
	char * buf_temp = malloc(sizeof(char)*100000);
	int ret = readlink(result,buf_temp,100000);
	if(ret>0)
		printf("Executable Path: %s\n",buf_temp);
	else 
		perror("");
}