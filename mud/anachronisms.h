#ifndef __anachronisms
#define __anachronisms

// setstate() is not the setstate() from stdlib
#define setstate library_setstate
#include <stdlib.h>
#undef setstate

#include <unistd.h>
#include <string.h>
#include <sys/fcntl.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

// blib.c
char* cuserid(char* str);
void sec_write(FILE* unit, long* block, long pos, long len);
void sec_read(FILE* unit, long* block, long pos, long len);
int scan(char* out, char* in, int start, char* skips, char* stops);
char* getstr(FILE* file, char* st);
long numarg(char* str);
char* lowercase(char* str);

// key.c
int keysetup(); // really returns void
int keysetback(); // really returns void
int key_reprint(); // really returns void
void key_input(char*ppt, int len_max);

// tk.c
FILE* openworld();
void fcloselock(FILE* file);
int loseme();
void putmeon(char* name);
void talker(char* name);
void lookin(long room);
int update(char* name); // really returns void
int broad(char* message); // really returns void
int trapch(long chan); // really returns void
int split(long* block, char* nam1, char* nam2, char* work, char* luser);
int sysctrl(long* block, char* luser); // really returns void
int special(char* string, char* name);
int cleanup(long *inpbk);
int revise(long cutoff);
int send2(long* block);

// parse.c
int Match(char* x, char* y);
void systat();
void u_system();
void calibme();
int brkword();
int chkverb();
void doaction(int n);
int dosumm(int loc);
int levelof(int score);
void dogive(int ob, int pl);
int eorte();
void gamrcv(long* blok);
int gamecom(char* str);
int convcom(); // really returns void
int dogocom();
int bugcom(); // really returns void
int typocom(); // really returns void
void becom();
void debugcom();
void digcom();
void eatcom();
void emptycom();
void exorcom();
void givecom();
void inumcom();
void look_cmd();
void playcom();
void rawcom();
void rescom();
void rmeditcom();
void rollcom();
void saycom();
void scorecom();
void shellcom();
void shoutcom();
void stealcom();
void tellcom();
void tsscom();
void updcom();
int setincom(); // returns ?
int setoutcom(); // returns ?
int setmincom(); // returns ?
int setmoutcom(); // returns ?

// frob.c
void frobnicate();

// support.c
char* pname();
int psex(int chr);
int setpsex(int chr, int v); // really returns void
int psexall(long chr); // truncated from long
int setpsexall(int chr, long v); // really returns void
int ocreate(int ob); // really returns void
int ospare(int ob); // really returns bool
int obaseval(int ob);
int ocarrf(int ob); // truncated from long
int ohany(long mask);
char* oname();
int oloc(int ob); // truncated from long
char* olongt(int ob, int st);
int obflannel(int ob);
int oflannel(int ob);
int setoloc(int ob, int l, int c); // really returns void
int isavl(int ob);
int isdest(int ob);
int plev(int chr); // truncated from long
int setplev(int chr, int v); // really returns void
int pstr(int chr); // truncated from long
int setpstr(int chr, int v); // really returns void
int pwpn(int chr);
int setpwpn(int chr, int n);
int pvis(int chr); // truncated from long
int setpvis(int chr, int v); // really returns void
int ploc(int chr); // truncated from long
int setploc(int chr, int n); // really returns void
int ptothlp(int pl);
int obyte(int ox, int x);
int osetbyte(int o, int x, int y); // really returns void
int oclrbit(int ob, int x); // really returns void
int oclearbit(int ob, int x); // really returns void
int osetbit(int ob, int x); // really returns void
int otstbit(int ob, int x); // truncated from long
int ptstbit(long ch, long x);
int psetflg(long ch, long x); // really returns void
int pclrflg(long ch, long x); // really returns void
int ptstflg(long ch, long x);
int omaxstate(int ob);
int phelping(int x); // truncated from long
int setphelping(int x, int y); // really returns void
int setppos(int chr, int v);

// objsys.c
int fobn(char* word);
int fobna(char* word);
int fobnc(char * word);
int fobncb(char* word, int by);
int fpbns(char* name);
int lojal2(int n);
int dumpitems(); // really returns void
int dumpstuff(int n, int loc);
int whocom(); // really returns void
int usercom(); // really returns void
void dropitem();
int inventory(); // really returns void
int disl4(int n, int s);
int disle3(int n, int s); // really returns void
int lobjsat(int loc); // really returns void
int aobjsat(int loc, int mode); // really returns void
int iscontin(int o1, int o2);
int ishere(int item);
int iscarrby(int item, int user);
void oplong(int x);
void dispuser(int ubase);
void getobj();
int lisobs(); // really returns void
int lispeople(); // really returns void

// packer.c
int byte_put(long* x, int y, int z); // really returns void
int byte_fetch(long x, int y);
int bit_fetch(long x, int y);
int bit_set(long* x, int y); // really returns void
int bit_clear(long* x, int y); // really returns void

// opensys.c
void closeworld();

// bprintf.c
void pbfr();
int fpbn(char* name); // truncated from long
void quprnt(char *x);
void logcom();
void snoopcom();
void chksnp();
void makebfr();
int seeplayer(int x);

// bbc.c
void btmscr();
void topscr();

// gamego.c
int sig_init(); // really returns void
int sig_alon(); // really returns void
int sig_aloff(); // really returns void
void sig_oops(int x);
void sig_ctrlc(int x);
void sig_occur(int x);
int unblock_alarm(); // really returns void
int block_alarm(); // really returns void
int set_progname(int n, char *text); // really returns void

// gamego.c & gmain2.c
char* getkbd(char* s, int l);
// wasn't originally marked as void in gamego.c
void crapup(char* str);

// gmain2.c
int chkbnid(char *user);

// make.h.c
void packitems(char *ary);

// newuaf.c
void saveme();
void initme();
int resword(char* name); // also in gmainstubs.c
void delpers(char* name);

// new1.c
int iam(char* x);
int state(int ob); // truncated from long
int setstate(int o, int v);
int setcarrf(int o, int n); // really returns void
int addforce(char* x);
int ohereandget(long* onm);
int new1rcv(int isme, int chan, char* to, char* from, int code, char* text);
int chkdumb();
int iswornby(int item, int chr);
int forchk(); // really returns void
int chkcrip();
int canwear(int a);
int woundmn(int mon, int am); // really returns void
void wounded(int n);
int damof(int n);
int vicfb(long* x);
int vichfb(long* x);
int victim(long* x);
int sillytp(int per, char *msg); // really returns void
int resetplayers(); // really returns void
int teletrap(long newch); // really returns void
int destroy(int ob); // really returns void
void blindcom();
void blowcom();
int bouncecom(); // really returns void
void changecom();
void closecom();
void cripplecom();
void cuddlecom();
void curecom();
void deafcom();
void dumbcom();
void extinguishcom();
void fireballcom();
void forcecom();
void gropecom();
void hugcom();
void kisscom();
void lightcom();
void lockcom();
void missilecom();
void opencom();
void pushcom();
void putcom();
void removecom();
void screamcom();
void shockcom();
void sighcom();
void slapcom();
void squeezecom();
void starecom();
void ticklecom();
void unlockcom();
void wavecom();
void wearcom();
void lightning();
int tscale();
int vichere(long* x);
void mhitplayer(int mon, int mn);
int on_flee_event();

// mobile.c
int on_timing(); // really returns void
int onlook();
void spraycom();
void singcom();
void crashcom();
void dircom();
void chkfight(int x);
void dorune();
void helpchkr();
int dragget();
int consid_move(int x); // really returns void
void sys_reset();

// blood.c
void hitplayer(long victim, long wpn);
void bloodrcv(long *array, int isme);
void killcom();
void weapcom();

// magic.c
int randperc();
void delcom();
void goloccom();
void inviscom();
int passcom(); // really returns void
void ressurcom();
void sumcom();
void viscom();
void wizcom();

// extra.c
void desrm(int loc, int cf);
int com(); // really returns void
void examcom(); // really returns void
void helpcom(); // really returns void
void incom(); // really returns void
void jumpcom(); // really returns void
int levcom(); // really returns void
//int smokecom(); // really returns void
void stacom(); // really returns void
void valuecom(); // really returns void
void wherecom(); // really returns void
void statplyr();
void wizlist();
void edit_world();

// ndebug.c
int debug2(); // really returns void

// weather.c
void showwthr();
void wthrrcv(int type);
int cancarry(int plyr);
int isdark();
int outdoors();
int modifwthr(int n);
int adjwthr(int n);
void setpflags();
int blizzardcom(); // really returns void
void burpcom();
void crycom();
int fartcom(); // really returns void
int grincom(); // really returns void
int groancom(); // really returns void
void hiccupcom();
void laughcom();
int moancom(); // really returns void
void posecom();
int praycom(); // really returns void
void purrcom();
int raincom(); // really returns void
void setcom();
int sillycom(char* txt);
int sulkcom(); // really returns void
int smilecom(); // really returns void
void sniggercom();
int snowcom(); // really returns void
int stormcom(); // really returns void
int suncom(); // really returns void
int winkcom(); // really returns void
int yawncom(); // really returns void
int emotecom(); // really return void
void longwthr();

// zones.c
int exits(); // really returns void
int findzone(int x, char* str);
int lodex(FILE* file);
int roomnum(char *str, char *offstr);
int showname(int loc);
void loccom();

// ogen.c
int saveout(int n); // really returns void
int loadup();
int flags(char* str);
int binproc(char* str);

// anachronisms.c (redefinitions of system functions)
int flock(int fd, int operation);

char* getpass(const char* prompt);
char* getpw(int uid, char* buf);

#endif
