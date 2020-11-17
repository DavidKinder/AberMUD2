/* Fast File Controller v0.1 */
#include <stdio.h>
 
FILE *filrf=NULL;  /* - = not open */

extern FILE *openlock(); 
closeworld()
{
	extern FILE *filrf;
        extern long objinfo[],numobs,ublock[];
	if(filrf==NULL) return;
	sec_write(filrf,objinfo,400,4*numobs);
	sec_write(filrf,ublock,350,16*48);
	fcloselock(filrf);
	filrf= NULL;
}
 
FILE *openworld()
{
	extern FILE *filrf;
        extern long objinfo[],numobs,ublock[];
	if(filrf!=NULL) return(filrf);
	filrf=openlock("/usr/tmp/-iy7AM","r+");
	if(filrf==NULL)
	   crapup("Cannot find World file");
	sec_read(filrf,objinfo,400,4*numobs);
	sec_read(filrf,ublock,350,16*48);
	return(filrf);
}
 
