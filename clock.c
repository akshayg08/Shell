#include "headers.h"

int flag = 0;

void signalhandler(int signum)
{
    printf("Clock exited normally.\n");
    fflush(stdout);
    flag = 1;
    return ;
}

int my_clock(char **args)
{
    flag=0;
	if(args[1]==NULL)
		perror("");
	else if(args[2]==NULL)
		perror("");
	else if(strcmp(args[1],"-t"))
		perror("");

    while(1)
    {
        char *date =malloc(sizeof(char)*1000);
        char *time = malloc(sizeof(char)*1000);
        signal(SIGTSTP,signalhandler);
        signal(SIGINT,signalhandler);
        char new_date[100];
        char new_time[100];
        int temp;

        if(flag)
            return 1;

        strcpy(date,"/sys/class/rtc/rtc0/date");
        strcpy(time,"/sys/class/rtc/rtc0/time");

        FILE *f1 = fopen(date,"r");
        FILE *f2 = fopen(time,"r");

        if(f1==NULL || f2==NULL)
        {
            perror("");
            return 0;
        }
        
        fscanf(f1,"%s",new_date);
        fscanf(f2,"%s",new_time);

        printf("%s, %s\n",new_date,new_time);
        fclose(f1);
        fclose(f2);
        sscanf(args[2],"%d",&temp);
        sleep(temp);
    }
    return 1;
}