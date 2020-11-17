#include "files.h"
#include <stdio.h>
#include "System.h"

long pr_due=0;

void bprintf(args,arg1,arg2,arg3,arg4,arg5,arg6,arg7)
char *args,*arg1,*arg2,*arg3,*arg4,*arg5,*arg6,*arg7;
    {
    char x[256],a[40];  /* Max 240 chars/msg */
    long ct;
    sprintf(x,args,arg1,arg2,arg3,arg4,arg5,arg6);
if(strlen(x)>235)
{
syslog("Bprintf Short Buffer overflow");
crapup("Internal Error in BPRINTF");
}
    /* Now we have a string of chars expanded */
    quprnt(x);
    }

 /* The main loop */

void dcprnt(str,file)
 char *str;
 FILE *file;
    {
    long ct;
    ct=0;
    while(str[ct])
       {
       if(str[ct]!='\001'){fputc(str[ct++],file);continue;}
       ct++;
       switch(str[ct++])
          {
          case 'f':
             ct=pfile(str,ct,file);continue;
          case 'd':
             ct=pndeaf(str,ct,file);continue;
          case 's':
             ct=pcansee(str,ct,file);continue;
          case 'p':
             ct=prname(str,ct,file);continue;
          case 'c':
             ct=pndark(str,ct,file);continue;
          case 'P':
             ct=ppndeaf(str,ct,file);continue;
          case 'D':
             ct=ppnblind(str,ct,file);continue;
          case 'l':
             ct=pnotkb(str,ct,file);continue;
          default:
             strcpy(str,"");
             loseme();crapup("Internal $ control sequence error\n");
             }
       }
    }

int pfile(str,ct,file)
 char *str;
 FILE *file;
    {
    extern long debug_mode;
    char x[128];
    ct=tocontinue(str,ct,x,128);
    if(debug_mode) fprintf(file,"[FILE %s ]\n",str);
    f_listfl(x,file);
    return(ct);
    }

int pndeaf(str,ct,file)
 char *str;
 FILE *file;
    {
    char x[256];
    extern long ail_deaf;
    ct=tocontinue(str,ct,x,256);
    if(!ail_deaf)fprintf(file,"%s",x);
    return(ct);
    }

 pcansee(str,ct,file)
 char *str;
 FILE *file;
    {
    char x[25];
    char z[257];
    long a;
    ct=tocontinue(str,ct,x,23);
    a=fpbns(x);
    if(!seeplayer(a))
       {
       ct=tocontinue(str,ct,z,256);
       return(ct);
       }
    ct=tocontinue(str,ct,z,256);
    fprintf(file,"%s",z);
    return(ct);
    }

 prname(str,ct,file)
 char *str;
 FILE *file;
    {
    char x[24];
    ct=tocontinue(str,ct,x,24);
    if(!seeplayer(fpbns(x)))
    fprintf(file,"Someone");
    else
      fprintf(file,"%s",x);
    return(ct);
    }


int pndark(str,ct,file)
 char *str;
 FILE *file;
    {
    char x[257];
    extern long ail_blind;
    ct=tocontinue(str,ct,x,256);
    if((!isdark())&&(ail_blind==0))
    fprintf(file,"%s",x);
    return(ct);
    }

int tocontinue(str,ct,x,mx)
 char *str;
 long ct;
 char *x;
 long mx;
    {
    long s;
    s=0;
    while(str[ct]!='\001')
       {
       x[s++]=str[ct++];
       }
    x[s]=0;
if(s>=mx)
{
syslog("IO_TOcontinue overrun");
strcpy(str,"");
crapup("Buffer OverRun in IO_TOcontinue");
}
    return(ct+1);
    }

int seeplayer(x)
    {
    extern long mynum;
    extern long ail_blind;
    extern long curch;
    if(x==-1) return(1);
    if(mynum==x) {return(1);} /* me */
    if(plev(mynum)<pvis(x)) return(0);
    if(ail_blind) return(0); /* Cant see */
    if((curch==ploc(x))&&(isdark(curch)))return(0);
    setname(x);
    return(1);
    }
int ppndeaf(str,ct,file)
 char *str;
 FILE *file;
    {
    char x[24];
    extern long ail_deaf;
    long a;
    ct=tocontinue(str,ct,x,24);
    if(ail_deaf) return(ct);
    a=fpbns(x);
    if(seeplayer(a)) fprintf(file,"%s",x);
    else
      fprintf(file,"Someone");
    return(ct);
    }

int  ppnblind(str,ct,file)
char *str;
FILE *file;
    {
    extern long ail_blind;
    char x[24];
    long a;
    ct=tocontinue(str,ct,x,24);
    if(ail_blind) return(ct);
    a=fpbns(x);
    if(seeplayer(a)) fprintf(file,"%s",x);
    else
       fprintf(file,"Someone");
    return(ct);
    }

char *sysbuf=NULL;

void makebfr()
    {
    extern char *sysbuf;
    extern char *malloc();
    sysbuf=malloc(4096); /* 4K of chars should be enough for worst case */
    if(sysbuf==NULL) crapup("Out Of Memory");
    sysbuf[0]=0;
    }
    
FILE * log_fl= 0; /* 0 = not logging */

void logcom()
    {
    extern FILE * log_fl;
    extern char globme[];
    if(getuid()!=geteuid()) {bprintf("\nNot allowed from this ID\n");return;}
    if(log_fl!=0)
       {
       fprintf(log_fl,"\nEnd of log....\n\n");
       fclose(log_fl);
       log_fl=0;
       bprintf("End of log\n");
       return;
       }
    bprintf("Commencing Logging Of Session\n");
    log_fl=fopen("mud_log","a");
    if(log_fl==0) log_fl=fopen("mud_log","w");
    if(log_fl==0)
       {
       bprintf("Cannot open log file mud_log\n");
       return;
       }
    bprintf("The log will be written to the file 'mud_log'\n");
    }

long pr_qcr; 

void pbfr()
    {
    FILE *fln;
    long mu;
    block_alarm();
    closeworld();
    if(strlen(sysbuf)) pr_due=1;
    if((strlen(sysbuf))&&(pr_qcr)) putchar('\n');
    pr_qcr=0;
    if(log_fl!=NULL)
       {
       iskb=0;
       dcprnt(sysbuf,log_fl);
       }
    if(snoopd!=-1)
       {
       fln=opensnoop(pname(snoopd),"a");
       if(fln>0)
          {
iskb=0;
          dcprnt(sysbuf,fln);
          fcloselock(fln);
          }
       }
    iskb=1;
    dcprnt(sysbuf,stdout);
    sysbuf[0]=0; /* clear buffer */
    if(snoopt!=-1) viewsnoop();
    unblock_alarm();
    }

long iskb=1;

void quprnt(x)
 char *x;
    {
    if((strlen(x)+strlen(sysbuf))>4095)
       {
       strcpy(sysbuf,"");
       loseme();
       syslog("Buffer overflow on user %s",globme);
       crapup("PANIC - Buffer overflow");
       }
    strcat(sysbuf,x);
    }

int pnotkb(str,ct,file)
 char *str;
 FILE *file;
    {
    extern long iskb;
    char x[128];
    ct=tocontinue(str,ct,x,127);
    if(iskb) return(ct);
    fprintf(file,"%s",x);
    return(ct);
    }

long snoopd= -1;

FILE *opensnoop(user,per)
char *per;
char *user;
    {
    FILE *x;
    extern FILE *openlock();
    char z[256];
    sprintf(z,"%s%s",SNOOP,user);
    x=openlock(z,per);
    return(x);
    }

long snoopt= -1;

char sntn[32];

void snoopcom()
    {
    FILE *fx;
    long x;
    if(my_lev<10)
       {
       bprintf("Ho hum, the weather is nice isn't it\n");
       return;
       }
    if(snoopt!=-1)
       {
       bprintf("Stopped snooping on %s\n",sntn);
       snoopt= -1;
       sendsys(sntn,globme,-400,0,"");
       }
    if(brkword()== -1)
       {
       return;
       }
    x=fpbn(wordbuf);
    if(x==-1)
       {
       bprintf("Who is that ?\n");
       return;
       }
    if(((my_lev<10000)&&(plev(x)>=10))||(ptstbit(x,6)))
       {
       bprintf("Your magical vision is obscured\n");
       snoopt= -1;
       return;
       }
    strcpy(sntn,pname(x));
    snoopt=x;
    bprintf("Started to snoop on %s\n",pname(x));
    sendsys(sntn,globme,-401,0,"");
    fx=opensnoop(globme,"w");
    fprintf(fx," ");
    fcloselock(fx);
    }

void viewsnoop()
    {
    long x;
    char z[128];
    FILE *fx;
    fx=opensnoop(globme,"r+");
    if(snoopt==-1) return;
    if(fx==0)return;
    while((!feof(fx))&&(fgets(z,127,fx)))
           printf("|%s",z);
    ftruncate(fileno(fx),0);
    fcloselock(fx);
    x=snoopt;
    snoopt= -1;
    /*
    pbfr();
    */
    snoopt=x;
    }
void chksnp()
{
if(snoopt==-1) return;
sendsys(sntn,globme,-400,0,"");
}
 
void setname(x)  /* Assign Him her etc according to who it is */
long x;
{
	if((x>15)&&(x!=fpbns("riatha"))&&(x!=fpbns("shazareth")))
	{
		strcpy(wd_it,pname(x));
		return;
	}
	if(psex(x)) strcpy(wd_her,pname(x));
	else strcpy(wd_him,pname(x));
	strcpy(wd_them,pname(x));
}
