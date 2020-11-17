#include <stdio.h>
#include <pwd.h>

/*
 *
 *	B functions and utilities
 *
 */

#include <ctype.h>
#include "System.h"

char *lowercase(str)
char *str;
{
	char *stp=str;
	while(*str)
	{
		if(isupper(*str)) *str=tolower(*str);
		str++;
	}
return(stp);
}

char *uppercase(str)
char *str;
{
	char *stp=str;
	while(*str)
	{
		if(islower(*str)) *str=toupper(*str);
		str++;
	}
return(stp);
}

char *trim(str)
char *str;
{
	char *x;
	x=str+strlen(str);
	while(*x==32)
	{
		*x=0;
		x--;
	}
	return(str);
}

int any(ch,str)
char ch;
char *str;
{
	extern char *strchr();
	if(strchr(str,ch)==NULL) return(-1);
	return(strchr(str,ch)-str);
}

void gepass(str)
{
	char key[33],pw[16];

	strcpy(key,getpass(""));
	strcpy(pw,crypt(key,"XX"));
	strcpy(str,pw);
}

int scan(out,in,start,skips,stops)
char *in,*out,*skips,*stops;
{
	char *in_base=in;
/*	char *sy_ot=out;
	printf("Scan(%s ->%d %d %s %s",in,out,start,skips,stops);*/
	if(strlen(in)<start) {*out=0;return(-1);}
	in+=start;
	while((*in)&&(strchr(skips,*in))) in++;
	if(*in==0) {*out=0;return(-1);}
	while((*in)&&(strchr(stops,*in)==0))
	{
		*out= *in;
		out++;
		in++;
	}
/*	printf(" : Outputting %s\n",sy_ot); */
	*out=0;
	return(in-in_base);
}

char *getstr(file,st)
FILE *file;
char *st;
{
	extern char *strchr();
	if(!fgets(st,255,file)) return(0);
	if(strchr(st,'\n')) *strchr(st,'\n')=0;
	return(st);
}

void addchar(str,ch)
char *str;
char ch;
{
	int x=strlen(str);
	str[x]=ch;
	str[x+1]=0;
}

long numarg(str)
char *str;
{
	long i=0;
	sscanf(str," %ld",&i);
	return(i);
}

sbar()
{
	return(-1); /* Unknown code needed here */
}

void f_listfl(name,file)
char *name;
FILE *file;
{
	FILE *a;
	char x[128];
	a=fopen(name,"r");
	if(a==NULL) fprintf(stderr,"[Cannot find file ->%s ]\n",name);
	else
        {
	while(fgets(x,127,a)) fprintf(file,"%s",x);
        }
}


void sec_read(unit,block,pos,len)
FILE *unit;
long *block;
long pos;
long len;
{
	fseek(unit,pos*64*sizeof(long),0);
	fread((char *)block,len*(sizeof(long)),1,unit);
}

void sec_write(unit,block,pos,len)
FILE *unit;
long *block;
long pos;
long len;
{
	fseek(unit,pos*64*sizeof(long),0);
	fwrite((char *)block,len*(sizeof(long)),1,unit);
}

char *cuserid(str)
char *str;
{
/*
	extern char *strchr();
	getpw(getuid(),ary);
	*strchr(ary,':')=0;
*/
	static char ary[128];
	strcpy(ary,getpwuid(getuid())->pw_name);
	if(str!=NULL) strcpy(str,ary);
	return(ary);
}
	
