/* mousedemo.c - Read the mouse, very simple */


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
 
void main() 
{
   USHORT fWait = MOU_WAIT, status;
   HMOU hmou;
   MOUEVENTINFO mouev;
   PCH ptr0;
   unsigned int x,y;

   MouOpen(NULL,&hmou);
   status=MOUSE_DISABLED | MOUSE_MICKEYS;             
   MouSetDevStatus(&status, hmou);     

x=160;
y=100;

Initgraph(&ptr0);
 
   do {      
	MouReadEventQue(&mouev, &fWait, hmou);
	x+=(SHORT) mouev.col;
	y+=(SHORT) mouev.row;
	
if (x>319) { x=319; }
if (y>199) { y=199; }

putpixel(ptr0,x,y,15);	
} while(1);
}
 
