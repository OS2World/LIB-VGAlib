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

FILE * dfile;

float tx,ty,tz;

int x,y;

main() {

dfile=fopen("model.dat","w+");


fprintf(dfile,"233 \n");

/* ball size */
fprintf(dfile,"12 \n");

/* enable water... */
fprintf(dfile,"1\n");

fprintf(dfile,"182\n 52\n 10\n");
fprintf(dfile,"1\n");

for (x=0; x<15; x++) {
  for (y=0; y<15; y++) {
tz=-3;
tx=1.333*x-9.5;
ty=1.333*y-9.5;
fprintf(dfile,"%f %f %f\n",tx,ty,tz);
  }
}

fprintf(dfile,"0.0 5.0 5.0\n");
fprintf(dfile,"0.0 2.5 2.5\n");
fprintf(dfile,"0.0 7.5 2.5\n");
fprintf(dfile,"0.0 5.0 0.0\n");
fprintf(dfile,"0.0 3.2 4.3\n");
fprintf(dfile,"0.0 6.8 4.3\n");  
fprintf(dfile,"0.0 3.2 0.7\n");
fprintf(dfile,"0.0 6.8 0.7\n");



fclose(dfile);

} 
