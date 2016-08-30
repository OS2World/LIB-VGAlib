/* table.c - create sin-cos table included in sincos.c */


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
#include<stdio.h>
#include<math.h>
#include<stdlib.h>

#define FDiv 2048
#define PI 3.14159265359

main() {

int x,y,z;
z=0;

for (x=0; x<=6434; x++) {
     y=2*FDiv*sin(PI*x/6434.0);
	printf("%#x, ",y);
	z++;
	if (z>8) {
	  z=0;
	  printf("\n");
	}

}

}
 
