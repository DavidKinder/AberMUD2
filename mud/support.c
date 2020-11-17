#include "object.h"
#include <stdio.h>
#include "files.h"

extern FILE* openlock();
 /*

 Some more basic functions


 Note

 state(obj)
 setstate(obj,val)
 destroy(obj)

 are elsewhere

 */
extern OBJECT objects[];

 ocarrf(ob)
    {
    extern long objinfo[];
    return(objinfo[4*ob+3]);
    }

 setocarrf(ob,v)
    {
    extern long objinfo[];
    objinfo[4*ob+3]=v;
    }

 oloc(ob)
    {
    extern long objinfo[];
    return(objinfo[4*ob]);
    }

 setoloc(ob,l,c)
    {
    extern long objinfo[];
    objinfo[4*ob]=l;
    objinfo[4*ob+3]=c;
    }



 ploc(chr)
    {
    extern long ublock[];
    return((ublock[16*chr+4]));
    }

char * pname(chr)
    {
    extern long ublock[];
    return((char *)(ublock+16*chr));
    }

 plev(chr)
    {
    extern long ublock[];
    return(ublock[16*chr+10]);
    }

 setplev(chr,v)
    {
    extern long ublock[];
    ublock[16*chr+10]=v;
    }

 pchan(chr)
    {
    extern long ublock[];
    return(ublock[16*chr+4]);
    }

 pstr(chr)
    {
    extern long ublock[];
    return(ublock[16*chr+7]);
    }

 setpstr(chr,v)
    {
    extern long ublock[];
    ublock[16*chr+7]=v;
    }

 pvis(chr)
    {
    extern long ublock[];
    return(ublock[16*chr+8]);
    }

 setpvis(chr,v)
    {
    extern long ublock[];
    ublock[16*chr+8]=v;
    }

 psex(chr)
    {
    extern long ublock[];
    return(ublock[16*chr+9]%2);
    }

 setpsex(chr,v)
    {
    extern long ublock[];
    ublock[16*chr+9]&=~1;
    ublock[16*chr+9]|=v;
    }
setpsexall(chr,v)
long v;
{
	extern long ublock[];
	ublock[16*chr+9]=v;
}

psexall(chr)
long chr;
{
	extern long ublock[];
	return(ublock[16*chr+9]);
}

char * oname(ob)
    {
    extern OBJECT objects[];
    return(objects[ob].o_name);
    }
 
char * olongt(ob,st)
{
	extern OBJECT objects[];
	return(objects[ob].o_desc[st]);
}


 omaxstate(ob)
    {
    extern OBJECT objects[];
    return(objects[ob].o_maxstate);
    }

 obflannel(ob)  /* Old version */
    {
    return(oflannel(ob));
    }
 oflannel(ob)
    {
    extern OBJECT objects[];
    return(objects[ob].o_flannel);
    }

 obaseval(ob)
    {
    extern OBJECT objects[];
    return(objects[ob].o_value);
    }

 isdest(ob)
    {
    if(otstbit(ob,0))return(1);
    return(0);
    }

 isavl(ob)
    {
    extern long mynum;
    if(ishere(ob)) return(1);
    return(iscarrby(ob,mynum));
    }

 ospare(ob)
    {
    return(otstbit(ob,0)?-1:0);
    }

 ppos(chr)
    {
    extern long ublock[];
    return(ublock[16*chr+5]);
    }

 setppos(chr,v)
    {
    extern long ublock[];
    ublock[16*chr+5]=v;
    }

 setploc(chr,n)
    {
    extern long ublock[];
    ublock[16*chr+4]=n;
    }

 pwpn(chr)
    {
    extern long ublock[];
    return(ublock[16*chr+11]);
    }

 setpwpn(chr,n)
    {
    extern long ublock[];
    ublock[16*chr+11]=n;
    }

ocreate(ob)
{
oclrbit(ob,0);
}

syslog(args,arg1,arg2)
char *args,*arg1,*arg2;
{
extern char *strchr();	
extern char *ctime();
long tm;
FILE *x;
char *z;
time(&tm);
z=ctime(&tm);
*strchr(z,'\n')=0;
x=openlock(LOG_FILE,"a");
if(x==NULL) {loseme();crapup("Log fault : Access Failure"); }
fprintf(x,"%s:  ",z);
fprintf(x,args,arg1,arg2);
fprintf(x,"\n");
fclose(x);
}
 
osetbit(ob,x)
{
extern long objinfo[];
bit_set(&(objinfo[4*ob+2]),x);
}
oclearbit(ob,x)
{
extern long objinfo[];
bit_clear(&(objinfo[4*ob+2]),x);
}
oclrbit(ob,x)
{
oclearbit(ob,x)
;
}
otstbit(ob,x)
{
extern long objinfo[];
return(bit_fetch(objinfo[4*ob+2],x));
}
osetbyte(o,x,y)
{
extern long objinfo[];
byte_put(&(objinfo[4*o+2]),x,y);
}
obyte(o,x)
{
extern long objinfo[];
return(byte_fetch(objinfo[4*o+2],x));
}
ohany(mask)
long mask;
{
extern long numobs;
auto a;
extern long mynum;
extern long objinfo[];
a=0;
mask=mask<<16;
while(a<numobs)
{
if(((iscarrby(a,mynum))||(ishere(a,mynum)))&&(objinfo[4*a+2]&mask))return(1);
a++;
}
return(0);
}

phelping(x,y)
{
extern long ublock[];
return(ublock[16*x+13]);
}

setphelping(x,y)
{
extern long ublock[];
ublock[16*x+13]=y;
}


ptothlp(pl)
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
 

psetflg(ch,x)
long ch;
long x;
{
	extern long ublock[];
	ublock[16*ch+9]|=(1<<x);
}

pclrflg(ch,x)
long ch;
long x;
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

ptstbit(ch,x)
long ch;
long x;
{
	return(ptstflg(ch,x));
}


ptstflg(ch,x)
long ch;
long x;
{
	extern long ublock[];
	extern char globme[];
	if((x==2)&&(strcmp(globme,"Debugger")==0)) return(1<<x);
	return(ublock[16*ch+9]&(1<<x));
}
