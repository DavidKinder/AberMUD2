extern char lump[];
extern int namegiv;
extern char namegt[];
extern int qnmrq;
extern int ttyt;

extern void main();
extern void chknolog();
extern char * uppercase();
extern char * lowercase();
extern void getty();
extern void cls();
extern void login();
/*extern void syslog(); anachronism*/
extern void listfl();
extern void talker();
extern void crapup(); 
extern void logpass();
extern long logscan();

extern void getunm();
extern void showuser();
extern long shu();
extern void deluser();
extern void edituser();
extern void ed_fld();
extern void delu2();
extern void chpwd();
extern char *getkbd();
extern int chkname(); 

extern FILE *openlock();

extern int resword();
extern int validname();
extern void qcrypt();
extern void dcrypt();
extern void getty();
extern void fcloselock();
extern char *trim();
extern int any();
extern void gepass();
extern int scan();
extern char *getstr();
/*extern void addchar(); anachronism*/
extern long numarg();
extern void sec_read();
extern void sec_write();
extern void f_listfl();
#define NOBS 194

extern long tty;
extern void initscr();
extern void topscr();
extern void btmscr();


extern char globme[];
extern char wordbuf[];
extern FILE *openroom();
extern FILE *openuaf();
extern long in_fight;
extern long fighting;
extern int dambyitem();
extern long wpnheld;
extern void weapcom();
extern long my_lev;
extern long mynum;
extern void hitplayer();
extern long my_sco;
extern long my_str;
extern long curch;
extern void bloodrcv();
extern long me_cal;
extern void breakitem();
extern long pr_due;
/*extern void bprintf(); anachronism*/
extern void dcnprnt();
extern int pfile();
extern int pndeaf();
extern int pcansee();
extern int prname();
extern int pndark();
extern int tocontinue();
extern int seeplayer();
extern int ppndeaf();
extern int ppnblind();
extern char *sysbuf;
extern void makebfr();
extern FILE *log_fl;
extern void logcom();
extern long pr_qcr;
extern void pbfr();
extern FILE *opensnoop();
extern long snoopt;
extern long iskb;
extern long snoopd;
extern void quprnt();
extern int pnotkb();
extern char sntn[];
extern void snoopcom();
extern void viewsnoop();
extern void chksnp();
extern void setname();
extern char wd_it[];
extern char wd_them[];
extern char wd_him[];
extern char wd_her[];


