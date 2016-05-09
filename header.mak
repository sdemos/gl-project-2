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
LDLIBS = -lglut -lGL -lm -lGLEW
# LDLIBS = -lgsl -lgslcblas -lglut -lGL -lm -lGLEW

CFLAGS = -g $(INCLUDE) -DGL_GLEXT_PROTOTYPES -std=c99
CCFLAGS =  $(CFLAGS)
CXXFLAGS = $(CFLAGS)

LIBFLAGS = -g $(LIBDIRS) $(LDLIBS)
CLIBFLAGS = $(LIBFLAGS)
CCLIBFLAGS = $(LIBFLAGS)
