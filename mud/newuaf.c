#include <errno.h>
#include <stdio.h>
#include "files.h"

extern FILE *openuaf();
extern FILE *openlock();
extern char *oname();
extern char *pname();

extern char globme[];

struct uaf_being
{
	char p_name[16];
	long p_score;
	long p_strength;
	long p_sex;
	long p_level;
};

typedef struct uaf_being PERSONA;

long personactl(name,d,act)
char *name;
PERSONA *d;
int act;
{
	FILE *a;
	char c[32],e[32];
	a=openuaf("r+");
	strcpy(e,name);
	lowercase(e);
	while(getpersona(a,d))
	{
		strcpy(c,d->p_name);
		lowercase(c);
		if(strcmp(c,e)==0) 
		{
			switch(act)
			{
			case 0:
				fcloselock(a);
				return(1);
			case 1:	fseek(a,ftell(a)-sizeof(PERSONA),0);
				return((long)a);
			}
		}
	}
	fcloselock(a);	
	return(-1);
}

#define PCTL_GET 0
#define PCTL_FIND 1

findpers(name,x)
char *name;
PERSONA *x;
{
	return(personactl(name,x,PCTL_GET));
}

delpers(name)
char *name;
{
	FILE *i;
	PERSONA x;
l1:	i=(FILE *)personactl(name,&x,PCTL_FIND);
	if(i==(FILE *)-1) return;
	lowercase(name);
	lowercase(x.p_name);
	if(strcmp(x.p_name,name)) 
	       crapup("Panic: Invalid Persona Delete");
	strcpy(x.p_name,"");
	x.p_level= -1;
	fwrite(&x,sizeof(PERSONA),1,i);
	fcloselock(i);
	goto l1;
}



putpers(name,pers)
char *name;
PERSONA *pers;
{
	FILE *i;
	unsigned long flen;
	PERSONA s;
	i=(FILE *)personactl(name,&s,PCTL_FIND);
	if(i==(FILE *)-1)
	{
		flen= -1;
		i=(FILE *)personactl("",&s,PCTL_FIND);
		if(i!=(FILE *)-1) goto fiok;
		i=openuaf("a");
		flen=ftell(i);
        fiok: 	if(fwrite(pers,sizeof(PERSONA),1,i)!=1)
		{
			bprintf("Save Failed - Device Full ?\n");
			if(flen!=-1)ftruncate(fileno(i),flen);
			fcloselock(i);
			return;
		}
		fcloselock(i);
		return;
	}
	fwrite(pers,sizeof(PERSONA),1,i);
	fcloselock(i);
}

FILE *openuaf(perm)
char *perm;
{
	FILE *i;
	i=openlock(UAF_RAND,perm);
	if(i==NULL)
	{
		crapup("Cannot access UAF\n");
	}
	return(i);
}

decpers(pers,name,str,score,lev,sex)
PERSONA *pers;
char *name;
long *str,*score,*lev,*sex;
{
	strcpy(name,pers->p_name);
	*str=pers->p_strength;
	*score=pers->p_score;
	*lev=pers->p_level;
	*sex=pers->p_sex;
}

long my_sco;
long my_lev;
long my_str;
long my_sex;

initme()
{
	PERSONA x;
	char s[32];
	extern char globme[];
	errno=0;
	if(findpers(globme,&x)!=-1)
	{
		decpers(&x,s,&my_str,&my_sco,&my_lev,&my_sex);
		return;
	}
	if(errno!=0) crapup("Panic: Timeout event on user file\n");
	x.p_score=0;
	bprintf("Creating character....\n");
	my_sco=0;
	my_str=40;
	my_lev=1;
	moan1:bprintf("\nSex (M/F) : ");
	pbfr();
	keysetback();
	getkbd(s,2);
	keysetup();
	lowercase(s);
	switch(s[0])
	{
		case 'm':my_sex=0;
		break;
		case 'f':my_sex=1;
		break;
		default:bprintf("M or F");
		goto moan1;
	}
	strcpy(x.p_name,globme);
	x.p_strength=my_str;
	x.p_level=my_lev;
	x.p_sex=my_sex;
	x.p_score=my_sco;
	putpers(globme,&x);
}

saveme()
{
	extern char globme[];
	extern long zapped;
	PERSONA x;
	extern int mynum;
	strcpy(x.p_name,globme);
	x.p_strength=my_str;
	x.p_level=my_lev;
	x.p_sex=psexall(mynum);
	x.p_score=my_sco;
	if(zapped) return;
	bprintf("\nSaving %s\n",globme);
	putpers(globme,&x);
}

 validname(name)
 char *name;
    {
    long a;
    if(resword(name)){bprintf("Sorry I cant call you that\n");return(0);  }
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
      bprintf("I can't call you that , It would be confused with an object\n");
       return(0);
       }
    return(1);
    }
 
resword(name)
{
if(!strcmp(name,"The")) return(1);
if(!strcmp(name,"Me")) return(1);
if(!strcmp(name,"Myself")) return(1);
if(!strcmp(name,"It")) return(1);
if(!strcmp(name,"Them")) return(1);
if(!strcmp(name,"Him")) return(1);
if(!strcmp(name,"Her")) return(1);
if(!strcmp(name,"Someone")) return(1);
return(0);
}


getpersona(file,pers)
FILE *file;
PERSONA *pers;
{
	if(fread(pers,sizeof(PERSONA),1,file)!=1) return(0);
	return(1);
}
