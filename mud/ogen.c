#include <stdio.h>

#include "functions.h"

void saveout(int n);
int loadup(void);
long flags(char *str);
long binproc(char *str);

int main()
{
saveout(loadup());
return 0;
}
 
long blob[10000];
 
void saveout(int n)
{
FILE *a;
extern long blob[];
a=fopen("ob.out","w");
sec_write(a,blob,0,n);
fclose(a);
}
 
int loadup(void)
{
FILE *a;
int/*auto*/ b;
int/*auto*/ ctt;
extern long blob[];
char c[128];
b=0;
ctt=0;
a=fopen("ob.in","r");
while(fgets(c,127,a))
{
if(ctt%4==2) blob[b++]=flags(c);
else
blob[b++]=numarg(c);
ctt++;
}
fclose(a);
return(b);
}
 
long flags(char *str)
{
char s2[16],s3[16],s4[128];
long ps;
long res;
char *i;
i=(char *)&res; /* Arggghh urk throw up barf etc - such is B->C conversion */
ps=scan(s2,str,0,"",":");
ps=scan(s3,str,ps,":",":");
ps=scan(s4,str,ps,":","");
printf("Input line is %s\n",str);
res=binproc(s4)<<16; /* highest bits */
res|=numarg(s2)<<8; /* Chars in lowest 16 bits */
res|=numarg(s3);
printf("Result=%ld\n",res);
return(res);
}
 
long binproc(char *str)
{
long a,b,c;
a=0;
b=0;
while((str[a])&&(str[a]!='\n'))
{
b=b*2+(str[a]-'0');
a++;
}
printf("Binproc of %s is %ld\n",str,b);
return(b);
}
