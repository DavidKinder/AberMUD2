In a fit of nostalgia, some years ago I started trying to find source code
to build a version of AberMUD2 close to the one I remember wasting far too
much time on circa 1990. What I found was a later release of AberMUD2
(3.8.7) which had been reworked by Rich Salz, and an early AberMUD2 version,
taken from the "X2 Support Group Game Development Archives" CD, which was at
```
  ftp://x2ftp.oulu.fi/pub/msdos/programming/gamesrc/abermud.zip
```
It's not completely clear which version this is, as the motd file lists it
as 1.12, while distrib says 3.7.14, but all the files seem consistent with
an early public release.

Although this is pretty much what I was after, the contents of the archive
are in a pretty sorry state. It looks like it had been packed with an old
MS-DOS archiver program, as all the filenames are truncated to 8.3, and all
the directory information has been lost, causing some of the files in
EXAMINES/ to be overwritten by those with the same name in TEXT/ROOMS/. Even
worse, the code does not build. Comparing against Rich Salz's version, it
looks as if long lines have somehow been deleted from several source files.

Armed with these two versions, I decided to see if I could get the earlier
and more historically interesting one to run, using the later version as a
guide for any missing pices. I ended up making the changes listed below to
produce a working version of AberMUD2. No attempt has been made to clean up
the code or correct the rather idiosyncratic spelling and grammar.

* Replaced the 10 or so missing files from EXAMINES/ and TEXT/ROOMS/
  with those from Rich Salz's version.
* Compared code against Rich Salz's version and replaced missing long
  lines in source files.
* Replaced a call to getpw() with a call to getpwuid().
* Replaced calls to the unsafe gets() with fgets() in order to avoid
  warning messages from glibc.
* Changed calls to sgtty in key.c to use termios.
* Changed the world generator to zero memory before writing it to the
  game's world file.

Further work was then done, with the help of Cory Cohen, to get AberMUD2 to
compile and run on 64-bit systems. This involved further changes:

* Added a new header file "functions.h" containing ANSI C declarations
  for all functions, and replaced all K&R definitions of functions with
  the ANSI C equivalent.
* Increased various buffer sizes to prevent buffer over-run problems.
* Fixed all mis-matches between printf-style format strings and the
  arguments passed to such functions.
* Moved the default location of the world file to be /var/tmp, rather than
  /usr/tmp.

The source has been tested under [Ubuntu Linux](https://ubuntu.com/) and [Cygwin](https://www.cygwin.com/) (a Unix-like
environment for Windows) and should work
under any other modern Unix or related system. If you have any problems
(or successes, for that matter) let me know.

In order to build you'll need gcc, make and the crypt library.
Virtually every Unix system should already have these. If you're using
Cygwin, gcc and make are in the "Devel" category of the installer, and
crypt is in "Libs". To build, open up a shell, go to the directory
containing this file and enter
```
  cd mud
  sh install.sh
  sh install2.sh
```
If all goes well you should have built the "mud.1" and "mud.exe"
executables, and a new world file in /usr/tmp/. Start up AberMUD:
```
  ./mud.1
```
log on as "debugger", set a password, and enter the game. Enter "reset"
to make items and mobiles appear, and you're ready to play!
