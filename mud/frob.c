frobnicate()
{
	extern char wordbuf[];
	extern long my_lev;
	int x;
	char ary[128];
	char bf1[8],bf2[8],bf3[8];
	if(my_lev<10000)
	{
		bprintf("No way buster.\n");
		return;
	}
	if(brkword()==-1)
	{
		bprintf("Frobnicate who ?\n");
		return;
	}
	x=fpbn(wordbuf);
	if((x>15)&&(my_lev!=10033))
	{
		bprintf("Can't frob mobiles old bean.\n");
		return;
	}
	if((plev(x)>9999)&&(my_lev!=10033)) 
	{
		bprintf("You can't frobnicate %s!!!!\n",pname(x));
		return;
	}
	bprintf("New Level: ");
	pbfr();
	keysetback();
	getkbd(bf1,6);
	bprintf("New Score: ");
	pbfr();
	getkbd(bf2,8);
	bprintf("New Strength: ");
	pbfr();
	getkbd(bf3,8);
	keysetup();
	sprintf(ary,"%s.%s.%s.",bf1,bf2,bf3);
	openworld();
	sendsys(pname(x),pname(x),-599,0,ary);
	bprintf("Ok....\n");
}
	
