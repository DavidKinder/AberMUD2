#include <stdio.h>
#include "files.h"
extern FILE * openlock();
extern FILE * openuaf();
extern FILE * openroom();
extern char *oname();
extern char *pname();
extern char globme[];
extern char wordbuf[];
extern long mynum;
extern long curch;
extern long my_lev;
long getnarg();



helpcom()
    {
extern char wordbuf[];
extern long curch,mynum;
extern char globme[];
extern long my_lev;
long a;
char b[128];
if(brkword()!= -1)
{
	a=fpbn(wordbuf);
	if(a== -1)
	{
		bprintf("Help who ?\n");
		return;
	}
	if((ploc(a)!=curch))
	{
		bprintf("They are not here\n");
		return;
	}
	if(a==mynum)
	{
		bprintf("You can't help yourself.\n");
		return;
	}
	if(phelping(mynum)!=-1) 
	{
		sprintf(b,"\001c%s\001 has stopped helping you\n",globme);
		sendsys(pname(a),pname(a),-10011,curch,b);
		bprintf("Stopped helping %s\n",pname(phelping(mynum)));
	}
	setphelping(mynum,a);
	sprintf(b,"\001c%s\001 has offered to help you\n",globme);
	sendsys(pname(a),pname(a),-10011,curch,b);
	bprintf("OK...\n");
	return;
    }
    closeworld();
    bprintf("\001f%s\001",HELP1);
    if(my_lev>9)
       {
       bprintf("Hit <Return> For More....\n");
       pbfr();
       while(getchar()!='\n');
       bprintf("\001f%s\001",HELP2);
       }
    bprintf("\n");
    if(my_lev>9999)
       {
       bprintf("Hit <Return> For More....\n");
       pbfr();
       while(getchar()!='\n');
       bprintf("\001f%s\001",HELP3);
       }
    bprintf("\n");
    }
 
 levcom()
    {
    closeworld();
    bprintf("\001f%s\001",LEVELS);
    }
 
 valuecom()
    {
    long a,b;
    extern char wordbuf[];
    extern long mynum;
    if(brkword()== -1)
       {
       bprintf("Value what ?\n");
       return;
       }
    b=fobna(wordbuf);
    if(b== -1)
       {
       bprintf("There isn't one of those here.\n");
       return;
       }
    bprintf("%s : %d points\n",wordbuf,(tscale()*(obaseval(b)))/5);
    return;
    }
 stacom()
    {
    long a,b;
    extern long my_lev;    	
    if(brkword()== -1)
       {
       bprintf("STATS what ?\n");
       return;
       }
    if(my_lev<10)
       {
       bprintf("Sorry, this is a wizard command buster...\n");
       return;
       }
    a=fobn(wordbuf);
    if(a== -1)
       {
       statplyr();
       return;
       }
    bprintf("\nItem        :%s",oname(a));
if(ocarrf(a)==3) bprintf(       "\nContained in:%s",oname(oloc(a)));
else
{
    if(ocarrf(a)!=0)bprintf("\nHeld By     :%s",pname(oloc(a)));
    else
       {bprintf("\nPosition    :");
       showname(oloc(a));
}
       }
    bprintf("\nState       :%d",state(a));
    bprintf("\nCarr_Flag   :%d",ocarrf(a));
    bprintf("\nSpare       :%d",ospare(a));
    bprintf("\nMax State   :%d",omaxstate(a));
    bprintf("\nBase Value  :%d",obaseval(a));
    bprintf("\n");
    }
 examcom()
    {
    long a,b;
    FILE *x;
    char r[88];
    extern long mynum,curch;
    extern char globme[],wordbuf[];
    if(brkword()== -1)
       {
       bprintf("Examine what ?\n");
       return;
       }
    a=fobna(wordbuf);
    if(a== -1)
       {
       bprintf("You see nothing special at all\n");
       return;
       }
    switch(a)
       {
       case 144:
          if(obyte(144,0)==0)
             {
             osetbyte(144,0,1);
             bprintf("You take a scroll from the tube.\n");
ocreate(145);
             setoloc(145,mynum,1);
             return;
             }
          break;
       case 145:
          ;
          curch= -114;
          bprintf("As you read the scroll you are teleported!\n");
          destroy(145);
          trapch(curch);
          return;
       case 101:
          if(obyte(101,0)==0)
             {
             bprintf("You take a key from one pocket\n");
             osetbyte(101,0,1);
oclrbit(107,0);
             setoloc(107,mynum,1);
             return;
             }
          break;
       case 7:
          setstate(7,randperc()%3+1);
          switch(state(7))
             {
             case 1:
                bprintf("It glows red");break;
             case 2:
                bprintf("It glows blue");break;
             case 3:
                bprintf("It glows green");break;
                }
          bprintf("\n");
          return;
       case 8:
          if(state(7)!=0)
             {
             if((iscarrby(3+state(7),mynum))&&(otstbit(3+state(7),13)))
                {
                bprintf("Everything shimmers and then solidifies into a different view!\n");
                destroy(8);
                teletrap(-1074);
                return;
       case 85:
          if(!obyte(83,0))
             {
             bprintf("Aha. under the bed you find a loaf and a rabbit pie\n");
             ocreate(83);ocreate(84);
             osetbyte(83,0,1);
             return;
             }
          break;
       case 91:
          if(!obyte(90,0))
             {
             ocreate(90);bprintf("You pull an amulet from the bedding\n");
             osetbyte(90,0,1);
             return;
             }
          break;
          }
       }
    break;
    }
 
 sprintf(r,"%s%d",EXAMINES,a);
 x=fopen(r,"r");
 if(x==NULL)
 {
 bprintf("You see nothing special.\n");
 return;
 }
 else
 {while(getstr(x,r))
    {
    bprintf("%s\n",r);
    }
 fclose(x);
 }
 }
 
 statplyr()
 {
 extern char wordbuf[];
 long a,b;
 b=fpbn(wordbuf);
 if(b== -1)
 {
 bprintf("Whats that ?\n");
 return;
 }
 bprintf("Name      : %s\n",pname(b));
 bprintf("Level     : %d\n",plev(b));
 bprintf("Strength  : %d\n",pstr(b));
 bprintf("Sex       : %s\n",(psex(b)==0)?"MALE":"FEMALE");
 bprintf("Location  : ");
 showname(ploc(b));
 }
 wizlist()
 {
 extern long my_lev;
 if(my_lev<10)
 {
 bprintf("Huh ?\n");
 return;
 }
 closeworld();
 bprintf("\001f%s\001",WIZLIST);
 }
 
 incom()
 {
 extern long my_lev,curch;
 extern char wordbuf[];
 char st[80],rn[80],rv[80];
 long ex_bk[7];
 extern long ex_dat[];
 long a;
 long x;
 long y;
 FILE *unit;
 a=0;
 if(my_lev<10){bprintf("Huh\n");return;}
 while(a<7)
 {
 ex_bk[a]=ex_dat[a];
 a++;
 }
 if(brkword()== -1)
 {
 bprintf("In where ?\n");
 return;
 }
 strcpy(rn,wordbuf);
 if(brkword()== -1)
 {
 bprintf("In where ?\n");
 return;
 }
 strcpy(rv,wordbuf);
 x=roomnum(rn,rv);
 if(x==0)
 {
 bprintf("Where is that ?\n");
 return;
 }
 getreinput(st);
 y=curch;
 curch=x;
 closeworld();
 unit=openroom(curch,"r");
if(unit==NULL){curch=y;bprintf("No such room\n");return;}
 lodex(unit);
 fclose(unit);
 openworld();
 gamecom(st);
 openworld();
 if(curch==x)
 {
 a=0;
 while(a<7) {ex_dat[a]=ex_bk[a];a++;}
 }
 curch=y;
 }
 smokecom()
 {
 lightcom();
 }
 
 jumpcom()
 {
 long a,b;
 extern long jumtb[],mynum,curch;
 extern long my_lev;
 char ms[128];
 extern char globme[];
 a=0;
 b=0;
 while(jumtb[a])
 {
 if(jumtb[a]==curch){b=jumtb[a+1];break;}
 a+=2;
 }
 if(b==0){bprintf("Wheeeeee....\n");
 return;}
 if((my_lev<10)&&((!iscarrby(1,mynum))||(state(1)==0)))
 {
 	curch=b;
 bprintf("Wheeeeeeeeeeeeeeeee  <<<<SPLAT>>>>\n");
 bprintf("You seem to be splattered all over the place\n");
 loseme();
 crapup("I suppose you could be scraped up - with a spatula");
 }
 sprintf(ms,"\001s%s\001%s has just left\n\001",globme,globme);
 sendsys(globme,globme,-10000,curch,ms);
 curch=b;
 sprintf(ms,"\001s%s\001%s has just dropped in\n\001",globme,globme);
 sendsys(globme,globme,-10000,curch,ms);
 trapch(b);
 }
 
long jumtb[]={-643,-633,-1050,-662,-1082,-1053,0,0};

wherecom()
 {
 extern long mynum,curch,my_lev,my_str;
 extern char wordbuf[];
 extern char globme[];
 long cha,rnd;
 extern long numobs;
 if(my_str<10)
 {
 bprintf("You are too weak\n");
 return;
 }
 if(my_lev<10) my_str-=2;
 rnd=randperc();
 cha=10*my_lev;
if((iscarrby(111,mynum))||(iscarrby(121,mynum))||(iscarrby(163,mynum)))
   cha=100;
 closeworld();
 if(rnd>cha)
 {
 bprintf("Your spell fails...\n");
 return;
 }
 cha=0;
 if(brkword()== -1)
 {
 bprintf("What is that ?\n");
 return;
 }
 rnd=0;
 while(cha<numobs)
 {
 if(!strcmp(oname(cha),wordbuf))
    {
    rnd=1;
if(my_lev>9999) bprintf("[%3d]",cha);
    bprintf("%16s - ",oname(cha));
    if((my_lev<10)&&(ospare(cha)== -1)) bprintf("Nowhere\n");
    else
       desrm(oloc(cha),ocarrf(cha));
    }
 cha++;
 }
 cha=fpbn(wordbuf);
 if(cha!= -1)
 {
 rnd++;
 bprintf("%s - ",pname(cha));
 desrm(ploc(cha),0);
 }
 if(rnd) return;
 bprintf("I dont know what that is\n");
 }
 
 desrm(loc,cf)
 {
 extern long my_lev;
 FILE *a;
 FILE *unit;
 long b;
 long x[32];
 if((my_lev<10)&&(cf==0)&&(loc>-5))
 {
 bprintf("Somewhere.....\n");
 return;
 }
if(cf==3){
bprintf("In the %s\n",oname(loc));
return;
}
 if(cf>0)
 {
 bprintf("Carried by \001c%s\001\n",pname(loc));
 return;
 }
 unit=openroom(loc,"r");
 if(unit==NULL)
 {
 bprintf("Out in the void\n");
 return;
 }
 b=0;
 while(b++<7) getstr(unit,x);
 bprintf("%-36s",x);
if(my_lev>9){bprintf(" | ");showname(loc);;}
else bprintf("\n");
 fclose(unit);
 }



edit_world()
{
	extern long my_lev,numobs;
	extern char wordbuf[];	
	extern long ublock[];
	extern long objinfo[];
	char a[80],b,c,d;
	extern long genarg();
	extern long mynum;
	if(!ptstbit(mynum,5))
	{
		bprintf("Must be Game Administrator\n");
		return;
	}	
	if(brkword()==-1)
	{
		bprintf("Must Specify Player or Object\n");
		return;
	}
	if(!strcmp(wordbuf,"player")) goto e_player;
	if(strcmp(wordbuf,"object"))
	{
		bprintf("Must specify Player or Object\n");
		return;
	}
	b=getnarg(0,numobs-1);
	if(b==-1) return;
	c=getnarg(0,3);
	if(c==-1) return;
	d=getnarg(0,0);
	if(d==-1) return;
	objinfo[4*b+c]=d;
        bprintf("Tis done\n");
        return;
e_player:b=getnarg(0,47);
	if(b==-1) return;
	c=getnarg(0,15);
	if(c==-1) return;
	d=getnarg(0,0);
	if(d==-1) return;
	ublock[16*b+c]=d;
        bprintf("Tis done\n");
        return;
}
        
long getnarg(bt,to)
long bt,to;
{
	extern char wordbuf[];
	long x;
	if(brkword()==-1)
	{
		bprintf("Missing numeric argument\n");
		return(-1);
	}
	x=numarg(wordbuf);
	if(x<bt) {bprintf("Invalid range\n");return(-1);}
	if((to)&&(x>to)) {bprintf("Invalid range\n");return(-1);}
	return(x);
}
