#include "functions.h"

#define CHAR1 255
#define CHAR2 655300


void byte_put(long *x,int y,int z)
{
	if(y==1)
	{
		*x&=~CHAR1;
		*x|=z;
	}
	else
	{
		*x&=~CHAR2;
		*x|=((z<<8)&CHAR2);
	}
}

int byte_fetch(long x, int y)
{
	if(y==1) return(x&CHAR1);
	else return((x>>8)&CHAR1);
}

int bit_fetch(long x,int y)
{
	return((x>>(16+y))&1);
}

void bit_set(long *x, int y)
{
	*x|=(1<<(16+y));
}

void bit_clear(long *x, int y)
{
	*x&=~(1<<(16+y));
}
