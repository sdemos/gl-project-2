#
# Created by gmakemake (Ubuntu Jul 25 2014) on Tue Nov 24 19:22:07 2015
#

#
# Definitions
#

.SUFFIXES:
.SUFFIXES:	.a .o .c .C .cpp .s .S
.c.o:
		$(COMPILE.c) $<
.C.o:
		$(COMPILE.cc) $<
.cpp.o:
		$(COMPILE.cc) $<
.S.s:
		$(CPP) -o $*.s $<
.s.o:
		$(COMPILE.cc) $<
.c.a:
		$(COMPILE.c) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%
.C.a:
		$(COMPILE.cc) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%
.cpp.a:
		$(COMPILE.cc) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%

CC =		gcc
CXX =		g++

RM = rm -f
AR = ar
LINK.c = $(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS)
LINK.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS)
COMPILE.c = $(CC) $(CFLAGS) $(CPPFLAGS) -c
COMPILE.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) -c
CPP = $(CPP) $(CPPFLAGS)
########## Flags from header.mak

#
# This header.mak file will set up all necessary options for compiling
# and linking C programs which use OpenGL and/or GLUT on the Ubuntu systems.
#
# To use it, place it in the same directory as your source code, and
# run the command
#
#       gmakemake > Makefile
#
# To compile and link your program, just run "make".
#
# If you want to take advantage of GDB's extra debugging features,
# change "-g" in the CFLAGS and LIBFLAGS macro definitions to "-ggdb".
#
INCLUDE =
LIBDIRS =

# To use GSL, comment out the first LDLIBS line and uncomment
# the second, then re-run 'gmakemake > Makefile'.
LDLIBS = -lglut -lGL -lm -lGLEW -lSOIL
# LDLIBS = -lgsl -lgslcblas -lglut -lGL -lm -lGLEW

CFLAGS = -std=c99 -g $(INCLUDE) -DGL_GLEXT_PROTOTYPES
CCFLAGS =  $(CFLAGS)
CXXFLAGS = $(CFLAGS)

LIBFLAGS = -g $(LIBDIRS) $(LDLIBS)
CLIBFLAGS = $(LIBFLAGS)
CCLIBFLAGS = $(LIBFLAGS)

########## End of flags from header.mak


CPP_FILES =	
C_FILES =	floatVector.c lightingParams.c finalMain.c shaderSetup.c shapes.c simpleShape.c viewParams.c
PS_FILES =	
S_FILES =	
H_FILES =	floatVector.h lightingParams.h shaderSetup.h shapes.h simpleShape.h viewParams.h house.h tallTree.h leafBall.h lumpyTree.h
SOURCEFILES =	$(H_FILES) $(CPP_FILES) $(C_FILES) $(S_FILES)
.PRECIOUS:	$(SOURCEFILES)
OBJFILES =	floatVector.o lightingParams.o shaderSetup.o shapes.o simpleShape.o viewParams.o 

#
# Main targets
#

all:	finalMain 

finalMain:	finalMain.o $(OBJFILES)
	$(CC) $(CFLAGS) -o finalMain finalMain.o $(OBJFILES) $(CLIBFLAGS)

#
# Dependencies
#

floatVector.o:	floatVector.h
lightingParams.o:	lightingParams.h
finalMain.o:	lightingParams.h shaderSetup.h shapes.h simpleShape.h viewParams.h
shaderSetup.o:	shaderSetup.h
shapes.o:	shapes.h simpleShape.h house.h tallTree.h leafBall.h lumpyTree.h
simpleShape.o:	floatVector.h simpleShape.h
viewParams.o:	viewParams.h

#
# Housekeeping
#

Archive:	archive.tgz

archive.tgz:	$(SOURCEFILES) Makefile
	tar cf - $(SOURCEFILES) Makefile | gzip > archive.tgz

clean: realclean
	-/bin/rm -f $(OBJFILES) finalMain.o core

realclean:
	-/bin/rm -f finalMain 
