/* texttest.c - Test of text drawing functions . . . */ 


/*
 *   Copyright (c) 1992, 1993, John E. Stone - johns@cs.umr.edu
 *   All rights reserved.
 *   
 *   For questions comments:  email to johns@cs.umr.edu
 *
 *   U.S. Mail to:  John E. Stone
 *                  1701 N. Pine Apt 8
 *                  Rolla MO, 65401 
 *
 */

#define INCL_BASE
#include <os2.h>
#include <stdio.h>
#include "vgalib.h"
 
int main()
{
   PCH ptr0;
   unsigned int x,y,ox,oy;

   char msg[]="ABCDEFGHIJKLMNOPQRSTUVWXYZ";

x=160;
y=100;


Initgraph(&ptr0);
for (y=1; y<20; y++) {
ox=8;
for (x=8; x<=100; x++) { 
putstring(ptr0,ox,ox,msg,0);
putstring(ptr0,x,x,msg,15);
WAITVSYNC
ox=x;
}
ox=100;
for (x=100; x>=8; x--) {
putstring(ptr0,ox,ox,msg,0);
putstring(ptr0,x,x,msg,15);
ox=x;
}
}

}
 
