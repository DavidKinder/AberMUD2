#include "files.h"
#include <stdio.h>
#include "System.h"

void talker(nam)
char *nam;
{
long isawiz;
char z[60];
x1:
if(qnmrq) if(execl(EXE,"   --}----- ABERMUD -----{--    Playing as ",nam,0)==-1)
{
	crapup("mud.exe : Not found\n");
}
cls();
printf("Welcome To AberMUD II [Unix]\n\n\n");
printf("Options\n\n");
printf("1]  Enter The Game\n");
printf("2]  Change Password\n");
printf("\n\n0] Exit AberMUD\n");
printf("\n\n");
isawiz=0;
cuserid(z);
if((!strcmp(z,"wisner"))||(!strcmp(z,"wisner")))
{
printf("4] Run TEST game\n");
printf("A] Show persona\n");
printf("B] Edit persona\n"); 
printf("C] Delete persona\n");
isawiz=1;
}
printf("\n\n");
printf("Select > ");
l2:getkbd(z,2);
lowercase(z);
switch(z[0])
{
case'1':
cls();
printf("The Hallway\n");
printf("You stand in a long dark hallway, which echoes to the tread of your\n");
printf("booted feet. You stride on down the hall, choose your masque and enter the\n");
printf("worlds beyond the known......\n\n");
execl(EXE,"   --{----- ABERMUD -----}--      Playing as ",nam,0);
crapup("mud.exe: Not Found\n");
case '2':chpwd(nam);break;
case '0':exit(0);
case '4':if(isawiz) 
{
cls();
printf("Entering Test Version\n");
}
break;
case 'a':if(isawiz) showuser();break;
case 'b':if(isawiz) edituser();break;
case 'c':if(isawiz) deluser();break;
default:printf("Bad Option\n");
}
goto x1;
}
