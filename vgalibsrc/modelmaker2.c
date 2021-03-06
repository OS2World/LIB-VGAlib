/* modelmaker.c - Produces text input files for vecballs.c */

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
#define NUM 200

FILE * dfile;

float tx,ty,tz;

int x,y;

main() {

dfile=fopen("model.dat","w+");
fprintf(dfile,"%d \n",NUM);
fprintf(dfile,"12 \n");
fprintf(dfile,"0 \n");
fprintf(dfile,"182\n 52\n 10\n");
fprintf(dfile,"1\n");


for (x=0; x<NUM; x++) {
  tx=(rand() % 2000)/100.0 - 10.0;
  ty=(rand() % 2000)/100.0 - 10.0;
  tz=(rand() % 2000)/100.0 - 10.0;
  fprintf(dfile,"%f %f %f\n",tx,ty,tz);
}

fclose(dfile);

} 
