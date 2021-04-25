#include <stdio.h>
#include <string.h>
#include <sys/errno.h>
#include <sys/file.h>

#include "object.h"
#include "System.h"
#include "functions.h"

void qcrypt(char *in,char *out,int len)
{
	strncpy(out,in,len);
}

void dcrypt(char *in,char *out,int len)
{
	strncpy(out,in,len);
}

void cls(void)
{
/*
 *	This isnt used on unix
 *
 */
	;
}

int ttyt=0;

void getty(void)
{
/*
 *	We dont use this on the unix version
 *
 */
	
	;
}

FILE *openlock(file,perm)
char *file;
char *perm;
    {
    FILE *unit;
    long ct;
    extern int errno;
    extern char globme[];
    ct=0;
   unit=fopen(file,perm);
   if(unit==NULL) return(unit);
   /* NOTE: Always open with R or r+ or w */
intr:if(flock(fileno(unit),LOCK_EX)== -1)
		if(errno==EINTR) goto intr; /* INTERRUPTED SYSTEM CALL CATCH */
    return(unit);
    }

void fcloselock(FILE* file)
{
	flock(fileno(file),LOCK_UN);
	fclose(file);
}
	

int validname(name)
 char *name;
    {
    long a;
    if(resword(name)){printf("Sorry I cant call you that\n");return(0);  }
    if(strlen(name)>10)
       {
       return(0);
       }
    a=0;
    while(name[a])
       {
       if(name[a]==' ')
          {
          return(0);
          }
       a++;
       }
    if(fobn(name)!=-1)
       {
      printf("I can't call you that , It would be confused with an object\n");
       return(0);
       }
    return(1);
    }
 
int resword(char *name)
{
if(!strcmp(name,"The")) return(1);
if(!strcmp(name,"Me")) return(1);
if(!strcmp(name,"Myself")) return(1);
if(!strcmp(name,"It")) return(1);
if(!strcmp(name,"Them")) return(1);
if(!strcmp(name,"Him")) return(1);
if(!strcmp(name,"Her")) return(1);
if(!strcmp(name,"Someone")) return(1);
if(!strcmp(name,"There")) return(1);
return(0);
}

	

extern OBJECT objects[];

long fobn(char *name)
{
	int ct=0;
	char x[32];
	strcpy(x,name);
	lowercase(x);
	while(ct<NOBS)
	{
		if(strcmp(x,objects[ct].o_name)==0) return(ct);
		ct++;
	}
	return(-1);
}
