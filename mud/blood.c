#include <stdio.h>
#include "files.h"
#include "System.h"



long in_fight=0;
long  fighting= -1;



int dambyitem(it)
long it;
    {
    switch(it)
       {
case -1:return(4);
default:if(!otstbit(it,15))return(-1);
else return(obyte(it,0));
          }

    }

long wpnheld= -1;

void weapcom()
    {
    long a,b;
    if(brkword()== -1)
       {
       bprintf("Which weapon do you wish to select though\n");
       return;
       }
    a=fobnc(wordbuf);
    if(a== -1)
       {
       bprintf("Whats one of those ?\n");
       return;
       }
    b=dambyitem(a);
    if(b<0)
       {
       bprintf("Thats not a weapon\n");
       wpnheld= -1;
       return;
       }
    wpnheld=a;
    	calibme();
    bprintf("OK...\n");
    }

void hitplayer(victim,wpn)
 long victim,wpn;
    {
    long a,b,c,d;
    extern long my_lev,my_str;
    extern long wpnheld;
    long z;
    long x[4];
    long cth,ddn,res;
    if(!strlen(pname(victim))) return;
    /* Chance to hit stuff */
    if((!iscarrby(wpn,mynum))&&(wpn!= -1))
       {
       bprintf("You belatedly realise you dont have the %s,\nand are forced to use your hands instead..\n",oname(wpn));
       if(wpnheld==wpn) wpnheld= -1;
       wpn= -1;
       }
    wpnheld=wpn;
    if((wpn==32)&&(iscarrby(16,victim)))
    {
        bprintf("The runesword flashes back away from its target, growling in anger!\n");
        return;
    }
    if(dambyitem(wpn)<0)
       {
       bprintf("Thats no good as a weapon\n");
       wpnheld= -1;
       return;
       }
	if(in_fight)
	{
		bprintf("You are already fighting!\n");
		return;
	}
	fighting=victim;
	in_fight=300;
	res=randperc();
	cth=40+3*my_lev;
	if((iswornby(89,victim))||(iswornby(113,victim))||(iswornby(114,victim)))
        cth-=10;
	if(cth<0) cth=0;
	if(cth>res)
        {
	       bprintf("You hit \001p%s\001 ",pname(victim));
 	       if(wpn!= -1)bprintf("with the %s",oname(wpn));
	       bprintf("\n");
	       ddn=randperc()%(dambyitem(wpn));
	       x[0]=mynum;
	       x[1]=ddn;
	       x[2]=wpn;
	       if(pstr(victim)-ddn<0)
		{
			bprintf("Your last blow did the trick\n");
			if(pstr(victim)>=0)
			{
/* Bonus ? */
				if(victim<16) my_sco+=(plev(victim)*plev(victim)*100);
				else my_sco+=10*damof(victim);
			}
			setpstr(victim,-1); /* MARK ALREADY DEAD */
			in_fight=0;
			fighting= -1;
		}
       if(victim<16)sendsys(pname(victim),globme,-10021,curch,(char *)x);
       else
          	{
          	woundmn(victim,ddn);
          	}
       my_sco+=ddn*2;
       calibme();
       return;
       }
    else
       {
	       bprintf("You missed \001p%s\001\n",pname(victim));
	       x[0]=mynum;
	       x[1]= -1;
	       x[2]=wpn;
	       if(victim<16) sendsys(pname(victim),globme,-10021,curch,(char *)x);
     		else
		woundmn(victim,0);
       }
    }

 killcom()
    {
    long vic,a;
    long x;
    if(brkword()== -1)
       {
       bprintf("Kill who\n");
       return;
       }
    if(!strcmp(wordbuf,"door"))
	{
		bprintf("Who do you think you are , Moog ?\n");
		return;
	}
	if(fobna(wordbuf)!= -1)
       {
	       breakitem(fobna(wordbuf));
	       return;
       }
    if((a=fpbn(wordbuf))== -1)
       {
	       bprintf("You can't do that\n");
	       return;
       }
    if(a==mynum)
       {
	       bprintf("Come on, it will look better tomorrow...\n");
	       return;
       }
    if(ploc(a)!=curch)
       {
	       bprintf("They aren't here\n");
	       return;
       }
    xwisc:if(brkword()== -1)
       {
	       hitplayer(a,wpnheld);
	       return;
       }
    if(!strcmp(wordbuf,"with"))
       {
	       if(brkword()== -1)
	          {
		          bprintf("with what ?\n");
		          return;
	          }
	       }
	    else
	       goto xwisc;
	    x=fobnc(wordbuf);
	    if(x== -1)
	       {
		       bprintf("with what ?\n");
		       return;
	       }
    hitplayer(a,x);
    }


void  bloodrcv(array,isme)
 long *array;
    {
    long x;
    char ms[128];
    if(!isme) return; /* for mo */
    if(array[0]<0) return;
    nlod:if(!strlen(pname(array[0]))) return;
    fighting=array[0];
    in_fight=300;
    if(array[1]== -1)
       {
       bprintf("\001p%s\001 attacks you",pname(array[0]));
       if(array[2]!= -1)bprintf(" with the %s",oname(array[2]));
       bprintf("\n");
       }
    else
       {
       bprintf("You are wounded by \001p%s\001",pname(array[0]));
       if(array[2]>-1)bprintf(" with the %s",oname(array[2]));
       bprintf("\n");
       if(my_lev<10){my_str-=array[1];
    if(array[0]==16) {
    	    my_sco-=100*array[1];
	    bprintf("You feel weaker, as the wraiths icy touch seems to drain your very life force\n");
	    if(my_sco<0) my_str= -1;
	    }
    }
    if(my_str<0)
    {
          syslog("%s slain by %s",globme,pname(array[0]));
          dumpitems();
          loseme();
          closeworld();
          delpers(globme);
          openworld();
          sprintf(ms,"\001p%s\001 has just died.\n",globme);
          sendsys(globme,globme,-10000,curch,ms);
          sprintf(ms,"[ \001p%s\001 has been slain by \001p%s\001 ]\n",globme,pname(array[0]));
          sendsys(globme,globme,-10113,curch,ms);
          crapup("Oh dear... you seem to be slightly dead\n");
          }
       me_cal=1; /* Queue an update when ready */
       }
    }


void  breakitem(x)
    {
    switch(x)
       {
	case 171:sys_reset();break;
	case -1:
          bprintf("What is that ?\n");break;
       default:
          bprintf("You can't do that\n");
          }
    }
	
