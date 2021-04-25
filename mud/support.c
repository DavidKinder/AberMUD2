#include <stdarg.h>
#include <stdio.h>
#include <time.h>

#include "object.h"
#include "files.h"
#include "functions.h"

/*

 Some more basic functions


 Note

 state(obj)
 set_state(obj,val)
 destroy(obj)

 are elsewhere

 */
extern OBJECT objects[];

 long ocarrf(int ob)
    {
    extern long objinfo[];
    return(objinfo[4*ob+3]);
    }

 void setocarrf(int ob, long v)
    {
    extern long objinfo[];
    objinfo[4*ob+3]=v;
    }

 int oloc(int ob)
    {
    extern long objinfo[];
    return(objinfo[4*ob]);
    }

 void setoloc(int ob,int l,int c)
    {
    extern long objinfo[];
    objinfo[4*ob]=l;
    objinfo[4*ob+3]=c;
    }



 int ploc(int chr)
    {
    extern long ublock[];
    return((ublock[16*chr+4]));
    }

char * pname(int chr)
    {
    extern long ublock[];
    return((char *)(ublock+16*chr));
    }

 long plev(int chr)
    {
    extern long ublock[];
    return(ublock[16*chr+10]);
    }

 void setplev(int chr, long v)
    {
    extern long ublock[];
    ublock[16*chr+10]=v;
    }

 long pchan(int chr)
    {
    extern long ublock[];
    return(ublock[16*chr+4]);
    }

 long pstr(int chr)
    {
    extern long ublock[];
    return(ublock[16*chr+7]);
    }

 void setpstr(int chr, long v)
    {
    extern long ublock[];
    ublock[16*chr+7]=v;
    }

 long pvis(int chr)
    {
    extern long ublock[];
    return(ublock[16*chr+8]);
    }

 void setpvis(int chr, long v)
    {
    extern long ublock[];
    ublock[16*chr+8]=v;
    }

 long psex(int chr)
    {
    extern long ublock[];
    return(ublock[16*chr+9]%2);
    }

 void setpsex(int chr, long v)
    {
    extern long ublock[];
    ublock[16*chr+9]&=~1;
    ublock[16*chr+9]|=v;
    }
void setpsexall(int chr, long v)
{
	extern long ublock[];
	ublock[16*chr+9]=v;
}

long psexall(long chr)
{
	extern long ublock[];
	return(ublock[16*chr+9]);
}

char * oname(int ob)
    {
    extern OBJECT objects[];
    return(objects[ob].o_name);
    }
 
char * olongt(int ob, int st)
{
	extern OBJECT objects[];
	return(objects[ob].o_desc[st]);
}


 long omaxstate(int ob)
    {
    extern OBJECT objects[];
    return(objects[ob].o_maxstate);
    }

 long obflannel(int ob)  /* Old version */
    {
    return(oflannel(ob));
    }
 long oflannel(int ob)
    {
    extern OBJECT objects[];
    return(objects[ob].o_flannel);
    }

 long obaseval(int ob)
    {
    extern OBJECT objects[];
    return(objects[ob].o_value);
    }

 int isdest(int ob)
    {
    if(otstbit(ob,0))return(1);
    return(0);
    }

 int isavl(int ob)
    {
    extern long mynum;
    if(ishere(ob)) return(1);
    return(iscarrby(ob,mynum));
    }

 int ospare(int ob)
    {
    return(otstbit(ob,0)?-1:0);
    }

 long ppos(int chr)
    {
    extern long ublock[];
    return(ublock[16*chr+5]);
    }

 void setppos(int chr,long v)
    {
    extern long ublock[];
    ublock[16*chr+5]=v;
    }

 void setploc(int chr,long n)
    {
    extern long ublock[];
    ublock[16*chr+4]=n;
    }

 long pwpn(int chr)
    {
    extern long ublock[];
    return(ublock[16*chr+11]);
    }

 void setpwpn(int chr, long n)
    {
    extern long ublock[];
    ublock[16*chr+11]=n;
    }

void ocreate(int ob)
{
oclrbit(ob,0);
}

void syslog(char *args, ...)
{
long tm;
FILE *x;
char *z;
time(&tm);
z=ctime(&tm);
*strchr(z,'\n')=0;
x=openlock(LOG_FILE,"a");
if(x==NULL) {loseme();crapup("Log fault : Access Failure"); }
fprintf(x,"%s:  ",z);
{
  va_list varargs;
  va_start(varargs,args);
  vfprintf(x,args,varargs);
  va_end(varargs);
  }
/* fprintf(x,args,arg1,arg2); */
fprintf(x,"\n");
fclose(x);
}
 
void osetbit(int ob,int x)
{
extern long objinfo[];
bit_set(&(objinfo[4*ob+2]),x);
}
void oclearbit(int ob,int x)
{
extern long objinfo[];
bit_clear(&(objinfo[4*ob+2]),x);
}
void oclrbit(int ob,int x)
{
oclearbit(ob,x)
;
}
long otstbit(int ob,int x)
{
extern long objinfo[];
return(bit_fetch(objinfo[4*ob+2],x));
}
void osetbyte(int o,int x,int y)
{
extern long objinfo[];
byte_put(&(objinfo[4*o+2]),x,y);
}
int obyte(int o,int x)
{
extern long objinfo[];
return(byte_fetch(objinfo[4*o+2],x));
}
int ohany(long mask)
{
extern long numobs;
int/*auto*/ a;
extern long mynum;
extern long objinfo[];
a=0;
mask=mask<<16;
while(a<numobs)
{
if(((iscarrby(a,mynum))||(ishere(a/*,mynum*/)))&&(objinfo[4*a+2]&mask))return(1);
a++;
}
return(0);
}

long phelping(int x/*,int y*/)
{
extern long ublock[];
return(ublock[16*x+13]);
}

void setphelping(int x, long y)
{
extern long ublock[];
ublock[16*x+13]=y;
}


int ptothlp(int pl)
{
int tot;
extern long maxu;
int ct=0;
while(ct<maxu)
{
if(ploc(ct)!=ploc(pl)){ct++;continue;}
if(phelping(ct)!=pl){ct++;continue;}
return(ct);
}
return(-1);
}
 

void psetflg(long ch,long x)
{
	extern long ublock[];
	ublock[16*ch+9]|=(1<<x);
}

void pclrflg(long ch,long x)
{
	extern long ublock[];
	ublock[16*ch+9]&=~(1<<x);
}

/*Pflags

0 sex

1 May not be exorcised ok

2 May change pflags ok

3 May use rmedit ok

4 May use debugmode ok

5 May use patch 

6 May be snooped upon

*/

long ptstbit(long ch, long x)
{
	return(ptstflg(ch,x));
}


long ptstflg(long ch, long x)
{
	extern long ublock[];
	extern char globme[];
	if((x==2)&&(strcmp(globme,"Debugger")==0)) return(1<<x);
	return(ublock[16*ch+9]&(1<<x));
}
