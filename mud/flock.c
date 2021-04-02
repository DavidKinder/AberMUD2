
#include <errno.h>
#include <stdio.h>
#include <sys/fcntl.h>
#include "flock.h"

int flock(int fd, int operation)
{
  struct flock flock;

  switch (operation & ~LOCK_NB)
  {
  case LOCK_SH:
    flock.l_type = F_RDLCK;
    break;
  case LOCK_EX:
    flock.l_type = F_WRLCK;
    break;
  case LOCK_UN:
    flock.l_type = F_UNLCK;
    break;
  default:
    errno = EINVAL;
    return -1;
  }

  flock.l_whence = SEEK_SET;
  flock.l_start = flock.l_len = 0;
  return fcntl(fd,(operation & LOCK_NB) ? F_SETLK : F_SETLKW,&flock);
}

