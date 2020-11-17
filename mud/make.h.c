#include <stdio.h>

char *fseg[]=
{
	"UAF_RAND","uaf.rand",
	"ROOMS","TEXT/ROOMS/",
	"LOG_FILE","mud_syslog",
	"BAN_FILE","banned_file",
	"NOLOGIN","nologin",
	"RESET_T","reset_t",
	"RESET_N","reset_n",
	"RESET_DATA","reset_data",
	"MOTD","TEXT/gmotd2",
	"GWIZ","TEXT/gwiz",
	"HELP1","TEXT/help1",
	"HELP2","TEXT/help2",
	"HELP3","TEXT/help3",
	"WIZLIST","TEXT/wiz.list",
	"CREDITS","TEXT/credits",
	"EXAMINES","EXAMINES/",
	"LEVELS","TEXT/level.txt",
	"PFL","user_file",
	"PFT","user_file.b",
	"EXE","mud.exe",
	"EXE2","mud.1",
	"SNOOP","SNOOP/",
	NULL
};

main()
{
	char ary[2048];
	if(getwd(ary)==0) 
	{
		fprintf(stderr,"Ermmm eek!:%s\n");
		exit(0);
	}
	packitems(ary);
	gethostname(ary,31);
	printf("#define HOST_MACHINE \"%s\"\n",ary);
}


packitems(ary)
char *ary;
{
	int i=0;
l1:	if(fseg[i]==NULL) return;
	printf("#define %s ",fseg[i++]);
	printf("\"%s/%s\"\n",ary,fseg[i++]);
	goto l1;
}

