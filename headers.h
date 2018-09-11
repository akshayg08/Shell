#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <wait.h>
#include <fcntl.h>

char * root;
char * bgprocesses[1000000];

char * path();
char ** read_command(char * line);
char ** split_command(char * line);
char * readline();
int prompt();
int cd(char ** args);
int pwd(char ** args);
int echo(char ** args);
int ls_details(struct stat buf,struct dirent * ent);
int ls_display(struct dirent * ent,DIR * dir,int l,int a,char * arg);
int ls(char ** args);
void pinfo(char ** args);
int getcommand();
int my_clock(char ** args);
