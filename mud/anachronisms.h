#ifndef __anachronisms
#define __anachronisms

// setstate() is not the setstate() from stdlib
#define setstate library_setstate
#include <stdlib.h>
#undef setstate

#include <unistd.h>
#include <string.h>
#include <sys/fcntl.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#endif
