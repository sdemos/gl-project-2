//
// shapes.h
//
// Prototypes for shape-drawing functions.
//

#ifndef _SHAPES_H_
#define _SHAPES_H_

// Macros for object and shading selection
#define OBJ_TORUS       0
#define OBJ_TEAPOT      1
#define OBJ_HOUSE       2
#define OBJ_TALL_TREE   3
#define OBJ_LEAF_BALL   4
#define OBJ_LUMPY_TREE  5

#define SHADE_FLAT       0
#define SHADE_NOT_FLAT   1

// Prototypes
void makeShape( int choice, int shadingType );

#endif
