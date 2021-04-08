#!/bin/sh'
echo 'Making directories'
mkdir -p TEXT
mkdir -p SNOOP
mkdir -p EXAMINES
mkdir -p TEXT/ROOMS
echo 'initialising files'
cat </dev/null >mud_syslog
cat </dev/null >reset_t
cat </dev/null >reset_n 
cat </dev/null >user_file
echo Compiling .h constructor
gcc make.h.c -o hmk
./hmk >files.h
echo '.h built'
echo 'Compiling mud.exe'
make -f makeexe
echo 'Compiling mud.1'
make -f makemud
echo 'Done'
