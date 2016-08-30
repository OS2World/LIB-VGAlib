/* plasma.c -  Plasma 1.0 for OS/2 using vgalib */


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
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "vgalib.h"
#include <process.h>
#include <conio.h>

#define CADD 16

BYTE red, green, blue;
BYTE hsidac[768];
PCH ptr0;
unsigned int x;
float hue, sat, intensity;
BYTE bug[64000];

main() {
  Initgraph(&ptr0);
  srand(getpid());
  DosSetPriority(0,1,31,getpid());

  for (x=0; x<256; x++) {
    hue=(x/255.0);
    sat=0.75;
    intensity=1.0;

    HSItoRGB(hue,sat,intensity,&red,&green,&blue);
    hsidac[x*3]=red;
    hsidac[x*3+1]=green;
    hsidac[x*3+2]=blue;
  }


  memset(ptr0,0,64000);
  WritePal(0,256,hsidac);

  for (x=0; x<64000; x++)
    bug[x]=(rand() % (256-CADD*4))+1;

  while (!kbhit()) {
    memcpy(ptr0, bug, 32000);   
    for (x=0; x<32000; x++) { 
      if (++bug[x]>250-CADD*4) {
        bug[x]=1;
        fire(x);
      }
    }
  } 
  exit(0);
}

fire(int x) {
  if (x<32000-320) {
    if (bug[x+320]>1) {
      bug[x+320]+=CADD;
      if (bug[x+320]>250-CADD*4) {
        bug[x+320]=1;
        fire(x+320); 
      }
    }
  }
  if (x>319) {
    if (bug[x-320]>1) {
      bug[x-320]+=CADD;
      if (bug[x-320]>250-CADD*4) {
        bug[x-320]=1;
        fire(x-320);
      }
    }
  }
  if (x % 320) {
    if (bug[x-1]>1) {
      bug[x-1]+=CADD;
      if (bug[x-1]>250-CADD*4) {
        bug[x-1]=1;
        fire(x-1);
      }
    } 
  }
  if (x%320<319) {
    if (bug[x+1]>1) {
      bug[x+1]+=CADD;
      if (bug[x+1]>250-CADD*4) {
        bug[x+1]=1;
        fire(x+1);
      }
    }
  }
}
