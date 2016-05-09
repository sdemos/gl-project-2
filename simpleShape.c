//
// simpleShape.c
//
// routines for adding triangles to create a new mesh
//
// Students are not to modify this file.
//

#include <stdio.h>
#include <stdlib.h>

#include "floatVector.h"

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/glew.h>
#include <GL/gl.h>
#endif

#include "simpleShape.h"

/**
 * common variables...should probably make this a class and make these
 * data members
 */
floatVector_t points;
floatVector_t normals;
float *pointArray = 0;
float *normalArray = 0;
GLushort *elemArray = 0;


/**
 * clear the current shape
 */
void clearShape( void )
{
    if (pointArray) {
        free( pointArray );
        free( elemArray );
        free( normalArray );
        pointArray = 0;
        elemArray = 0;
        normalArray = 0;
    }
    floatVectorClear( &points );
    floatVectorClear( &normals );
}


/**
 * adds a triangle to the current shape using calculated normals
 */
void addTriangle(
    float x0, float y0, float z0,
    float x1, float y1, float z1,
    float x2, float y2, float z2 )
{
    // calculate the normal
    float ux = x1 - x0;
    float uy = y1 - y0;
    float uz = z1 - z0;

    float vx = x2 - x0;
    float vy = y2 - y0;
    float vz = z2 - z0;

    float nx = (uy * vz) - (uz * vy);
    float ny = (uz * vx) - (ux * vz);
    float nz = (ux * vy) - (uy * vx);

    // Attach the normal to all 3 vertices
    addTriangleWithNorms(
        x0, y0, z0, x1, y1, z1, x2, y2, z2,
        nx, ny, nz, nx, ny, nz, nx, ny, nz
    );
}


/**
 * adds a triangle to the current shape using supplied normals
 */
void addTriangleWithNorms(
    float x0, float y0, float z0,
    float x1, float y1, float z1,
    float x2, float y2, float z2,
    float nx0, float ny0, float nz0,
    float nx1, float ny1, float nz1,
    float nx2, float ny2, float nz2 )
{
    floatVectorPushBack( &points, x0 );
    floatVectorPushBack( &points, y0 );
    floatVectorPushBack( &points, z0 );
    floatVectorPushBack( &points, 1.0 );

    floatVectorPushBack( &normals, nx0 );
    floatVectorPushBack( &normals, ny0 );
    floatVectorPushBack( &normals, nz0 );

    floatVectorPushBack( &points, x1 );
    floatVectorPushBack( &points, y1 );
    floatVectorPushBack( &points, z1 );
    floatVectorPushBack( &points, 1.0 );

    floatVectorPushBack( &normals, nx1 );
    floatVectorPushBack( &normals, ny1 );
    floatVectorPushBack( &normals, nz1 );

    floatVectorPushBack( &points, x2 );
    floatVectorPushBack( &points, y2 );
    floatVectorPushBack( &points, z2 );
    floatVectorPushBack( &points, 1.0 );

    floatVectorPushBack( &normals, nx2 );
    floatVectorPushBack( &normals, ny2 );
    floatVectorPushBack( &normals, nz2 );

}


/**
 * gets the vertex points for the current shape
 */
float *getVertices( void )
{
    int i;

    // delete the old point array of we have one
    if( pointArray ) {
        free( pointArray );
    }

    // create and fill a new point array
    pointArray = (float *) malloc(
        floatVectorSize(&points) * sizeof(float) );
    if( pointArray == 0 ) {
        perror( "point allocation failure" );
        exit( 1 );
    }
    for( i=0; i < points.size; i++ ) {
        pointArray[i] = points.vec[i];
    }

    return pointArray;
}


/**
 * gets the normals for the current shape
 */
float *getNormals( void )
{
    int i;

    // delete the old point array of we have one
    if( normalArray ) {
        free( normalArray );
    }

    // create and fill a new point array
    normalArray = (float *) malloc(
        floatVectorSize(&points) * sizeof(float) );
    if( normalArray == 0 ) {
        perror( "normal allocation failure" );
        exit( 1 );
    }
    for( i=0; i < normals.size; i++ ) {
        normalArray[i] = normals.vec[i];
    }

    return normalArray;
}


/**
 * gets the array of elements for the current shape
 */
GLushort *getElements( void )
{
    int i;

    // delete the old point array of we have one
    if( elemArray ) {
        free( elemArray );
    }

    // create and fill a new point array
    elemArray = (GLushort *) malloc(
        floatVectorSize(&points) * sizeof(GLushort) );
    if( elemArray == 0 ) {
        perror( "element allocation failure" );
        exit( 1 );
    }
    for( i=0; i < points.size; i++ ) {
        elemArray[i] = i;
    }

    return elemArray;
}



/**
 * returns number of vertices in current shape
 */
int nVertices( void )
{
    return floatVectorSize(&points) / 4;
}
