#include "headers.h"
 
int ls_details(struct stat buf,struct dirent * ent)
{
	int i;
	int fd;
	int save;
	struct group *grp;
	struct passwd *pwd;
	char date[10000];
	pwd = getpwuid(buf.st_uid);
	grp = getgrgid(buf.st_gid);
	printf((S_ISDIR(buf.st_mode))?"d":"-");
	printf((buf.st_mode & S_IRUSR)?"r":"-");
	printf((buf.st_mode & S_IWUSR)?"w":"-");
	printf((buf.st_mode & S_IXUSR)?"x":"-");
	printf((buf.st_mode & S_IRGRP)?"r":"-");
	printf((buf.st_mode & S_IWGRP)?"w":"-");
	printf((buf.st_mode & S_IXGRP)?"x":"-");
	printf((buf.st_mode & S_IROTH)?"r":"-");
	printf((buf.st_mode & S_IWOTH)?"w":"-");
	printf((buf.st_mode & S_IXOTH)?"x":"-");
	printf(" %d",(int)buf.st_nlink);
	printf(" %s",grp->gr_name);
	printf(" %s",pwd->pw_name);
	strftime(date,50,"%b  %d  %R",localtime(&(buf.st_mtime)));
	printf(" %s",date);	
	printf(" %s\n", ent->d_name);
	return 0;
}

int ls_display(struct dirent * ent,DIR * dir,int l,int a,char * arg)
{
	while((ent = readdir(dir))!=NULL)
	{
		char cur[1000000];
		getcwd(cur,sizeof(cur));
		char * result = malloc(sizeof(char)*(sizeof(cur)+sizeof(ent->d_name)+1));
		strcpy(result,cur);
		strcat(result,"/");
		strcat(result,arg);	
		strcat(result,"/");
		strcat(result,ent->d_name);
		if(l & a)
		{
			struct stat buf;
			stat(result,&buf);
			ls_details(buf,ent);
		}
		else if(l & !a)
		{
			if(ent->d_name[0]!='.')
			{
				struct stat buf;
				stat(result,&buf);
				ls_details(buf,ent);
			}
		}
		else if(!l & a)
			printf("%s  ",ent->d_name);

		else if(!l & !a)
		{
			if(ent->d_name[0]!='.')
				printf("%s  ",ent->d_name);
		}
	}
	closedir(dir);
	if(!l)
		printf("\n");
	return 0;
}

int ls(char ** args)
{
	int i;
	int j;
	int l=0;
	int a=0;
	int flag = 0;

	for(i=1;args[i]!=NULL;i++)
	{
		if(strcmp(args[i],"-la")==0)
		{
			l=1;
			a=1;
		}
		else if(strcmp(args[i],"-l")==0)
			l=1;
		else if(strcmp(args[i],"-a")==0)
			a=1;
		else if(strcmp(args[i],"-al")==0)
		{
			l=1;
			a=1;
		}
	}
	for(i=1;args[i]!=NULL;i++)
	{
		if(strcmp(args[i],"-l")!=0 && strcmp(args[i],"-a")!=0 && strcmp(args[i],"-la")!=0 && strcmp(args[i],"-al")!=0)
		{					
			if(strcmp(args[i],"~")==0)
				args[i]=root;

			flag = 1 ;
			DIR * dir;
			struct dirent * ent;
			if((dir=opendir(args[i]))!=NULL)
				ls_display(ent,dir,l,a,args[i]);
			else 
				perror("");

			printf("\n");
		}
	}
	if(!flag)
	{
		DIR * dir;
		struct dirent * ent;
		if((dir=opendir("./"))!=NULL)
			ls_display(ent,dir,l,a,"");
		else
			perror("");
	}
	return 0;
}