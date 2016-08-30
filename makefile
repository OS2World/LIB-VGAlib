#
#
#  Vgalib V2.0  04/15/93 - By John E. Stone
#
#  Vgalib - A fast direct video grapics library for OS/2 2.x
#


#
#   Copyright (c) 1992, 1993, John E. Stone - johns@cs.umr.edu
#   All rights reserved.
#   
#   For questions comments:  email to johns@cs.umr.edu
#
#   U.S. Mail to:  John E. Stone
#                  1701 N. Pine Apt 8
#                  Rolla MO, 65401 
#
#


# CC is the name of the C compiler.  (For IBM's C Set/2 this is icc)
CC=icc

# ASM is the name of the assembler to use for compiling the 16 bit 
# port I/O functions
ASM=tasm

# COPT are the options for use with single-threaded compilation.
COPT=  /Q+ /G4 /O+ /Gi+ /Gf+ /Gs+ /Gw- /C+

# MTCOPT are the options for use with multi-threaded compilation.
MTCOPT=  /Q+ /G4 /O+ /Gi+ /Gf+ /Gs+ /Gw- /Gm+ /C+ 

# ASMOPT is the list of options for the assembler
ASMOPT= /oi /q

# link is the name of the linker and any global link options.
LNK=link386 /nologo

LIBS=vgalib.lib 3dlib.lib mtvgalib.lib mt3dlib.lib 

OBJS= io386.obj vgalib.obj 3dlib.obj mtvgalib.obj mt3dlib.obj \
	int3dlib.obj mtint3dlib.obj paldemo.obj mousedemo.obj \
	sincos.obj mtsincos.obj spring.obj spirals.obj agregate.obj \
	volcano.obj linyos2.obj lscapes.obj wave.obj spring2.obj  cells.obj \
	plasma.obj text.obj mttext.obj spheres.obj vecballs.obj \
	shadepoly.obj poly.obj shadescapes.obj fire.obj \
	vecpoly.obj linecloud.obj firefly.obj

DEMOS=demomsg $(EXES)

EXES=agregate.exe linyos2.exe spirals.exe wave.exe lscapes.exe     \
	mousedemo.exe paldemo.exe plasma.exe spheres.exe \
	spring.exe spring2.exe volcano.exe vecballs.exe  \
	cells.exe shadepoly.exe shadescapes.exe \
	fire.exe vecpoly.exe linecloud.exe firefly.exe

all : working stvgalib mtvgalib st3dlib mt3dlib $(DEMOS) 

working:
	@echo  ************************************************** 
	@echo  *                                                *
	@echo  *    Vgalib V2.0 04/15/93  -  By John E. Stone   *
	@echo  *                                                * 
	@echo  *      A fast graphics library for OS/2 2.x      * 
	@echo  *                                                *
	@echo  **************************************************
	@echo  .        
	@echo  .  Use licc for better compilation speeds with icc.
	@echo  . 
	@echo  Beginning compilation. . . . .


#
#  ********* Build the libraries ********
#

stvgalib : stvgmsg vgalib.lib
 
vgalib.lib : vgalib.obj sincos.obj poly.obj text.obj io386.obj 
	rm -f vgalib.lib
	lib /nologo vgalib.lib \
	  +vgalib.obj +sincos.obj +io386.obj +poly.obj +text.obj;

stvgmsg :
	@echo * Building Single Threaded Vgalib Library. . 

vgalib.obj : vgalib.c 
	$(CC) $(COPT) vgalib.c

io386.obj : io386.asm
	$(ASM) $(ASMOPT) io386.asm 

sincos.obj : sincos.c 
	$(CC) $(COPT) sincos.c

poly.obj : poly.c
	$(CC) $(COPT) poly.c

text.obj : text.c
	$(CC) $(COPT) text.c

st3dlib : st3dmsg 3dlib.lib

3dlib.lib : 3dlib.obj int3dlib.obj 
	rm -f 3dlib.lib
	lib /nologo 3dlib.lib +3dlib.obj +int3dlib.obj;

st3dmsg :
	@echo * Building Single Threaded 3D Library. . .

3dlib.obj : 3dlib.c
	$(CC) $(COPT) 3dlib.c

int3dlib.obj : int3dlib.c
	$(CC) $(COPT) int3dlib.c

mtvgalib : mtvgmsg mtvgalib.lib

mtvgalib.lib : mtvgalib.obj mtsincos.obj mtpoly.obj mttext.obj 
	rm -f mtvgalib.lib
	lib /nologo mtvgalib.lib \
	   +mtvgalib.obj +mtsincos.obj +io386.obj +mtpoly.obj +mttext.obj;

mtvgmsg : 
	@echo * Building Multi Threaded Vgalib Library. . . . .

mtvgalib.obj : vgalib.c
	$(CC) $(MTCOPT) /Fomtvgalib.obj vgalib.c

mtsincos.obj : sincos.c
	$(CC) $(MTCOPT) /Fomtsincos.obj sincos.c

mtpoly.obj : poly.c
	$(CC) $(MTCOPT) /Fomtpoly.obj poly.c

mttext.obj : text.c
	$(CC) $(MTCOPT) /Fomttext.obj text.c

mt3dlib : mt3dmsg mt3dlib.lib

mt3dlib.lib : mt3dlib.obj mtint3dlib.obj
	rm -f mt3dlib.lib
	lib /nologo mt3dlib.lib +mt3dlib.obj +mtint3dlib.obj;

mt3dmsg :
	@echo * Building Multi Threaded 3D Library. . .

mt3dlib.obj : 3dlib.c
	$(CC) $(MTCOPT) /Fomt3dlib.obj 3dlib.c

mtint3dlib.obj : int3dlib.c
	$(CC) $(MTCOPT) /Fomtint3dlib.obj int3dlib.c

#
# ********** Build The Demo Programs **********
# 
demomsg :
	@echo * Building Demo Program Executables. . . . . . .

wave.exe : vgalib.lib wave.obj
	$(LNK) wave,,,vgalib 3dlib,demo.def;

wave.obj : wave.c vgalib.h
	$(CC) $(COPT) wave.c

vecpoly.exe : vgalib.lib 3dlib.lib vecpoly.obj
	$(LNK) vecpoly,,,vgalib 3dlib,demo.def;

vecpoly.obj : vecpoly.c vgalib.h 3dlib.h
	$(CC)  $(COPT) /Sm vecpoly.c

vecballs.exe : vgalib.lib 3dlib.lib vecballs.obj
	$(LNK) vecballs,,,vgalib 3dlib,demo.def;

vecballs.obj : vecballs.c vgalib.h 3dlib.h inline.h
	$(CC) $(COPT) /Sm vecballs.c

lscapes.exe : vgalib.lib 3dlib.lib lscapes.obj
	$(LNK) lscapes,,,vgalib 3dlib,demo.def;

lscapes.obj : lscapes.c vgalib.h 3dlib.h
	$(CC) $(COPT) /Sm lscapes.c

spring.exe : vgalib.lib 3dlib.lib spring.obj 
	$(LNK) spring,,,vgalib 3dlib,demo.def;

spring.obj : spring.c vgalib.h 3dlib.h
	$(CC) $(COPT) /Sm spring.c

spring2.exe : vgalib.lib 3dlib.lib spring2.obj
	$(LNK) spring2,,,vgalib 3dlib,demo.def;

spring2.obj : spring2.c vgalib.h 3dlib.h int3dlib.h 
	$(CC) $(COPT) /Sm spring2.c

spirals.exe : vgalib.lib spirals.obj
	$(LNK) spirals,,,vgalib,demo.def;

spirals.obj : spirals.c vgalib.h
	$(CC) $(COPT) /Sm spirals.c

spheres.exe : vgalib.lib spheres.obj
	$(LNK) spheres,,,vgalib,demo.def;

spheres.obj : spheres.c vgalib.h
	$(CC) $(COPT) /Sm spheres.c

shadescapes.exe : shadescapes.obj vgalib.lib 3dlib.lib vgalib.h 3dlib.h
	$(LNK) shadescapes,,,vgalib 3dlib,demo.def;

shadescapes.obj : shadescapes.c vgalib.h 3dlib.h
	$(CC) $(COPT) /Sm shadescapes.c

shadepoly.exe : shadepoly.obj vgalib.lib 3dlib.lib vgalib.h 3dlib.h
	$(LNK) shadepoly,,,vgalib 3dlib,demo.def;

shadepoly.obj : shadepoly.c vgalib.h 3dlib.h
	$(CC) $(COPT) /Sm shadepoly.c

fire.exe : fire.obj vgalib.lib vgalib.h 
	$(LNK) fire,,,vgalib,demo.def;

fire.obj : fire.c vgalib.h 
	$(CC) $(COPT) /Sm fire.c

firefly.exe : firefly.obj vgalib.lib vgalib.h
	$(LNK) firefly,,,vgalib,demo.def;

firefly.obj : firefly.c vgalib.h
	$(CC) $(COPT) /Sm firefly.c

plasma.exe : vgalib.lib plasma.obj
	$(LNK) plasma,,,vgalib,demo.def;

plasma.obj : plasma.c vgalib.h
	$(CC) $(COPT) /Sm plasma.c 

paldemo.exe : vgalib.lib paldemo.obj
	$(LNK) paldemo,,,vgalib,demo.def;

paldemo.obj : paldemo.c vgalib.h
	$(CC) $(COPT) paldemo.c

mousedemo.exe : vgalib.lib mousedemo.obj
	$(LNK) mousedemo,,,vgalib,demo.def;

mousedemo.obj : mousedemo.c vgalib.h
	$(CC) $(COPT) mousedemo.c

linyos2.exe : vgalib.lib linyos2.obj
	$(LNK) linyos2,,,vgalib,demo.def;

linyos2.obj : linyos2.c vgalib.h
	$(CC) $(COPT) /Sm linyos2.c

linecloud.exe : vgalib.lib linecloud.obj
	$(LNK) linecloud,,,vgalib,demo.def;

linecloud.obj : linecloud.c vgalib.h
	$(CC) $(COPT) /Sm linecloud.c

volcano.exe : mtvgalib.lib volcano.obj
	$(LNK) volcano,,,mtvgalib,demo.def;

volcano.obj : volcano.c vgalib.h
	$(CC) $(MTCOPT) /Sm volcano.c

cells.exe : vgalib.lib cells.obj 
	$(LNK) cells,,,mtvgalib,demo.def;

cells.obj : cells.c vgalib.h
	$(CC) $(MTCOPT) /Sm cells.c

agregate.exe : mtvgalib.lib agregate.obj
	$(LNK) agregate,,,mtvgalib,demo.def;

agregate.obj : agregate.c vgalib.h
	$(CC) $(MTCOPT) /Sm agregate.c

clean : 
	@echo Making clean....
	@echo    Removing Object Files...
	@rm -f $(OBJS) 
	@echo    Removing Library Files...
	@rm -f *.lib
	@echo    Removing Map Files...
	@rm -f *.map
	@echo    Removing Demo Executables...
	@rm -f $(EXES)
	@echo All generated files removed.
