#include "headers.h"

char * readline()
{
	ssize_t bufsize = 0;
	char * buff = NULL;
	getline(&buff,&bufsize,stdin);
	return buff;
}

char ** split_command(char * line)
{
	int bufsize = 64;
	char ** commands = malloc(sizeof(char *) * bufsize);
	char * command;
	int pos = 0;
	command = strtok(line,";");
	while(command!=NULL)
	{
		commands[pos] = command;
		pos++;
		if(pos>=bufsize)
		{
			bufsize+=bufsize;
			commands = realloc(commands,bufsize);
		}
		command = strtok(NULL,";");
	}
	commands[pos]=NULL;
	return commands;
}
	
char ** read_command(char * line)
{
	int bufsize = 64;
	char ** commands = malloc(sizeof(char *) * bufsize);
	char * command;
	int pos = 0;
	command = strtok(line," \t\n\r\a");
	while(command!=NULL)
	{
		commands[pos] = command;
		pos++;
		if(pos>=bufsize)
		{
			bufsize+=bufsize;
			commands = realloc(commands,bufsize);
		}
		command = strtok(NULL," \t\n\r\a");
	}
	commands[pos]=NULL;
	return commands;
}

int getcommand()
{
	int i;
	int j;
	int and = 0;
	char * line = readline();
	char ** tokens = split_command(line);

	for(i=0;tokens[i]!=NULL;i++)
	{
		int flag = 0;
		char ** commands = read_command(tokens[i]);
		int len;

		if(commands[0]==NULL)
			return 1;

		if (strcmp(commands[0],"exit")==0)
			return 0;

		len = strlen(commands[0]);

		if(commands[0][len-1]=='&')
		{
			and = 1;
			commands[0][len-1]='\0';
		}

		if(strcmp(commands[0],"remindme")==0)
			and = 1;

		if(strcmp(commands[0],"pinfo")==0)
			pinfo(commands);

		else if(strcmp(commands[0],"clock")==0)
			my_clock(commands);

		else
		{
			int pid=fork();
			int st;
			if(pid==0)
			{
				if (strcmp(commands[0],"cd")==0)
					cd(commands);
				else if (strcmp(commands[0],"pwd")==0)
					pwd(commands);

				else if (strcmp(commands[0],"echo")==0)
					echo(commands);

				else if (strcmp(commands[0],"ls")==0)
					ls(commands);


				else if(strcmp(commands[0],"remindme")==0)
				{
					int lap;
					int i;
					sscanf(commands[1],"%d",&lap);
					sleep(lap);
					for(j=2;commands[j]!=NULL;j++)
						printf("%s ",commands[j]);
					printf("\n");
				}
				else
				{
					if(execvp(commands[0],commands)<0)
						printf("Command Not Found\n");
				}
				exit(0);
			}
			else 
			{
				if(!and)
					waitpid(pid,&st,WUNTRACED);
				else 
				{
					bgprocesses[pid]=commands[0];
					continue;
				}
			}
		}
	}
	return 1;
}