/* int3dlib.c - Fixed point integer 3D graphics library */

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

#include<math.h>
#include<stdlib.h>

#define FDiv 4096
#define FShift 12


typedef struct {
	int rx1; 
	int rx2;
	int rx3;
	int ry1;
	int ry2;
	int ry3;
	int rz1;
	int rz2;
	int rz3;
	} ROTMATRIX;



void InitRot(Rot,theta,phi,rho)
ROTMATRIX *Rot;
float theta,phi,rho;
{

Rot->rx1= FDiv*cos(phi)*cos(rho);
Rot->rx2= FDiv*(sin(theta)*sin(phi)*cos(rho) - cos(theta)*sin(rho));
Rot->rx3= FDiv*(sin(theta)*sin(rho) + cos(theta)*cos(rho)*sin(phi));
Rot->ry1= FDiv*cos(phi)*sin(rho);
Rot->ry2= FDiv*(cos(theta)*cos(rho) + sin(theta)*sin(phi)*sin(rho));
Rot->ry3= FDiv*(cos(theta)*sin(phi)*sin(rho) - sin(theta)*cos(rho));
Rot->rz1=-FDiv*sin(phi);
Rot->rz2= FDiv*sin(theta)*cos(phi);
Rot->rz3= FDiv*cos(theta)*cos(phi);
}   



void IntInitRot(Rot,theta,phi,rho)
ROTMATRIX *Rot;
int theta,phi,rho;
{
Rot->rx1= (ICOS(phi)*ICOS(rho))/FDiv;
Rot->rx2= (((ISIN(theta)*ISIN(phi))/FDiv)*ICOS(rho))/FDiv - 
		(ICOS(theta)*ISIN(rho))/FDiv;
Rot->rx3= (ISIN(theta)*ISIN(rho))/FDiv + 
		(((ICOS(theta)*ICOS(rho))/FDiv)*ISIN(phi))/FDiv;
Rot->ry1= (ICOS(phi)*ISIN(rho))/FDiv;
Rot->ry2= (ICOS(theta)*ICOS(rho))/FDiv + 
		(((ISIN(theta)*ISIN(phi))/FDiv)*ISIN(rho))/FDiv;
Rot->ry3= (((ICOS(theta)*ISIN(phi))/FDiv)*ISIN(rho))/FDiv - 
		(ISIN(theta)*ICOS(rho))/FDiv;
Rot->rz1= -ISIN(phi);
Rot->rz2= (ISIN(theta)*ICOS(phi))/FDiv;
Rot->rz3= (ICOS(theta)*ICOS(phi))/FDiv;
}


void Rotate3d(Rot,x,y,z,x2,y2,z2) 
ROTMATRIX *Rot;
int x,y,z;
int *x2, *y2, *z2;
{

*x2=(x*(Rot->rx1) + y*(Rot->rx2) + z*(Rot->rx3))>>FShift;
*y2=(x*(Rot->ry1) + y*(Rot->ry2) + z*(Rot->ry3))>>FShift;
*z2=(x*(Rot->rz1) + y*(Rot->rz2) + z*(Rot->rz3))>>FShift;

}


/*
void Project3d(ptr0,x,y,z)
PCH ptr0;
int x,y,z;
{
int x2,y2,t1,t2;

x2=160+((8*x/(z>>12))>>12);
y2=100-((8*y/(z>>12))>>12);

}


*/









