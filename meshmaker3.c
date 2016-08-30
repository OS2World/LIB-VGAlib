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

dfile=fopen("mesh.dat","w+");


fprintf(dfile,"1600 \n");
fprintf(dfile,"3042 \n");

/* enable water... */
fprintf(dfile,"0\n");

fprintf(dfile,"182\n 152\n 110\n");
fprintf(dfile,"1\n");

for (x=0; x<40; x++) {
  for (y=0; y<40; y++) {
tz=(rand() % 20) / 8.0;
tx=x/2.1-10.5;
ty=y/2.1-10.5;
fprintf(dfile,"%f %f %f\n",tx,ty,tz);
  }
}

for (y=0; y<39; y++) {
for (x=(y*40); x<(y*40+39); x++) {
 fprintf(dfile,"%d %d %d %d\n",x,x+1,x+40,(rand() % 10)+25);
}
}

for (y=0; y<39; y++) {
for (x=(y*40); x<(y*40+39); x++) {
 fprintf(dfile,"%d %d %d %d\n",x+1,x+41,x+40,(rand() % 10) + 25);
}
}



fclose(dfile);

} 
