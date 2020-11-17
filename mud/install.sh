#!/bin/sh'
echo 'Making directories'
mkdir TEXT
mkdir SNOOP
mkdir EXAMINES
mkdir TEXT/ROOMS
echo 'initialising files'
cat </dev/null >mud_syslog
cat </dev/null >reset_t
cat </dev/null >reset_n 
cat </dev/null >user_file
echo Compiling .h constructor
gcc -w make.h.c -o hmk
./hmk >files.h
echo '.h built'
echo 'Compiling mud.exe'
make -f makeexe
echo 'Compiling mud.1'
make -f makemud
echo 'Done'
