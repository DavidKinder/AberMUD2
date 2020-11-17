#include <stdio.h>

/*
 
     Two Phase Game System
 
*/
extern FILE *openlock();

char **argv_p;
 
main(argc,argv)
char *argv[];
{
char x[32];
extern char globme[];
extern long tty;
sig_init();
argv_p= argv;
if(argc!=2)
{
	printf("Args!\n");
	exit(0);
}
printf("Entering Game ....\n");
strcpy(x,argv[1]);
tty=0;
/*if(tty==4) {initbbc();initscr();topscr();}*/
if(!strcmp(x,"Phantom")) sprintf(globme,"The %s",x);
else strcpy(globme,x);
printf("Hello %s\n",globme);
syslog("GAME ENTRY: %s[%s]",globme,cuserid(NULL));
keysetup();
talker(globme);
}
 
char privs[4];

crapup(str)
char *str;
{
extern long pr_due;
static char *dashes =
"-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-";
pbfr();
pr_due=0;  /* So we dont get a prompt after the exit */ 
keysetback();
printf("\n%s\n\n%s\n\n%s\n", dashes, str, dashes);
exit(0);
}
 
listfl(name)
char *name;
{
FILE *a;
char b[128];
a=openlock(name,"r+");
while(fgets(b,128,a)) printf("%s\n",b);
fcloselock(a);
}
 
char *getkbd(s,l)   /* Getstr() with length limit and filter ctrl */
 char *s;
 int l;
    {
    char c,f,n;
    f=0;c=0;
    while(c<l)
       {
       regec:n=getchar();
       if ((n<' ')&&(n!='\n')) goto regec;
       if (n=='\n') {s[c]=0;f=1;c=l-1;}
       else
          s[c]=n;
       c++;
       }
    if (f==0) {s[c]=0;while(getchar()!='\n');}
    return(s);
    }

#include <signal.h>

long sig_active=0;

sig_alon()
{
	extern int sig_occur();
	sig_active=1;	
	signal(SIGALRM,sig_occur);
	alarm(2);
}



unblock_alarm()
{
	extern int sig_occur();
	signal(SIGALRM,sig_occur);
	if(sig_active) alarm(2);
}

block_alarm()
{
	signal(SIGALRM,SIG_IGN);
}


sig_aloff()
{
	sig_active=0;	
	signal(SIGALRM,SIG_IGN);
	alarm(2147487643);
}

long interrupt=0;

sig_occur()
{
	extern char globme[];
	if(sig_active==0) return;
	sig_aloff();
	openworld();
	interrupt=1;
	rte(globme);
	interrupt=0;
	on_timing();
	closeworld();
	key_reprint();
	sig_alon();
}

	
sig_init()
{
	extern int sig_oops();
	extern int sig_ctrlc();
	signal(SIGHUP,sig_oops);
	signal(SIGINT,sig_ctrlc);
	signal(SIGTERM,sig_ctrlc);
	signal(SIGTSTP,SIG_IGN);
	signal(SIGQUIT,SIG_IGN);
        signal(SIGCONT,sig_oops);
}

sig_oops()
{
	sig_aloff();
	loseme();
	keysetback();
	exit(255);
}

sig_ctrlc()
{
	extern in_fight;
	printf("^C\n");
	if(in_fight) return;
	sig_aloff();
	loseme();
	crapup("Byeeeeeeeeee  ...........");
}


set_progname(n,text)
char *text;
{
	/*
	int x=0;
	int y=strlen(argv_p[n])+strlen(argv_p[1]);  
	y++;
	if(strcmp(argv_p[n],text)==0) return;
	
	while(x<y)
	   argv_p[n][x++]=0; 
	strcpy(argv_p[n],text);
	*/
}

