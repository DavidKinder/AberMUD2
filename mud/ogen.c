#include <stdio.h>

main()
{
saveout(loadup());
}
 
long blob[10000];
 
saveout(n)
{
FILE *a;
extern long blob[];
a=fopen("ob.out","w");
sec_write(a,blob,0,n);
fclose(a);
}
 
loadup()
{
FILE *a;
auto b;
auto ctt;
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
 
flags(str)
char *str;
{
char s2[16],s3[16],s4[128];
long ps;
long res;
char *i;
i=(char *)&res; /* Arggghh urk throw up barf etc - such is B->C conversion */
ps=scan(s2,str,0,"",":");
ps=scan(s3,str,ps,":",":");
ps=scan(s4,str,ps,":","");
printf("Input line is %d\n",str);
res=binproc(s4)<<16; /* highest bits */
res|=numarg(s2)<<8; /* Chars in lowest 16 bits */
res|=numarg(s3);
printf("Result=%d\n",res);
return(res);
}
 
binproc(str)
char *str;
{
long a,b,c;
a=0;
b=0;
while((str[a])&&(str[a]!='\n'))
{
b=b*2+(str[a]-'0');
a++;
}
printf("Binproc of %s is %d\n",str,b);
return(b);
}
