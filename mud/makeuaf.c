#include <stdio.h>

struct uaf_being
{
	char p_name[16];
	long p_score;
	long p_strength;
	long p_sex;
	long p_level;
};

main()
{
	struct uaf_being x;
	x.p_sex=0;
	x.p_level=10033;
	x.p_score=0;
	x.p_strength=100;
	strcpy(x.p_name,"Debugger");
	fwrite(&x,1,sizeof(struct uaf_being),stdout);
}
	
