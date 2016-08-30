/* Agregate.c - Fractal seaweed... */
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
#include<stdlib.h>
#include<os2.h>
#include<math.h>
#include<conio.h>
#include<stdio.h>
#include"vgalib.h"
#include<process.h>

#define HANDLE 0
#define WAIT 1

PCH ptr0;
volatile static int KEYHIT;

void keycheck(void *arg);

int main(int argc, char *argv[])
{
char status;
int dx[9] = {0,0,0,1,1,1,-1,-1,-1};
int dy[9] = {0,-1,1,-1,0,1,-1,0,1};
int x,y,x1,y1,i,a,d;
int ymin;
BYTE c;
BYTE savedac[768], newdac[768];


printf("Aggregate 1.0\nBy John E. Stone\n10/19/92\n");
printf("Send email to: johns@cs.umr.edu\n");
DosSleep(2000L);


KEYHIT=0;

/* setup for graphics mode... */



Initgraph(&ptr0);

_beginthread(keycheck,NULL,4096,NULL);

srand(getpid());

while (!KEYHIT) {
ymin=196;
DosSleep(1300L);
cls(ptr0,0);

  while ((!KEYHIT) && (ymin>1)) {
    y=ymin;
    x=rand() % 320;
    c=0;
	while (c==0) {
	   if (y==198) { c=rand() % 60 + 25; }
	   for (d=0; d<9; d++) {
		x1=x+dx[d];
		y1=y+dy[d];
		if (getpixel(ptr0,x1,y1)!=0) {
		    c=getpixel(ptr0,x1,y1);
		    d=10;
		    }
		}
	    putpixel(ptr0,x,y,c);
	    y++;
	    x=x - 1 + (rand() % 4);

	    if ((x<0) || (x>319)) { 
		c=1;
		}
	}
    if ((y-2)<ymin) {
	ymin=y-2;
    }
  }
}




VioScrUnLock(HANDLE);

VioScrLock(WAIT,&status,HANDLE);
cls(ptr0,0);
VioScrUnLock(HANDLE);
exit(0);
}


void keycheck(void *arg) {
char key1;
key1=getchar();

KEYHIT=1;
_endthread();
}
