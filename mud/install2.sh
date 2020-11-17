#!/bin/sh
echo 'Compiling world maker'
gcc -w makeworld.c blib.c -o makeworld.util -lcrypt
./makeworld.util
echo 'Game universe intialised'
echo 'Compiling reset data compiler'
gcc -w ogen.c blib.o -o ogenerate -lcrypt
./ogenerate
cp ob.out reset_data
echo 'Reset data generated'
echo 'Compiling uaf generator'
gcc -w makeuaf.c -o makeuaf
./makeuaf >uaf.rand
echo 'Ok'
echo 'Now set up a password for arthur the archwizard'
