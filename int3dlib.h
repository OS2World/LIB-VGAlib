/*
 *
 *  Int3dlib.h - Header file for Integer 3D library
 *
 *
 */


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

void InitRot(ROTMATRIX *, float, float, float);
void IntInitRot(ROTMATRIX *, int, int, int);
void Rotate3d(ROTMATRIX *, int, int, int, int *, int *, int *);



