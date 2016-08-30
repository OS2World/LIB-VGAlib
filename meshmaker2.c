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


fprintf(dfile,"400 \n");
fprintf(dfile,"762 \n");

/* enable water... */
fprintf(dfile,"0\n");

fprintf(dfile,"202\n 192\n 190\n");
fprintf(dfile,"1\n");

for (x=0; x<20; x++) {
  for (y=0; y<20; y++) {
tz=0;
tx=x/1.2-8.5;
ty=y/1.2-8.5;
fprintf(dfile,"%f %f %f\n",tx,ty,tz);
  }
}

for (y=0; y<19; y++) {
for (x=(y*20); x<(y*20+19); x++) {
 fprintf(dfile,"%d %d %d %d\n",x,x+1,x+20,(rand() % 10) + 25);
}
}

for (y=0; y<19; y++) {
for (x=(y*20); x<(y*20+19); x++) {
 fprintf(dfile,"%d %d %d %d\n",x+1,x+21,x+20,(rand() % 10) + 25);
}
}



fclose(dfile);

} 
