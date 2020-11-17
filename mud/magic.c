#include <stdio.h>
#include "files.h"

extern long curch;
extern long mynum;
extern long my_lev;
extern char globme[];
extern char wordbuf[];
extern char *pname();
extern char *oname();
extern FILE *openroom();
extern FILE *openuaf();
extern FILE *openlock();

randperc()
{
    long x;
    time(&x);
    srand(x);
    x=rand();
    return(x%100);
}

sumcom()
    {
    long a,b;
    extern char wordbuf[];
    extern long curch,mynum;
    extern long my_lev;
    extern long my_str;
    extern char globme[];
    char seg[128];
    char mes[128];
    char ms[128];
    long c,d,x;
    if(brkword()== -1)
       {
       bprintf("Summon who ?\n");
       return;
       }
    a=fobn(wordbuf);
    if(a!= -1) goto sumob;
    a=fpbn(wordbuf);
    if(a== -1)
       {
       bprintf("I dont know who that is\n");
       return;
       }
    if(my_str<10)
       {
       bprintf("You are too weak\n");
       return;
       }
    if(my_lev<10)my_str-=2;
    c=my_lev*2;
    if(my_lev>9) c=101;
if(iscarrby(111,mynum)) c+=my_lev;
if(iscarrby(121,mynum)) c+=my_lev;
if(iscarrby(163,mynum)) c+=my_lev;
    d=randperc();
    if(my_lev>9) goto willwork;
    if((iswornby(90,a))||(c<d))
       {
       bprintf("The spell fails....\n");
       return;
       }
    if((a==fpbn("wraith"))||((iscarrby(32,a))||(iscarrby(159,a))||iscarrby(174,a)))
       {
       bprintf("Something stops your summoning from succeeding\n");
       return;
       }
    if(a==mynum)
       {
       bprintf("Seems a waste of effort to me....\n");
       return;
       }
    if((curch>=-1082)&&(curch<=-1076))
       {
       bprintf("Something about this place makes you fumble the magic\n");
       return;
       }
willwork:bprintf("You cast the summoning......\n");
    if(a<16)
       {
       sendsys(pname(a),globme,-10020,curch,"");
       return;
       }
    if((a==17)||(a==23)) return;
    dumpstuff(a,ploc(a));
    sprintf(seg,"\001s%s\001%s has arrived\n\001",pname(a),pname(a));
    sendsys("","",-10000,curch,seg);
    setploc(a,curch);
    return;
    sumob:;
    if(my_lev<10)
       {
       bprintf("You can only summon people\n");
       return;
       }
    x=oloc(a);
    if(ocarrf(a)>0) x=ploc(x);
    sprintf(ms,"\001p%s\001 has summoned the %s\n",globme,oname(a));
    sendsys(globme,globme,-10000,x,ms);
    bprintf("The %s flies into your hand ,was ",oname(a));
    desrm(oloc(a),ocarrf(a));
    setoloc(a,mynum,1);
    }

 delcom()
    {
    extern long my_lev;
    extern char wordbuf[];
    if(my_lev<11)
       {
       bprintf("What ?\n");
       return;
       }
    if(brkword()== -1)
       {
       bprintf("Who ?\n");
       return;
       }
    if(delu2(wordbuf)== -1)bprintf("failed\n");
    }

 passcom()
    {
    extern char globme[];
    chpwd(globme);
    }

 goloccom()
    {
    extern long curch,my_lev;
    extern char globme[];
    char n1[128];
    char bf[128];
    extern char mout_ms[],min_ms[];
    extern char wordbuf[];
    long a;
    FILE *b;
    if(my_lev<10)
       {
       bprintf("huh ?\n");
       return;
       }
    if(brkword()== -1)
       {
       bprintf("Go where ?\n");
       return;
       }
    strcpy(n1,wordbuf);
    if(brkword()== -1) strcpy(wordbuf,"");
    a=roomnum(n1,wordbuf);
    if((a>=0)||((b=openroom(a,"r"))==0))
       {
       bprintf("Unknown Room\n");
       return;
       }
    fclose(b);
    sprintf(bf,"\001s%%s\001%%s %s\n\001",mout_ms);
    sillycom(bf);
    curch=a;
    trapch(curch);
    sprintf(bf,"\001s%%s\001%%s %s\n\001",min_ms);    
    sillycom(bf);
    }




 wizcom()
    {
    extern long my_lev;
    extern char globme[],wordbuf[];
    extern long curch;
    extern long rd_qd;
    char bf[128];
    if(my_lev<10)
       {
       bprintf("Such advanced conversation is beyond you\n");
       return;
       }
    getreinput(wordbuf);
    sprintf(bf,"\001p%s\001 : %s\n",globme,wordbuf);
    sendsys(globme,globme,-10113,curch,bf);
    rd_qd=1;
    }

 viscom()
    {
    long f;
    extern long my_lev;
    extern long mynum;
    extern char globme[];
    long ar[4];
    if(my_lev<10)
       {
       bprintf("You can't just do that sort of thing at will you know.\n");
       return;
       }
    if(!pvis(mynum))
       {
       bprintf("You already are visible\n");
       return;
       }
    setpvis(mynum,0);
    ar[0]=mynum;
    ar[1]=pvis(mynum);
    sendsys("","",-9900,0,ar);
    bprintf("Ok\n");
    sillycom("\001s%s\001%s suddenely appears in a puff of smoke\n\001");
    }

 inviscom()
    {
    extern long mynum,my_lev;
    extern char globme[];
    extern char wordbuf[];
    long f,x;
    long ar[4];
    if(my_lev<10)
       {
       bprintf("You can't just turn invisible like that!\n");
       return;
       }
    x=10;
    if(my_lev>9999) x=10000;
    if((my_lev==10033)&&(brkword()!=-1)) x=numarg(wordbuf);
    if(pvis(mynum)==x)
       {
       bprintf("You are already invisible\n");
       return;
       }
    setpvis(mynum,x);
    ar[0]=mynum;
    ar[1]=pvis(mynum);
    sendsys("","",-9900,0,ar);
    bprintf("Ok\n");
    sillycom("\001c%s vanishes!\n\001");
    }

 ressurcom()
    {
    extern long my_lev;
    long bf[32];
    extern long curch;
    long a,b;
    extern char wordbuf[];
    if(my_lev<10)
       {
       bprintf("Huh ?\n");
       return;
       }
    if(brkword()== -1)
       {
       bprintf("Yes but what ?\n");
       return;
       }
    a=fobn(wordbuf);
    if(a== -1)
       {
       bprintf("You can only ressurect objects\n");
       return;
       }
    if(ospare(a)!= -1)
       {
       bprintf("That already exists\n");
       return;
       }
    ocreate(a);
    setoloc(a,curch,0);
    sprintf(bf,"The %s suddenly appears\n",oname(a));
    sendsys("","",-10000,curch,bf);
    }
