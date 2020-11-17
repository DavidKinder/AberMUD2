#include <stdio.h>
#include "files.h"

extern FILE *openlock();
extern char *pname(  ) ;
extern char *oname(  ) ;

on_timing()
{
	if(randperc()>80) onlook();
}

onlook(  )
    {
long a ;
extern long mynum ;
chkfight( fpbns( "shazareth" ) ) ;
if( !iscarrby( 45, mynum ) )chkfight( fpbns( "wraith" ) ) ;
chkfight( fpbns( "bomber" ) ) ;
chkfight( fpbns( "owin" ) ) ;
chkfight( fpbns( "glowin" ) ) ;
chkfight( fpbns( "smythe" ) ) ;
chkfight( fpbns( "dio" ) ) ;
if( !iscarrby( 45, mynum ) ) chkfight( fpbns( "zombie" ) ) ;
chkfight( fpbns( "rat" ) ) ;
chkfight( fpbns( "ghoul" ) ) ;
chkfight( fpbns( "ogre" ) ) ;
chkfight( fpbns( "riatha" ) ) ;
chkfight( fpbns( "yeti" ) ) ;
chkfight( fpbns( "guardian"));
if( iscarrby( 32, mynum ) ) dorune(  ) ;
if(phelping(mynum)!=-1) helpchkr();
    }
 
 chkfight( x )
    {
    extern long curch ;
    extern long mynum ;
    if( x<0 ) return ; /* No such being */
    consid_move( x); /* Maybe move it */
    if( !strlen( pname( x ) ) ) return ;
    if( ploc( x )!=curch ) return ;
    if( pvis( mynum ) ) return ; /* Im invis */
    if(randperc()>40) return;
if( ( x==fpbns( "yeti" ) )&&( ohany( ( 1<<13 ) ) ) )
{
return ;
}
    mhitplayer( x, mynum ) ;
    }
 
 consid_move(x)
 {;}
 
 crashcom(  )
    {
    extern long my_lev ;
    if( my_lev<10 )
       {
       bprintf( "Hmmm....\n" ) ;
       bprintf( "I expect it will sometime\n" ) ;
       return ;
       }
    bprintf( "Bye Bye Cruel World...\n" ) ;
    sendsys( "", "", -666, 0, "" ) ;
    rescom(  ) ;
    }
 
 singcom(  )
    {
    if( chkdumb(  ) ) return ;
    sillycom( "\001P%s\001\001d sings in Gaelic\n\001" ) ;
    bprintf( "You sing\n" ) ;
    }
 
 spraycom(  )
    {
    long a, b ;
    long c ;
    char bk[ 128 ] ;
    extern long wordbuf[  ] ;
    extern long mynum ;
    extern long curch ;
    b=vichere( &a ) ;
    if( b== -1 ) return ;
    if( brkword(  )== -1 )
       {
       bprintf( "With what ?\n" ) ;
       return ;
       }
    if( !strcmp( wordbuf, "with" ) )
       {
       if( brkword(  )== -1 )
          {
          bprintf( "With what ?\n" ) ;
          return ;
          }
       }
    c=fobna( wordbuf ) ;
    if( c== -1 )
       {
       bprintf( "With what ?\n" ) ;
       return ;
       }
    switch( c )
       {
       default:
          bprintf( "You can't do that\n" ) ;
          break ;
          }
    return ;
    }
 
 /* More new stuff */
 
 dircom(  )
    {
    long a ;
    char b[ 40 ] ;
    char d[ 40 ] ;
    long c ;
    extern long my_lev ;
    extern long numobs ;
    if( my_lev<10 )
       {
       bprintf( "That's a wiz command\n" ) ;
       return ;
       }
    a=0 ;
    while( a<numobs )
       {
       c=findzone( oloc( a ), b ) ;
       sprintf( d, "%s%d", b, c ) ;
       if( ocarrf( a ) ) strcpy( d, "CARRIED" ) ;
       if( ocarrf( a )==3 ) strcpy( d, "IN ITEM" ) ;
       bprintf( "%-13s%-13s", oname( a ), d ) ;
       if( a%3==2 )bprintf( "\n" ) ;
       if( a%18==17 ) pbfr(  ) ;
       a++ ;
       }
    bprintf( "\n" ) ;
    }
 
 sys_reset(  )
    {
    extern long my_lev ;
    char xx[ 128 ] ;
    FILE *fl ;
    long t, u ;
    if( tscale(  )!=2 )
       {
       bprintf( "There are other people on.... So it wont work!\n" ) ;
       return ;
       }
    time( &t ) ;
    fl=openlock( RESET_N, "ruf" ) ;
    if(fl==NULL) goto errk;
    fscanf( fl, "%ld", &u ) ;
    fclose(fl ) ;
    if( ( t-u<( 3600 ) )&&( u<t ) )
       {
       bprintf( "Sorry at least an hour must pass between resets\n" ) ;
       return ;
       }
errk:t=my_lev ;
    my_lev=10 ;
    rescom(  ) ;
    my_lev=t ;
    }
 
 
 dorune(  )
    {
    char bf[ 128 ] ;
    long ct ;
    extern long mynum, my_lev, curch ;
    extern long in_fight;
    if(in_fight) return;
    ct=0 ;
    while( ct<32 )
       {
       if( ct==mynum ){ct++ ;continue ;}
       if( !strlen( pname( ct ) ) ) {ct++ ;continue ;}
       if( plev( ct )>9 ) {ct++ ;continue ;}
       if( ploc( ct )==curch ) goto hitrune ;
       ct++ ;
       }
    return ;
    hitrune:if( randperc(  )<9*my_lev ) return ;
    if( fpbns( pname( ct ) )== -1 ) return ;
    bprintf( "The runesword twists in your hands lashing out savagely\n" ) ;
    hitplayer(ct,32);
    }
 

 pepdrop(  )
    {
    extern long my_sco ;
    long a, b ;
    extern char globme[];
    extern long mynum ;
    extern long curch ;
    sendsys( " ", " ", -10000, curch, "You start sneezing ATISCCHHOOOOOO!!!!\n" ) ;
    if( ( !strlen( pname( 32 ) ) )||( ploc( 32 )!=curch ) )
    return ;
    /* Ok dragon and pepper time */
    if( ( iscarrby( 89, mynum ) )&&( ocarrf( 89 )==2 ) )
       {
       /* Fried dragon */
       strcpy( pname( 32 ), "" ) ; /* No dragon */
       my_sco+=100 ;
       calibme(  ) ;
       return ;
       }
    else
       {
       /* Whoops !*/
       bprintf( "The dragon sneezes forth a massive ball of flame.....\n" ) ;
       bprintf( "Unfortunately you seem to have been fried\n" ) ;
       loseme(  ) ;
       crapup( "Whoops.....   Frying tonight" ) ;
       }
    }
 
 dragget(  )
    {
    extern long curch, my_lev ;
    long a, b ;
long l ;
if( my_lev>9 ) return( 0 ) ;
l=fpbns( "dragon" ) ;
if( l== -1 ) return( 0 ) ;
    if( ploc( l )!=curch ) return( 0 ) ;
    return( 1 ) ;
    }

helpchkr()
{
	extern long mynum;
	extern long curch;
	extern long i_setup;
	long x=phelping(mynum);
	if(!i_setup) return;
	if(!strlen(pname(x))) goto nhelp;
	if(ploc(x)!=curch) goto nhelp;
	return;
	nhelp:bprintf("You can no longer help \001c%s\001\n",pname(x));
	setphelping(mynum,-1);
}
