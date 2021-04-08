/* Function declarations for Abermud.
 * The file was not part of the original Abermud distribution.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

/* bbc.c */
void btmscr(void);
void topscr(void);

/* blib.c */
void addchar(char *str,char ch);
int any(char ch,char *str);
char *cuserid(char *str);
void f_listfl(char *name,FILE *file);
void gepass(char *str);
char *getstr(FILE *file,char *st);
char *lowercase(char *str);
long numarg(char *str);
int scan(char *out,char *in,int start,char *skips,char *stops);
void sec_read(FILE *unit,long *block,long pos,long len);
void sec_write(FILE *unit,long *block,long pos,long len);
char *trim(char *str);
char *uppercase(char *str);

/* blood.c */
void bloodrcv(long *array,int isme);
void breakitem(int x);
void hitplayer(long victim,long wpn);
void killcom(void);
void weapcom(void);

/* bprintf.c */
void bprintf(char* args, ...);
void chksnp(void);
void logcom(void);
void makebfr(void);
void pbfr(void);
FILE *opensnoop(char *user,char *per);
int pcansee(char *str,int ct,FILE *file);
int pfile(char *str,int ct,FILE *file);
int pndark(char *str,int ct,FILE *file);
int pndeaf(char *str,int ct,FILE *file);
int pnotkb(char *str,int ct,FILE *file);
int ppnblind(char *str,int ct,FILE *file);
int ppndeaf(char *str,int ct,FILE *file);
int prname(char *str,int ct,FILE* file);
void quprnt(char *x);
int seeplayer(int x);
void setname(long x);
void snoopcom(void);
int tocontinue(char *str,long ct,char *x,long mx);
void viewsnoop(void);

/* extra.c */
void desrm(int loc,int cf);
void edit_world(void);
void examcom(void);
long getnarg(long bt,long to);
void helpcom(void);
void incom(void);
void jumpcom(void);
void levcom(void);
long phelping(int x);
void smokecom(void);
void stacom(void);
void statplyr(void);
void valuecom(void);
void wherecom(void);
void wizlist(void);

/* frob.c */
void frobnicate(void);

/* gamego.c */
void block_alarm(void);
void crapup(char *str);
char *getkbd(char *s,int l);
void listfl(char *name);
void set_progname(int n, char *text);
void sig_aloff(void);
void sig_alon(void);
void sig_ctrlc(int sig);
void sig_init(void);
void sig_occur(int sig);
void sig_oops(int sig);
void unblock_alarm(void);

/* gmain2.c */
int chkname(char *user);
int chkbnid(char *user);
void chknolog(void);
void deluser(void);
void ed_fld(char *name,char *string);
void edituser(void);
void login(char *user);
void logpass(char *uid);
long logscan(char *uid,char *block);
void showuser(void);
long shu(char *name,char *block);

/* gmainstubs.c */
void cls(void);
void dcrypt(char *in,char *out,int len);
void getty(void);
void qcrypt(char *in,char *out,int len);

/* key.c */
void keysetback(void);
void keysetup(void);
void key_input(char *ppt,int len_max);
void key_reprint(void);

/* magic.c */
void delcom(void);
void goloccom(void);
void inviscom(void);
void passcom(void);
int randperc(void);
void ressurcom(void);
void sumcom(void);
void viscom(void);
void wizcom(void);

/* mobile.c */
void chkfight(int x);
void consid_move(int x);
void crashcom(void);
void dircom(void);
void dorune(void);
int dragget(void);
void helpchkr(void);
void on_timing(void);
void onlook(void);
void singcom(void);
void spraycom(void);
void sys_reset(void);

/* ndebug.c */
void chpwd(char *user);
void debug2(void);
int delu2(char *name);

/* newuaf.c */
void delpers(char *name);
void initme(void);
FILE *openuaf(char *perm);
int resword(char *name);
void saveme(void);
int validname(char *name);

/* new1.c */
void addforce(char *x);
void blindcom(void);
void blowcom(void);
void bouncecom(void);
int canwear(int a);
void changecom(void);
int chkblind(void);
int chkcrip(void);
int chkdeaf(void);
int chkdumb(void);
void closecom(void);
void cripplecom(void);
void cuddlecom(void);
void curecom(void);
int damof(int n);
void deafcom(void);
void destroy(int ob);
void dumbcom(void);
void extinguishcom(void);
void fireballcom(void);
void forcecom(void);
void forchk(void);
void gropecom(void);
void hugcom(void);
int iam(char *x);
int iswornby(int item, int chr);
void kisscom(void);
void lightcom(void);
void lockcom(void);
void mhitplayer(int mon,int mn);
void missilecom(void);
void new1rcv(int isme,int chan,char *to,char *from,int code,char *text);
int ohereandget(long *onm);
void on_flee_event(void);
void opencom(void);
void pushcom(void);
void putcom(void);
void resetplayers(void);
void screamcom(void);
void set_state(int o,int v);
void setcarrf(int o,int n);
void sighcom(void);
void sillytp(int per,char *msg);
void shockcom(void);
void squeezecom(void);
void slapcom(void);
void starecom(void);
int state(int ob);
void removecom(void);
int tscale(void);
void teletrap(long newch);
void ticklecom(void);
void unlockcom(void);
long vicbase(long *x);
long vicf2(long *x,int f1);
long vicfb(long *x);
long vichere(long *x);
long vichfb(long *x);
long victim(long *x);
void wavecom(void);
void wearcom(void);
void wounded(int n);
void woundmn(int mon,int am);

/* objsys.c */
void aobjsat(int loc,int mode);
void disle3(int n,int s);
void disl4(int n,int s);
void dispuser(int ubase);
void dropitem(void);
void dumpitems(void);
void dumpstuff(int n, int loc);
long fobn(char *word);
long fobna(char *word);
long fobnc(char *word);
long fobncb(char *word,int by);
long fobnh(char *word);
long fobnin(char *word,long ct);
long fobnsys(char *nam,long ctrl,long ct_inf);
long fpbn(char *name);
long fpbns(char *name);
void getobj(void);
int iscarrby(int item, int user);
int iscontin(int o1,int o2);
int ishere(int item);
void inventory(void);
void lisobs(void);
void lispeople(void);
void lobjsat(int loc);
void lojal2(int n);
void oplong(int x);
void usercom(void);
void whocom(void);

/* opensys.c */
void closeworld(void);
FILE *openworld(void);

/* packer.c */
void byte_put(long *x,int y,int z);
int byte_fetch(long x, int y);
int bit_fetch(long x,int y);
void bit_set(long *x, int y);
void bit_clear(long *x, int y);

/* parse.c */
void becom(void);
int brkword(void);
void bugcom(void);
void calibme(void);
int chklist(char *word,char *lista[],int listb[]);
int chkverb(void);
void convcom(void);
void debugcom(void);
void digcom(void);
void doaction(int n);
void dodirn(int n);
void dogive(int ob,int pl);
void dogocom(void);
void dosumm(int loc);
void eatcom(void);
void emptycom(void);
void eorte(void);
void exorcom(void);
int gamecom(char *str);
void gamrcv(long *blok);
void getreinput(char *blob);
void givecom(void);
void inumcom(void);
long levelof(int score);
void lightning(void);
void look_cmd(void);
int Match(char *x,char *y);
FILE *openroom(int n,char* mod);
void playcom(void);
void rawcom(void);
void rescom(void);
void rmeditcom(void);
void rollcom(void);
void saycom(void);
void scorecom(void);
void sendsys(char *to,char *from,long codeword,long chan,char *text);
void set_ms(char *x);
void setherecom(void);
void setincom(void);
void setmincom(void);
void setmoutcom(void);
void setoutcom(void);
void shellcom(void);
void shoutcom(void);
void stealcom(void);
void systat(void);
void tellcom(void);
void tsscom(void);
void typocom(void);
void updcom(void);
void u_system(void);

/* support.c */
int isavl(int ob);
int isdest(int ob);
long obflannel(int ob);
long obaseval(int ob);
int obyte(int o,int x);
long ocarrf(int ob);
void oclearbit(int ob,int x);
void oclrbit(int ob,int x);
void ocreate(int ob);
long oflannel(int ob);
int ohany(long mask);
int oloc(int ob);
char *olongt(int ob, int st);
long omaxstate(int ob);
char *oname(int ob);
void osetbit(int ob,int x);
void osetbyte(int o,int x,int y);
int ospare(int ob);
long otstbit(int ob,int x);
long pchan(int chr);
void pclrflg(long ch,long x);
long plev(int chr);
int ploc(int chr);
char *pname(int chr);
long ppos(int chr);
void psetflg(long ch,long x);
long psex(int chr);
long psexall(long chr);
long pstr(int chr);
int ptothlp(int pl);
long ptstbit(long ch, long x);
long ptstflg(long ch, long x);
long pvis(int chr);
long pwpn(int chr);
void setocarrf(int ob, long v);
void setoloc(int ob,int l,int c);
void setphelping(int x, long y);
void setplev(int chr, long v);
void setploc(int chr, long n);
void setppos(int chr, long v);
void setpsex(int chr, long v);
void setpsexall(int chr, long v);
void setpstr(int chr, long v);
void setpvis(int chr, long v);
void setpwpn(int chr, long n);
void syslog(char *args, ...);

/* tk.c */
void broad(char *mesg);
void cleanup(long *inpbk);
void fcloselock(FILE* file);
long findend(FILE *unit);
void lookin(long room);
void loseme(void);
FILE *openlock(char *file,char *perm);
void putmeon(char *name);
void revise(long cutoff);
void rte(char *name);
void send2(long *block);
int special(char *string,char *name);
int split(long *block,char *nam1,char *nam2,char *work,char *luser);
void sysctrl(long *block,char *luser);
void talker(char *name);
void trapch(long chan);
void update(char *name);

/* weather.c */
void adjwthr(int n);
void blizzardcom(void);
void burpcom(void);
int cancarry(int plyr);
void crycom(void);
void emotecom(void);
void fartcom(void);
void grincom(void);
void groancom(void);
void hiccupcom(void);
int isdark(void);
void laughcom(void);
void longwthr(void);
void moancom(void);
int modifwthr(int n);
int outdoors(void);
void posecom(void);
void praycom(void);
void purrcom(void);
void raincom(void);
void setcom(void);
void setpflags(void);
void setwthr(int n);
void showwthr(void);
void sillycom(char *txt);
void smilecom(void);
void sniggercom(void);
void snowcom(void);
void stormcom(void);
void sulkcom(void);
void suncom(void);
void winkcom(void);
void wthrrcv(int type);
void yawncom(void);

/* zones.c */
int findzone(int x, char *str);
void exits(void);
void loccom(void);
void lodex(FILE *file);
long roomnum(char *str, char *offstr);
void showname(int loc);
