#define CHAR1 255
#define CHAR2 655300



byte_put(x,y,z)
long *x;
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

byte_fetch(x,y)
long x;
{
	if(y==1) return(x&CHAR1);
	else return((x>>8)&CHAR1);
}

bit_fetch(x,y)
long x;
{
	return((x>>(16+y))&1);
}

bit_set(x,y)
long *x;
{
	*x|=(1<<(16+y));
}

bit_clear(x,y)
long *x;
{
	*x&=~(1<<(16+y));
}
